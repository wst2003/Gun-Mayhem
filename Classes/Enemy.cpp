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
//����AI
Enemy* Enemy::createWithActor(Actor* actor)
{
	//Enemy��ָ�봴���������
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
//����
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
//�õ�������Ϣ���ݴ�������Ӧ
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

//AI�ƶ������𡢼�ǹ����Ϊ�߼�
void Enemy::actByAI()
{
	/*ͨ��Ŀ���AI���Ĳ�ͬ������ͬ��Ӧ*/
	clock_t now = clock();
	int mapId = UserDefault::getInstance()->getIntegerForKey(MAPID) - MAP1;  //��ȡ��ͼID
	auto playerPosition = Vec2(informationOfPlayer.getPosition().x, informationOfPlayer.getPosition().y - 44);
	auto aiPosition = Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 2);
	int controlDistance = 200;  //�������
	Vec2 distance = { 0,0 };
	//��ҵ�����ͼ�߽磬Ŀ������Ϊ��ͼ�ϱ߽�
	if (playerPosition.y < GameScene::mapEdge[mapId].begin()->edgePos.y)
		playerPosition.y = 900;
	//AI�ӵ�Ϊ�ղ���ǹ֧����û�б���ȥ������Ŀ��Ϊ����
	if (this->getGun()->getBullets() == 0 && GameScene::_box->isVisible()) {
		playerPosition = GameScene::_box->getPosition();
		controlDistance = 10;
	}
	distance = aiPosition - playerPosition;
	if (distance.y < -220) {
		//Ѱ·�߼���������ͼ���飬�ҵ���AI����Ҹ���һ�����ҵĵ���ΪĿ��
		std::vector<EdgePosition>::iterator minMapFloor = GameScene::mapEdge[mapId].begin();
		std::vector<EdgePosition>::iterator MapFloor = GameScene::mapEdge[mapId].begin();
		for (; MapFloor != GameScene::mapEdge[mapId].end(); MapFloor++) {
			if (MapFloor->edgePos.y - aiPosition.y > 110 && MapFloor->edgePos.y - aiPosition.y < 150 && this->getPhysicsBody()->getVelocity().y < 1e-5) {
				minMapFloor = MapFloor;
				break;
			}
		}
		playerPosition = minMapFloor->edgePos;
		controlDistance = 10;  //���ÿ�����룬��AIĿ��Ϊ������ֿ�
		distance = aiPosition - playerPosition;
	}
	//����Ŀ����һ��߶����ں���ж��߼�
	//�Ƚ���X����Ľӽ�
	if (fabs(distance.x) > controlDistance && now - damageTime >= 200 && now - fireTime >= 100) {
		if (distance.x > 0)
			this->moveOnGround({ -300.0f,this->getPhysicsBody()->getVelocity().y });
		else
			this->moveOnGround({ 300.0f,this->getPhysicsBody()->getVelocity().y });
	}
	//AI����Ŀ��һ�����ϣ���������������
	if (distance.y >= 110 && !this->getIsIntheAir() && fabs(getPhysicsBody()->getVelocity().y) < 1e-5) {
		this->jumpDown();
	}
	//Y������20���ڣ�����
	else if (fabs(distance.y) < 20) {
		//�������Ϊ200����ʱҲ��Ŀ���Ϊ���ʱ������
		if (controlDistance == 200)
			this->fire();
	}
	//AI����Ŀ�꣬������Ծ
	else if (distance.y <= -50) {
		this->jumpUp();
	}
	return;
}
//���ѵĲ���
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