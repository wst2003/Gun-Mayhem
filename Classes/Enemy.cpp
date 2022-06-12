#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
#include "Enemy.h"
#include "GameScene.h"
#include "SystemHeader.h"
#include"Client.h"
#include "CreateRoomScene.h"


USING_NS_CC;
int  Enemy::leftOrRight = 0;
//创建AI
Enemy* Enemy::createWithActor(Actor* actor)
{
	//Enemy类指针创建与错误处理
	auto EnemyPtr = new (std::nothrow) Enemy();
	if (EnemyPtr && EnemyPtr->initWithFile(actor->getResourceName()))
	{
		EnemyPtr->autorelease();
		EnemyPtr->_physicsBody = PhysicsBody::createBox(EnemyPtr->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
		EnemyPtr->_physicsBody->setDynamic(true);
		EnemyPtr->_physicsBody->setRotationEnable(false);
		EnemyPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
		EnemyPtr->setTag(ENEMY);

		EnemyPtr->_physicsBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
		EnemyPtr->_physicsBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		EnemyPtr->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
		EnemyPtr->addComponent(EnemyPtr->_physicsBody);
		return EnemyPtr;
	}

	CC_SAFE_DELETE(EnemyPtr);
	return nullptr;
}
//开火
void Enemy::fire()
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

void Enemy::stopFire()
{

}
//得到敌人信息，据此做出反应
void Enemy::getPlayerInformation(Player* player)
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

//AI移动、开火、捡枪等行为逻辑
void Enemy::actByAI()
{
	/*通过目标和AI间距的不同做出不同响应*/
	clock_t now = clock();
	int mapId = UserDefault::getInstance()->getIntegerForKey(MAPID) - MAP1;  //获取地图ID
	auto playerPosition = Vec2(informationOfPlayer.getPosition().x, informationOfPlayer.getPosition().y - 44);
	auto aiPosition = Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2);
	int controlDistance = 200;  //开火距离
	Vec2 distance = { 0,0 };
	//玩家掉出地图边界，目标设置为地图上边界
	if (playerPosition.y < GameScene::mapEdge[mapId].begin()->edgePos.y)
		playerPosition.y = 900;
	//AI子弹为空并且枪支箱子没有被拿去，设置目标为箱子
	if (this->getGun()->getBullets() == 0 && GameScene::_box->isVisible()) {
		playerPosition = GameScene::_box->getPosition();
		controlDistance = 10;
	}
	distance = aiPosition - playerPosition;
	if (distance.y < -220) {
		//寻路逻辑，遍历地图数组，找到与AI最近且高于一层左右的地面为目标
		std::vector<EdgePosition>::iterator minMapFloor = GameScene::mapEdge[mapId].begin();
		std::vector<EdgePosition>::iterator MapFloor = GameScene::mapEdge[mapId].begin();
		for (; MapFloor != GameScene::mapEdge[mapId].end(); MapFloor++) {
			if (MapFloor->edgePos.y - aiPosition.y > 110 && MapFloor->edgePos.y - aiPosition.y < 150 && this->getPhysicsBody()->getVelocity().y < 1e-5) {
				minMapFloor = MapFloor;
				break;
			}
		}
		playerPosition = minMapFloor->edgePos;
		controlDistance = 10;  //设置开火距离，与AI目标为玩家区分开
		distance = aiPosition - playerPosition;
	}
	//限制目标在一层高度以内后的判断逻辑
	//先进行X方向的接近
	if (fabs(distance.x) > controlDistance && now - damageTime >= 200 && now - fireTime >= 100) {
		if (distance.x > 0)
			this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
		else
			this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
	}
	//AI高于目标一层以上，且满足下落条件
	if (distance.y >= 110 && !this->getIsIntheAir() && fabs(getPhysicsBody()->getVelocity().y) < 1e-5) {
		this->jumpDown();
	}
	//Y距离在20以内，开火
	else if (fabs(distance.y) < 20) {
		//开火距离为200，此时也是目标仅为玩家时，开火
		if (controlDistance == 200)
			this->fire();
	}
	//AI低于目标，进行跳跃
	else if (distance.y <= -50) {
		this->jumpUp();
	}
	return;
}
//好友的操作
void Enemy::actByFriend(std::string infom)
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
	else if (info.substr(26, 4).compare("true") == 0) {
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
	Enemy::leftOrRight = leftOrRight;
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