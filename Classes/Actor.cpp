#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include "Actor.h"
#include "GameScene.h"
#include "SystemHeader.h"
#include "loseScene.h"
#include "winScene.h"
#include "CreateRoomScene.h"
USING_NS_CC;

//创建人物
Actor* Actor::createActorWithPhysicsBody(const std::string& filename)
{
	//Actor 类指针创建与错误处理
	auto actorPtr = new (std::nothrow) Actor();
	if (actorPtr && actorPtr->initWithFile(filename))
	{
		actorPtr->autorelease();
		//设置人物为物理刚体
		actorPtr->_physicsBody = PhysicsBody::createBox(actorPtr->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		actorPtr->_physicsBody->setDynamic(true);
		actorPtr->_physicsBody->setRotationEnable(false);
		actorPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

		actorPtr->addComponent(actorPtr->_physicsBody);
		
		return actorPtr;
	}

	CC_SAFE_DELETE(actorPtr);
	return nullptr;
}
//初始化人物面板
void Actor::initActor()
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	std::string str_1 = "ID:" + getName();
	nameLabel = Label::createWithTTF(str_1, "fonts/arial.ttf", 35);
	nameLabel->setPosition(Vec2(visibleSize.width * (2 * ID + 1) / 8, visibleSize.height * 1 / 8 + 25));

	std::string str_2 = "bulletsLeft:" + getGun()->getBullets();
	bulletsLeftLabel = Label::createWithTTF(str_2, "fonts/arial.ttf", 35);
	bulletsLeftLabel->setPosition(Vec2(_contentSize.width / 2, _contentSize.height + bulletsLeftLabel->getContentSize().height ));

	std::string str_3 = "PlayerLives:" + getRemainingLive();
	livesLeftLabel = Label::createWithTTF(str_3, "fonts/arial.ttf", 35);
	livesLeftLabel->setPosition(Vec2(visibleSize.width * (2 * ID + 1) / 8, visibleSize.height * 1 / 8 - 25));

	bloodBar = LoadingBar::create("bloodBar.png");
	bloodBar->setPosition(Vec2(visibleSize.width * (2 * ID + 1) / 8, visibleSize.height * 1 / 8 - 80));
	bloodBar->setDirection(LoadingBar::Direction::LEFT);
	bloodBar->setPercent(getBloodLeft());
	
	return;
}

//设置枪械
void Actor::setGun(Gun* inputGun)
{
	if (_joint != nullptr)
	{
		log("remove");
		GameScene::physicsWorld->removeJoint(_joint, true);
		gun->setVisible(false);
		gun->getPhysicsBody()->setCollisionBitmask(0);
		gun->getPhysicsBody()->setCategoryBitmask(0);
	}
	gun = inputGun;
	gun->setVisible(true);
	gun->getPhysicsBody()->setContactTestBitmask(0);
	gun->getPhysicsBody()->setCollisionBitmask(0);
	gun->getPhysicsBody()->setCategoryBitmask(0);

	gun->setPosition(this->getPosition().x + gun->getContentSize().width / 2 + this->getContentSize().width / 2, this->getPosition().y);
	if (gun->getAttribute().damageValue == 50)
		gun->getAttribute().damageValue + ID;
	_joint = PhysicsJointFixed::construct(this->getPhysicsBody(), gun->getPhysicsBody(), this->getPosition());
	GameScene::physicsWorld->addJoint(_joint);

	return;
}

//得到枪械
Gun* Actor::getGun()
{
	return gun;
}

//扔掉枪械
void Actor::throwGun()
{

}

//设置速度
void Actor::moveOnGround(Vec2 speed)
{
	_physicsBody->setVelocity(speed);
	this->setFlippedX(speed.x < 0);
	this->getGun()->setFlippedX(speed.x < 0);
	this->getGun()->setPosition(this->getPosition().x + (speed.x > 0 ? 1 : -1) * (gun->getContentSize().width / 2 + this->getContentSize().width / 2), this->getPosition().y);
	PhysicsJointFixed* joint = PhysicsJointFixed::construct(this->getPhysicsBody(), this->getGun()->getPhysicsBody(), this->getPosition());
	GameScene::physicsWorld->removeJoint(this->_joint, true);
	this->getScene()->getPhysicsWorld()->addJoint(joint);
	this->_joint = joint;
	return;
}

//上跳
void Actor::jumpUp()
{
	auto speedX = _physicsBody->getVelocity().x + 10;
	if (this->_jumpTime == 0 || this->_jumpTime == 1) 
	{
		log("jump");
		this->_isJumping = true;
		_physicsBody->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
		_physicsBody->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
		_physicsBody->setVelocity({ speedX, SPEED_UP });
		this->_jumpTime++;
		
	}
	return;
}

//下平台
void Actor::jumpDown()
{
	if (this->_isDowning)
		return;
	else
	{
		log("down");
		this->_isDowning = true;
		this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 100));
		this->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
		this->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
	}

	return;
}

//落地的效果
void Actor::fallOnGroundEffect()
{

}

//受伤的效果
void Actor::damagedEffect(int damage)
{
	damageTime = clock();
	auto emitter = ParticleExplosion::create();
	emitter->setLife(0.1f);
	emitter->setLifeVar(0.2f);
	emitter->setDuration(0.1f);
	emitter->setPosition(this->getPosition());
	emitter->setStartColor(Color4F::RED);
	emitter->setEndColor(Color4F::RED);
	this->getScene()->addChild(emitter);

	_bloodLeft -= damage;
	_bloodLeft = std::max(_bloodLeft, 0);
}

//死亡的效果
void Actor::killedEffect()
{

}

cocos2d::ui::LoadingBar* Actor::getBloodBar()
{
	return bloodBar;
}

//活动动画
void Actor::startAnimation(bool isFire)
{

}

//停止动画
void Actor::stopAnimation()
{

}
//人物开火
void Actor::fire()
{
	
	if(gun->fire())
		this->_physicsBody->setVelocity({ (this->_flippedX ? 1 : -1) * 400.0f,_physicsBody->getVelocity().y });

	return;
}

//设置是否跳跃
void Actor::setIsJumping(bool isJumping)
{
	_isJumping = isJumping;
	return;
}

//得到跳跃状态
bool Actor::getIsJumping()
{
	return _isJumping;
}
//设置是否下落
void Actor::setIsDowning(bool isDowning)
{
	_isDowning = isDowning;
	return;
}
//得到下落状态
bool Actor::getIsDowning()
{
	return _isDowning;
}
//设置跳跃次数
void Actor::setJumpTime(int times)
{
	_jumpTime = times;
	return;
}
//得到跳跃次数
int Actor::getJumpTime()
{
	return _jumpTime;
}
//设置是否在空中
void Actor::setIsIntheAir(bool isInTheAir)
{
	_isInTheAir = isInTheAir;
	return;
}
//得到是否在空中的状态
bool Actor::getIsIntheAir()
{
	return _isInTheAir;

}
//设置人物剩余生命
void Actor::setRemainingLive(int num)
{
	_remainingLive = num;
	return;
}
//得到人物剩余生命
int Actor::getRemainingLive()
{
	return _remainingLive;
}
//设置人物当前位置信息
void Actor::setActorInformation()
{
	actorInformation.changePosition(this->getPosition());
}
//改变掩码为不可碰撞
void Actor::changeBitMask()
{
	if (getPhysicsBody()->getVelocity().y < 0)
	{
		if (getIsJumping()) {
			setIsJumping(false);

			getPhysicsBody()->setCollisionBitmask((1<<(30-(ID&1) ) )+(1<<ID));
			getPhysicsBody()->setCategoryBitmask((1<<(30-(ID&1) ) )+(1<<ID));


		}
		if (getIsDowning())
		{
			getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
			setIsDowning(false);
		}

	}
	else if (getPhysicsBody()->getVelocity().y < 10.0f &&
		getPhysicsBody()->getVelocity().y > -10.0f)
	{
		setJumpTime(0);
		if (getIsJumping())
			setIsJumping(false);
		if (getIsDowning())
			setIsDowning(false);
		if (getIsIntheAir())
		{
			setIsIntheAir(false);
			log("not in the air");
		}
	}
	else if (getPhysicsBody()->getVelocity().y > 10.0f ||
		getPhysicsBody()->getVelocity().y < -10.0f)
	{
		setIsIntheAir(true);
		log("is in the air");
	}

}
//恢复掩码为可碰撞
void Actor::renewBitMask()
{
	if (getIsDowning())
	{
		if (getPhysicsBody()->getVelocity().y < 0)
		{
			log("separate current ground");
			setIsDowning(false);
			getPhysicsBody()->setCollisionBitmask((1<<(30-(ID&1) ) )+(1<<ID));
			getPhysicsBody()->setCategoryBitmask((1<<(30-(ID&1) ) )+(1<<ID));
		}
	}
	return;
}
//人物触底后调用，实现状态归零
void Actor::contactGround()
{
	Vec2 currentVelovity = getPhysicsBody()->getVelocity();
	if (currentVelovity.y <= 0)
		setJumpTime(0);
	if (getIsJumping())
	{
		if (currentVelovity.y > 0)
		{
			getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
		}
		else
		{
			getPhysicsBody()->setCollisionBitmask((1<<(30-(ID&1) ) )+(1<<ID));
			getPhysicsBody()->setCategoryBitmask((1<<(30-(ID&1) ) )+(1<<ID));
			setIsJumping(false);
		}
	}
	if (getIsDowning())
	{
		log("downing");
		getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
		getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
	}
	else
	{
		getPhysicsBody()->setCollisionBitmask((1<<(30-(ID&1) ) )+(1<<ID));
		getPhysicsBody()->setCategoryBitmask((1<<(30-(ID&1) ) )+(1<<ID));

		setIsDowning(false);
	}
}
//得到人物ID
int Actor::getID()
{
	return ID;
}
//设置人物ID
void Actor::setID(int id)
{
	ID = id;
}
//人物重生机制，游戏结束判定
void Actor::reLive(bool flag)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (CreateRoomScene::AIorPerson == 2) {
		if (this->getPosition().y > visibleSize.height + this->getContentSize().height + 100)
		{
			isLive = true;
		}
		if ((this->getPosition().y < 100 || getBloodLeft() == 0) && isLive)
		{
			if (getBloodLeft() == 0) {
				this->setPosition(Vec2(0, -1));
			}
			isLive = false;
			int currentLive = this->getRemainingLive() - 1;
			this->setGun(this->getGun());
			if (currentLive == 0)
			{
				auto scene = flag ? loseScene::createScene() : winScene::createScene();
				Director::getInstance()->pushScene(scene);
			}
			this->setRemainingLive(currentLive);
			this->setBloodLeft(100);
			log("Enemy:%d", currentLive);
		}
		if (this->getPosition().y < 0) {
			this->setPosition(visibleSize.width / 4, visibleSize.height + this->getContentSize().height + 200);
			this->getPhysicsBody()->setVelocity({ 0,0 });
			this->setGun(gun);
		}
	}
	else {
		if (this->getPosition().y < 0 || getBloodLeft() == 0)
		{
			int currentLive = this->getRemainingLive() - 1;
			this->setGun(this->getGun());
			if (currentLive == 0)
			{
				auto scene = flag ? loseScene::createScene() : winScene::createScene();
				//			log("you lose");//跳转
				Director::getInstance()->pushScene(scene);
			}
			this->setRemainingLive(currentLive);
			this->setBloodLeft(100);
			log("%d", currentLive);
			this->setPosition(visibleSize.width / 4, visibleSize.height + this->getContentSize().height);
			this->getPhysicsBody()->setVelocity({ 0,0 });
			this->setGun(gun);
		}
	}
	return;
}
//得到人物血条
int Actor::getBloodLeft()
{
	return _bloodLeft;
}
//设置人物血条
void Actor::setBloodLeft(int num)
{
	_bloodLeft = num;
}
//更新人物面板显示
void Actor::renewBrand()
{
	char bullets[10] = {};
	itoa(this->getGun()->getBullets(), bullets, 10);
	std::string str_sub_1 = bullets;
	std::string str_1 = str_sub_1;
	bulletsLeftLabel->setString(str_1);

	char player[10] = {};
	itoa(this->getRemainingLive(), player, 10);
	std::string str_sub_2 = player;
	std::string str_2 = "PlayerLives:" + str_sub_2;
	livesLeftLabel->setString(str_2);

	bloodBar->setPercent(_bloodLeft);
	return;
}