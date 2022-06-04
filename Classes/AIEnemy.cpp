#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
#include "AIEnemy.h"
#include "GameScene.h"
#include "SystemHeader.h"
USING_NS_CC;

AIEnemy* AIEnemy::createWithActor(Actor* actor)
{
	//Player 类指针创建与错误处理
	auto AIEnemyPtr = new (std::nothrow) AIEnemy();
	if (AIEnemyPtr && AIEnemyPtr->initWithFile(actor->getResourceName()))
	{
		AIEnemyPtr->autorelease();
		AIEnemyPtr->_physicsBody = PhysicsBody::createBox(AIEnemyPtr->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		AIEnemyPtr->_physicsBody->setDynamic(true);
		AIEnemyPtr->_physicsBody->setRotationEnable(false);
		AIEnemyPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
		AIEnemyPtr->setTag(ENEMY);

		AIEnemyPtr->_physicsBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
		AIEnemyPtr->_physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		AIEnemyPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
		AIEnemyPtr->addComponent(AIEnemyPtr->_physicsBody);
		return AIEnemyPtr;
	}

	CC_SAFE_DELETE(AIEnemyPtr);
	return nullptr;
}


void AIEnemy::fire()
{
	if (gun->fire())
		this->_physicsBody->setVelocity({ (this->_flippedX ? 1 : -1) * 400.0f,_physicsBody->getVelocity().y });
	return;
}

void AIEnemy::stopFire()
{

}

void AIEnemy::getPlayerInformation(Player* player)
{
	informationOfPlayer = player->sendPlayerInformation();
	return;
}

void AIEnemy::actByAI()
{
	auto playerPosition = informationOfPlayer.getPosition();
	if (this->getGun()->getBullets() == 0)
		playerPosition = GameScene::_box->getPosition();
	auto upPosition = this->getPosition().y + this->getContentSize().height / 2;
	auto downPosition = this->getPosition().y - this->getContentSize().height / 2;
	if (playerPosition.y >= downPosition && playerPosition.y <= upPosition)
		this->fire();
	
	if (fabs(this->getPosition().x - playerPosition.x) < Director::getInstance()->getVisibleSize().width / 10 + 2)
	{

		if (fabs(this->getPosition().x - playerPosition.x - Director::getInstance()->getVisibleSize().width / 10) == 0)
			flag = -1;
		else if (fabs(this->getPosition().x - playerPosition.x + Director::getInstance()->getVisibleSize().width / 10) == 0)
			flag = 1;
		else if (!flag && fabs(this->getPosition().x - playerPosition.x) < Director::getInstance()->getVisibleSize().width / 10)
			flag = (this->getPosition().x - playerPosition.x > 0 ? -1 : 1);
		if (flag == -1)
			this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
		else if (flag == 1)
			this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
		else
		{
			if (this->getPosition().x < playerPosition.x && fabs(this->getPhysicsBody()->getVelocity().y) <= 1e-5 && this->getPosition().y < Director::getInstance()->getVisibleSize().height)
				this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
			else if (fabs(this->getPhysicsBody()->getVelocity().y) <= 1e-5 && this->getPosition().y < Director::getInstance()->getVisibleSize().height)
				this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
		}
	}
	else
	{
		flag = 0;
		if (this->getPosition().x < playerPosition.x && fabs(this->getPhysicsBody()->getVelocity().y) <= 1e-5 && this->getPosition().y < Director::getInstance()->getVisibleSize().height)
			this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
		else if (fabs(this->getPhysicsBody()->getVelocity().y) <= 1e-5 && this->getPosition().y < Director::getInstance()->getVisibleSize().height)
			this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
	}


	if (jumpFlag && (this->getPhysicsBody()->getVelocity().y + 1 < 0 || (fabs(this->getPhysicsBody()->getVelocity().y) < 1e-5 && playerPosition.y - this->getPosition().y > Director::getInstance()->getVisibleSize().height / 5)))
		this->jumpUp();
	if (this->getPosition().y > playerPosition.y + Director::getInstance()->getVisibleSize().height / 5 && this->getPosition().y + 200 < Director::getInstance()->getVisibleSize().height)
	{
		if (fabs(this->getPhysicsBody()->getVelocity().y) < 1e-5 && this->getPosition().y > Director::getInstance()->getVisibleSize().height / 5)
		{
			this->jumpDown();
			jumpFlag = 0;
		}

	}
	else if (fabs(this->getPhysicsBody()->getVelocity().y) < 1e-5)
		jumpFlag = 1;
	return;
}

