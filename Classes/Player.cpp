#include "cocos2d.h"
#include "Player.h"
#include "GameScene.h"
#include "SystemHeader.h"
#include"Actor.h"
USING_NS_CC;

//得到人物信息
ActorInformation Player::sendPlayerInformation()
{
	return Actor::actorInformation;
}

Player* Player::createWithActor(Actor* actor)
{
	//Player 类指针创建与错误处理
	auto playerPtr = new (std::nothrow) Player();
	if (playerPtr && playerPtr->initWithFile(actor->getResourceName()))
	{
		playerPtr->autorelease();
		playerPtr->_physicsBody = PhysicsBody::createBox(playerPtr->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		playerPtr->_physicsBody->setDynamic(true);
		playerPtr->_physicsBody->setRotationEnable(false);
		playerPtr->_physicsBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
		playerPtr->_physicsBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
		playerPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
		playerPtr->setTag(PLAYER);

		playerPtr->addComponent(playerPtr->_physicsBody);

		
		return playerPtr;
	}

	CC_SAFE_DELETE(playerPtr);
	return nullptr;
}


//
void Player::actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap)
{
	auto now = clock();
	auto velocity = _physicsBody->getVelocity();
	
	if ((keyMap[LEFT_KEY] || keyMap[A_KEY]) && now - damageTime >= 200 && now - fireTime >= 100)
	{
		this->moveOnGround({ -400,this->getPhysicsBody()->getVelocity().y });
		this->actorInformation.changeLeftOrRight(1);
	}
	if ((keyMap[RIGHT_KEY] || keyMap[D_KEY]) && now - damageTime >= 200 && now - fireTime >= 100)
	{
		this->moveOnGround({ 400,this->getPhysicsBody()->getVelocity().y });
		this->actorInformation.changeLeftOrRight(2);
	}
	if (keyMap[UP_KEY] || keyMap[W_KEY])
	{
		this->jumpUp();
		keyMap[UP_KEY] = false;
		keyMap[W_KEY] = false;
	}

	if ((keyMap[DOWN_KEY] || keyMap[S_KEY]) && !this->getIsIntheAir() && fabs(velocity.y) < 1e-6)
	{
		this->jumpDown();
		keyMap[DOWN_KEY] = false;
		keyMap[S_KEY] = false;
	}

	return;
}

//
void Player::actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap)
{
	if (mouseMap[MOUSE_DOWN] && this->gun->getFirable())
	{
		/*王诗腾添加*/
		this->actorInformation.changeIsFire(true);
		this->fire();
	}
	else 
	{
		this->actorInformation.changeIsFire(false);
	}
	return;
}

void Player::fire()
{
	if (gun->fire())
	{
		this->_physicsBody->setVelocity({ (this->_flippedX ? 1 : -1) * gun->getAttribute().recoilValue,
		_physicsBody->getVelocity().y });

		fireTime = clock();
		this->actorInformation.changeIsFire(true);
	}
	else
		this->actorInformation.changeIsFire(false);

	return;
}
