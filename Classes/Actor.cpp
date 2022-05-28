#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include "Actor.h"
#include "GameScene.h"

USING_NS_CC;
#define SPEED_LEFT -400
#define SPEED_RIGHT 400
#define SPEED_UP 950


//创建人物
Actor* Actor::createActorWithPhysicsBody(const std::string& filename)
{
	//Actor 类指针创建与错误处理
	auto actorPtr = new (std::nothrow) Actor();
	if (actorPtr && actorPtr->initWithFile(filename))
	{
		actorPtr->autorelease();
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

//设置枪械
void Actor::setGun(Gun* inputGun)
{
	if (_joint != nullptr)
	{
		log("remove");
		GameScene::physicsWorld->removeJoint(_joint, false);
		gun->setVisible(false);
		gun->getPhysicsBody()->setCollisionBitmask(0);
		gun->getPhysicsBody()->setCategoryBitmask(0);
	}
	gun = inputGun;
	gun->getPhysicsBody()->setContactTestBitmask(0);
	gun->getPhysicsBody()->setCollisionBitmask(0);
	gun->getPhysicsBody()->setCategoryBitmask(0);

	gun->setPosition(this->getPosition().x + gun->getContentSize().width, this->getPosition().y);
//	gun->setPosition(1000, 1000);
	_joint = PhysicsJointFixed::construct(this->getPhysicsBody(), gun->getPhysicsBody(), this->getPosition());
//	if(_joint==nullptr)
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
	this->getGun()->setPosition(this->getPosition().x + (speed.x > 0 ? 1 : -1) * this->getGun()->getContentSize().width, this->getPosition().y);
	PhysicsJointFixed* joint = PhysicsJointFixed::construct(this->getPhysicsBody(), this->getGun()->getPhysicsBody(), this->getPosition());
	GameScene::physicsWorld->removeJoint(this->_joint, true);
	this->getScene()->getPhysicsWorld()->addJoint(joint);
	this->_joint = joint;
	return;
}

//上跳
void Actor::jumpUp()
{
	auto speedX = _physicsBody->getVelocity().x;
	if (this->_jumpTime == 0 || this->_jumpTime == 1) 
	{
		if (this->_isJumping)
			return;
		else 
		{
			log("jump");
			this->_isJumping = true;
			_physicsBody->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			_physicsBody->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
			_physicsBody->setVelocity({ speedX, SPEED_UP });
			this->_jumpTime++;
		}
	}
	return;
}

//下落
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
void Actor::damagedEffect()
{
	auto emitter = ParticleExplosion::create();
	emitter->setLife(0.1f);
	emitter->setLifeVar(0.5f);
	emitter->setPosition(this->getPosition());
	this->getScene()->addChild(emitter);
}

//死亡的效果
void Actor::killedEffect()
{

}

//活动动画
void Actor::startAnimation(bool isFire)
{

}

//停止动画
void Actor::stopAnimation()
{

}

void Actor::fire()
{
	gun->fire();

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

void Actor::setIsDowning(bool isDowning)
{
	_isDowning = isDowning;
	return;
}

bool Actor::getIsDowning()
{
	return _isDowning;
}

void Actor::setJumpTime(int times)
{
	_jumpTime = times;
	return;
}

int Actor::getJumpTime()
{
	return _jumpTime;
}


