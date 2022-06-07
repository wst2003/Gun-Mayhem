#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
#include "AIEnemy.h"
#include "GameScene.h"
#include "SystemHeader.h"
#include"Client.h"
#include "CreateRoomScene.h"

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

void AIEnemy::stopFire()
{

}

void AIEnemy::getPlayerInformation(Player* player)
{
	if (CreateRoomScene::AIorPerson == 1) 
	{
		informationOfPlayer = player->sendPlayerInformation();
	}
	else 
	{
		Client::getInstance()->sendInfo(player->sendPlayerInformation().toString());
	}
	return;
}

void AIEnemy::actByAI()
{
	clock_t now = clock();
	int mapId = UserDefault::getInstance()->getIntegerForKey(MAPID) - MAP1;
	auto playerPosition = Vec2(informationOfPlayer.getPosition().x, informationOfPlayer.getPosition().y - 44);
	auto aiPosition = Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2);
	int controlDistance = 200;
	Vec2 distance = { 0,0 };
	if (playerPosition.y < GameScene::mapEdge[mapId].begin()->edgePos.y)
		playerPosition.y = 900;
	distance = aiPosition - playerPosition;
	if (distance.y < -260) {
		//find way to jump up
		std::vector<EdgePosition>::iterator minMapFloor = GameScene::mapEdge[mapId].begin();
		std::vector<EdgePosition>::iterator MapFloor = GameScene::mapEdge[mapId].begin();
		for (; MapFloor != GameScene::mapEdge[mapId].end(); MapFloor++) {
			if (MapFloor->edgePos.y - aiPosition.y > 110 && MapFloor->edgePos.y - aiPosition.y < 150 && this->getIsJumping() == false) {
				minMapFloor = MapFloor;
				break;
			}
		}
		playerPosition = minMapFloor->edgePos;
		controlDistance = 10;
		distance = aiPosition - playerPosition;
	}
	if (this->getGun()->getBullets() == 0 && GameScene::_box->isVisible()) {
		playerPosition = GameScene::_box->getPosition();
		controlDistance = 10;
		distance = aiPosition - playerPosition;
	}
	if (fabs(distance.x) > controlDistance && now - damageTime >= 200 && now - fireTime >= 100) {
		if (distance.x > 0)
			this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
		else
			this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
	}
	if (distance.y >= 110 && !this->getIsIntheAir() && fabs(getPhysicsBody()->getVelocity().y) < 1e-5) {
		this->jumpDown();
	}
	else if (fabs(distance.y) < 20) {
		if (controlDistance == 200)
			this->fire();
	}
	else if (distance.y <= -50) {
		this->jumpUp();
	}
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
	if (info.substr(26, 5).compare("false") == 0) {
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