#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
#include "AIEnemy.h"
#include "CreateRoomScene.h"
#include "GameScene.h"
#include "SystemHeader.h"
#include"Client.h"
#include<vector>
USING_NS_CC;

int  AIEnemy::leftOrRight = 0;
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
	if (gun->fire()) {
		this->_physicsBody->setVelocity({ (this->_flippedX ? 1 : -1) * gun->getAttribute().recoilValue,
		_physicsBody->getVelocity().y });
		/*王诗腾添加*/
		this->actorInformation.changeIsFire(true);
	}
}

void AIEnemy::stopFire()
{

}

void AIEnemy::getPlayerInformation(Player* player)
{
	if (CreateRoomScene::AIorPerson == 1) {
		informationOfPlayer = player->sendPlayerInformation();
	}
	else {
		Client::getInstance()->sendInfo(player->sendPlayerInformation().toString());
	}
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



void AIEnemy::actByFriend(std::string infom)
{
	auto info = infom;
	info.erase(info.begin());
	info.erase(info.end() - 1);
	if (info.length() < 5) {
		return;
	}
	log(info.c_str());
	
	auto x = Value(info.substr(0, 12)).asFloat();
	auto y = Value(info.substr(13, 12)).asFloat();
	bool isFire;
	if (info.substr(26,5).compare("false") == 0) {
		isFire = false;
	}
	else {
		isFire = true;
	}
	int leftOrRight;
	if (isFire) {
		leftOrRight = Value(info.substr(31, 1)).asInt();
	}
	else {
		leftOrRight = Value(info.substr(32, 1)).asInt();
	}
	log(Value(leftOrRight).asString().c_str());
	AIEnemy::leftOrRight = leftOrRight;
	//cocos2d::log((Value(x).asString() + Value(y).asString()).c_str());
	this->setPosition(Vec2(x, y));
	if (leftOrRight == 1) {
		this->moveOnGround(Vec2(-1e-5, 0));
	}
	else {
		this->moveOnGround(Vec2(1e-5, 0));
	}
	if (isFire) {
		this->fire();
	}
	
}