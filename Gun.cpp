#include "cocos2d.h"
#include "Gun.h"
#include "Attribute.h"
#include "SystemHeader.h"
#include "GameScene.h"

USING_NS_CC;

//创建物理枪支
Gun* Gun::createGunWithPhysicsBody(const std::string& filename)
{
	//Gun 类指针创建与错误处理
	auto gunPtr = new (std::nothrow) Gun();

	if (gunPtr && gunPtr->initWithFile(filename))
	{
		gunPtr->_physicsBody = PhysicsBody::createBox(gunPtr->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 1.0f));
		gunPtr->_physicsBody->setDynamic(true);
		gunPtr->_physicsBody->setRotationEnable(false);
		gunPtr->_physicsBody->setCategoryBitmask(GUN_CATEGORY_BITMASK);
		gunPtr->_physicsBody->setCollisionBitmask(GUN_COLLISION_BITMASK);
		gunPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

		gunPtr->addComponent(gunPtr->_physicsBody);
		gunPtr->attr.maxCapacity = 7;
		gunPtr->bulletsLeft = 0;
		gunPtr->attr.velocity = 2800.0f;
		gunPtr->attr.recoilValue = 400.0f;
		gunPtr->_firable = true;
		gunPtr->setIsReloading(false);
		gunPtr->autorelease();
		return gunPtr;
	}

	CC_SAFE_DELETE(gunPtr);
	return nullptr;
}

//对枪支属性赋值
void Gun::setAttribute(GunAttribute inputAttr)
{
	attr = inputAttr;
	return;
}

//读取枪支属性
GunAttribute Gun::getAttribute()
{
	return attr;
}

//设置子弹数量
void Gun::setBullets(int num)
{
	bulletsLeft = std::max(num + bulletsLeft, attr.maxCapacity);
	return;
}

//得到当前剩余子弹数量
int Gun::getBullets()
{
	return bulletsLeft;
}

//将子弹加入精灵帧缓冲区
void Gun::addBulletWithPhysicsBody(const std::string& filename)
{
	auto frame = SpriteFrame::create(filename,Rect(0,0,94,52));
	SpriteFrameCache::getInstance()->addSpriteFrame(frame, "bullet");
	
	return;
}

bool Gun::fire()
{
	if (bulletsLeft > 0)
	{
		clock_t now = clock();
		if (static_cast<double>(now - last) / CLOCKS_PER_SEC < attr.fireRate)
			return false;
		last = clock();
		bulletsLeft--;
		log("%d", bulletsLeft);
		if (bulletsLeft == 0)
		{
			_firable = false;
			log("cannot fire next");
			if (_firable)
				log("true1");
			if (getFirable())
				log("true2");
		}

		Vec2 position = this->getPosition();

		auto bulletSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet"));
		bulletSprite->setPosition(position);
		bulletSprite->setScale(0.25f);

		bulletSprite->setTag(attr.damageValue);
		this->getScene()->addChild(bulletSprite);

		auto bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize(), PhysicsMaterial(100.0f, 1.0f, 1.0f));
		bulletBody->setGravityEnable(false);
		bulletSprite->addComponent(bulletBody);

		bulletSprite->getPhysicsBody()->setCollisionBitmask(BULLET_COLLISION_BITMASK);
		bulletSprite->getPhysicsBody()->setCategoryBitmask(BULLET_CATEGORY_BITMASK);
		bulletSprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
		//float bulletVelocity = 2800;
		bulletBody->setVelocity({ (this->_flippedX ? -1 : 1) * attr.velocity,0 });
		auto emitter = ParticleFire::create();
		emitter->setLife(0.1f);
		emitter->setLifeVar(0.5f);
		emitter->setDuration(0.1f);
		emitter->setColor(Color3B::YELLOW);
		emitter->setPosition(bulletBody->getPosition() + this->getContentSize());
		addChild(emitter);

		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
			AudioEngine::play2d(CLICKSOUND);
		return true;
	}
	else
	{
		log("fire when no bullet remaining");
	}
	return false;
}
void Gun::bulletReloading(float dt)
{
	log("enter the schedule function ");
	setBullets(attr.maxCapacity);
	
	if (getIsReloading())
	{
		setIsReloading(false);
	}
	if (!getFirable())
	{
		_firable = true;
	}
	
}
void Gun::setIsReloading(bool isReloading)
{
	_isReloading = isReloading;
}
bool Gun::getIsReloading()
{
	return _isReloading;
}
bool Gun::getFirable()
{
	return _firable;
}

