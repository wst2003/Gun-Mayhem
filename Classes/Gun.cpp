#include "cocos2d.h"
#include "Gun.h"
#include "Attribute.h"
#include "SystemHeader.h"
#include "GameScene.h"

USING_NS_CC;

//��������ǹ֧
Gun* Gun::createGunWithPhysicsBody(const std::string& filename)
{
	//Gun ��ָ�봴���������
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

		//����ǹ֧��������
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

//��ǹ֧���Ը�ֵ
void Gun::setAttribute(GunAttribute inputAttr)
{
	attr = inputAttr;
	return;
}

//��ȡǹ֧����
GunAttribute Gun::getAttribute()
{
	return attr;
}

//�����ӵ�����
void Gun::setBullets(int num)
{
	bulletsLeft = std::max(num + bulletsLeft, attr.maxCapacity);
	return;
}

//�õ���ǰʣ���ӵ�����
int Gun::getBullets()
{
	return bulletsLeft;
}

//���ӵ����뾫��֡������
void Gun::addBulletWithPhysicsBody(const std::string& filename)
{
	auto frame = SpriteFrame::create(filename, Rect(0, 0, 94, 52));
	if (filename == BOMB_FILENAME)
		frame = SpriteFrame::create(filename, Rect(0, 0, 50, 50));
	SpriteFrameCache::getInstance()->addSpriteFrame(frame, filename.substr(0, filename.size() - 4));
	return;
}

//ǹ֧����
bool Gun::fire()
{
	if (bulletsLeft > 0)
	{
		//���ٵ�����
		clock_t now = clock();
		if (static_cast<double>(now - last) / CLOCKS_PER_SEC < attr.fireRate)
			return false;

		last = clock();
		bulletsLeft--;

		log("fire");
		log("%d", bulletsLeft);

		//���пգ��޷����
		if (bulletsLeft == 0)
		{
			_firable = false;
			log("cannot fire next");
			if (_firable)
				log("true1");
			if (getFirable())
				log("true2");
		}

		//�ӵ��������
		Vec2 position = this->getPosition();
		auto bulletSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(attr.damageValue == 50 ? "bomb" : "bullet"));
		bulletSprite->setPosition(position);
		bulletSprite->setScale(0.25f);

		bulletSprite->setTag(attr.damageValue);
		this->getScene()->addChild(bulletSprite);

		auto bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize(), PhysicsMaterial(80.0f, 1.0f, 1.0f));
		bulletBody->setGravityEnable(false);
		bulletSprite->addComponent(bulletBody);

		bulletSprite->getPhysicsBody()->setCollisionBitmask(BULLET_COLLISION_BITMASK);
		bulletSprite->getPhysicsBody()->setCategoryBitmask(BULLET_CATEGORY_BITMASK);
		bulletSprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);

		//ը������
		if (attr.damageValue == 50) 
		{
			bulletSprite->setScale(1.0f);
			bulletSprite->getPhysicsBody()->setGravityEnable(true);
			bulletSprite->getPhysicsBody()->setCollisionBitmask(0xFFFFFFFF);
			bulletBody->setMass(10000000.0f);
		}
		bulletBody->setVelocity({ (this->_flippedX ? -1 : 1) * attr.velocity,0 });

		//ǹ�ڻ���
		auto emitter = ParticleFire::create();
		emitter->setLife(0.5f);
		emitter->setLifeVar(0.5f);
		emitter->setDuration(0.2f);
		emitter->setColor(Color3B::YELLOW);
		emitter->setPosition(this->getPosition());

		this->getScene()->addChild(emitter);

		//������Ч
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
		{
			AudioEngine::play2d(CLICKSOUND);
			AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
		}


		return true;
	}
	else
	{
		log("fire when no bullet remaining");
	}
	return false;
}

//ǹ֧����
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

//�����Ƿ񻻵�
void Gun::setIsReloading(bool isReloading)
{
	_isReloading = isReloading;
}

//�õ�����״̬
bool Gun::getIsReloading()
{
	return _isReloading;
}

//�õ��Ƿ���Կ���
bool Gun::getFirable()
{
	return _firable;
}

