#include "cocos2d.h"
#include "Gun.h"
#include "Attribute.h"
#include "HandGun.h"
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

		gunPtr->_physicsBody->setCategoryBitmask(GUN_CATEGORY_BITMASK);
		gunPtr->_physicsBody->setCollisionBitmask(GUN_COLLISION_BITMASK);
		gunPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

		gunPtr->addComponent(gunPtr->_physicsBody);

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
	auto frame = SpriteFrame::create(filename,Rect(0,0,94,52));
	SpriteFrameCache::getInstance()->addSpriteFrame(frame, "bullet");
	
	return;
}

void Gun::fire()
{
	Vec2 position = this->getPosition();

	auto bulletSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet"));
	bulletSprite->setPosition(position);
	bulletSprite->setScale(0.25f);

	bulletSprite->setTag(BULLET);
	this->getScene()->addChild(bulletSprite);

	auto bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize(), PhysicsMaterial(20.0f, 1.0f, 1.0f));
	bulletBody->setGravityEnable(false);
	bulletSprite->addComponent(bulletBody);

	bulletSprite->getPhysicsBody()->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	bulletSprite->getPhysicsBody()->setCategoryBitmask(BULLET_CATEGORY_BITMASK);
	bulletSprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	float bulletVelocity = 2800;
	bulletBody->setVelocity({ (this->_flippedX ? -1 : 1) * bulletVelocity,0 });
	auto emitter = ParticleFire::create();
	emitter->setLife(0.1f);
	emitter->setLifeVar(0.5f);
	emitter->setDuration(0.1f);
	emitter->setColor(Color3B::YELLOW);
	emitter->setPosition(bulletBody->getPosition()+this->getContentSize());
	addChild(emitter);

	return;
}