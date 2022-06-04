#include "cocos2d.h"
#include "StartGameScene.h"
#include "Player.h"
#include "Actor.h"
#include "GameScene.h"
#include "AIEnemy.h"
#include "Gun.h"
#include"winScene.h"
#include"loseScene.h"
#include "SystemHeader.h"
#include "ui/UIScrollView.h"


USING_NS_CC;

PhysicsWorld* GameScene::physicsWorld = nullptr;
Sprite* GameScene::_box = nullptr;

//创建场景
Scene* GameScene::createScene()
{

	auto scene = Scene::createWithPhysics();	//物理引擎
	scene->getPhysicsWorld()->setGravity({ 0,-2000 });
	scene->getPhysicsWorld()->setSubsteps(10.0f);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	physicsWorld = scene->getPhysicsWorld();
	auto gameLayer = GameScene::create();
	scene->addChild(gameLayer);

	return scene;
}

bool GameScene::init()
{
	//物理世界
	if (!Scene::init())
	{
		return false;
	}
	//添加调度器
	this->scheduleUpdate();

	//视窗大小与原点
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	initMap();

	auto box = Sprite::create("box.png");
	_box = box;
	_box->setVisible(false);
	auto boxBody = PhysicsBody::createBox(_box->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
	_box->addComponent(boxBody);
	boxBody->setDynamic(true);
	boxBody->setRotationEnable(false);

	box->setTag(BOX);
	addChild(_box);


	//
	auto enemyGun=Gun::createGunWithPhysicsBody(HANDGUN_FILENAME);
	enemyGun->setPosition(visibleSize.width / 4 + 300, visibleSize.height);
	enemyGun->setTag(GUN);
	addChild(enemyGun);
	enemyGun->addBulletWithPhysicsBody("bullet.png");
	enemyGun->setAttribute(HANDGUN_ARR);
	enemyGun->setBullets(enemyGun->getAttribute().maxCapacity);

	auto playerGun = Gun::createGunWithPhysicsBody(HANDGUN_FILENAME);
	playerGun->setPosition(visibleSize.width / 4 + 300, visibleSize.height);
	playerGun->setTag(GUN);
	addChild(playerGun);
	playerGun->addBulletWithPhysicsBody("bullet.png");
	playerGun->setAttribute(HANDGUN_ARR);
	playerGun->setBullets(playerGun->getAttribute().maxCapacity);
	
	randomFallGun({ visibleSize.width * 4 / 5, 290 });

	//人物
	auto player = Player::createWithActor(Actor::createActorWithPhysicsBody("playerA.png"));
	player->setPosition(visibleSize.width / 4, visibleSize.height + player->getContentSize().height);
	player->setRemainingLive(3);
	addChild(player);
	player->setGun(playerGun);
	player->setID(0);
	player->initActor();
	this->_player = player;

	//敌人
	auto enemy = AIEnemy::createWithActor(Actor::createActorWithPhysicsBody("playerB.png"));
	enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height + enemy->getContentSize().height);
	enemy->setRemainingLive(5);
	addChild(enemy);
	this->_enemy = enemy;
	enemy->setGun(enemyGun);
	enemy->setID(3);
	enemy->initActor();

	createBrand(_enemy);
	createBrand(_player);

	//鼠标监听器
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseDown = [=](EventMouse* event) {
		_mouseMap[MOUSE_DOWN] = true;
		_mouseMap[MOUSE_UP] = false;
	};
	//加一个reloadiing的函数
	myMouseListener->onMouseMove = [=](EventMouse* event) {
		_mouseMap[MOUSE_MOVE] = true;

	};

	myMouseListener->onMouseUp = [=](EventMouse* event) {
		_mouseMap[MOUSE_DOWN] = false;
		_mouseMap[MOUSE_UP] = true;
	};

	//键盘监听器
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = true;
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = false;
	};


	//碰撞监听器
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::responseContact, this);

	//添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this); 

	return true;
}

void GameScene::initMap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//创建平台
	switch (UserDefault::getInstance()->getIntegerForKey(MAPID)) {
		case 111:
			map = Sprite::create("map1.png");
			createGround(Vec2(660, 290), 1332);
			createGround(Vec2(400, 510), 413);
			createGround(Vec2(400, 647), 413);
			createGround(Vec2(900, 438), 426);
			createGround(Vec2(900, 575), 426);
			break;
		case 112:
			map = Sprite::create("map2.png");
			createGround(Vec2(675, 720), 1045);
			createGround(Vec2(675, 140), 1045);
			createGround(Vec2(675, 438), 515);
			createGround(Vec2(297, 577), 420);
			createGround(Vec2(297, 286), 420);
			createGround(Vec2(1076, 577), 420);
			createGround(Vec2(1076, 286), 420);
			break;
		case 113:
			map = Sprite::create("map3.png");
			createGround(Vec2(675, 237), 1350);
			createGround(Vec2(190, 350), 225);
			createGround(Vec2(190, 490), 225);
			createGround(Vec2(1150, 350), 225);
			createGround(Vec2(1150, 490), 225);
			break;
		case 114:
			map = Sprite::create("map4.png");
			createGround(Vec2(175, 647), 255);
			createGround(Vec2(610, 647), 272);
			createGround(Vec2(1082, 650), 260);
			createGround(Vec2(400, 510), 182);
			createGround(Vec2(890, 540), 176);
			createGround(Vec2(163, 395), 262);
			createGround(Vec2(687, 400), 180);
			createGround(Vec2(1180, 410), 245);
			createGround(Vec2(520, 290), 178);
			createGround(Vec2(865, 280), 178);
			createGround(Vec2(188, 140), 320);
			createGround(Vec2(540, 140), 260);
			createGround(Vec2(880, 140), 260);
			createGround(Vec2(1215, 140), 245);
			break;
		default:
			break;
	}
	map->setScaleX(visibleSize.width / map->getContentSize().width);
	map->setScaleY(visibleSize.height / map->getContentSize().height);
	map->setPosition(visibleSize / 2);
	this->addChild(map);

	//创建一个物体对象 EdgeBox是一个空心的矩形 相当于边框效果 
	auto node = Node::create();
	auto bound = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height * 3 / 2), PhysicsMaterial(0.1f, 0.0f, 1.0f));
	bound->setContactTestBitmask(0xFFFFFFFF);
	bound->setCategoryBitmask(EDGE_CATEGORY_BITMASK);
	bound->setCollisionBitmask(EDGE_COLLISION_BITMASK);
	node->setPhysicsBody(bound);
	node->setTag(EDGE);
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(node);
	/*--------------------------------------------------*/
}
void GameScene::createGround(Vec2 pos, float length)
{
	auto stoneSprite = Sprite::create("ground.jpg");
	stoneSprite->setScaleX(length / stoneSprite->getContentSize().width);
	stoneSprite->setScaleY(0.1f);
	stoneSprite->setPosition(pos);
	stoneSprite->setVisible(false);

	auto stoneBody = PhysicsBody::createBox(stoneSprite->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 1.0f));
	stoneBody->setDynamic(false);
	stoneSprite->setTag(FOOTSTEP);
	stoneSprite->setPhysicsBody(stoneBody);
	this->addChild(stoneSprite);

	stoneBody->setCategoryBitmask(FOOTSTEP_CATEGORY_BITMASK);
	stoneBody->setCollisionBitmask(FOOTSTEP_COLLISION_BITMASK);
	stoneSprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);

	return;
}

void GameScene::createBrand(Actor* actor)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	addChild(actor->nameLabel, 2, BRAND_NAME + actor->getID());
	addChild(actor->livesLeftLabel, 2, BRAND_LIFELEFT + actor->getID());
	actor->addChild(actor->bulletsLeftLabel, 2, BRAND_BULLETLEFT + actor->getID());
	addChild(actor->getBloodBar(), 2, BRAND_BLOODPERCENT + actor->getID());
	return;
}
//
void GameScene::update(float dt)
{
	_player->renewBrand();
	_enemy->renewBrand();

	clock_t now = clock();
	if (now - _lastTime > 10000.0f)
	{
		randomFallGun({ 1.0f * (rand() % (static_cast<int>(Director::getInstance()->getVisibleSize().width))),
			1.0f * (std::max(rand() % static_cast<int>(Director::getInstance()->getVisibleSize().height / 2),0) +static_cast<int>(Director::getInstance()->getVisibleSize().height / 2)) });
		_lastTime = now;
	}

	//刷新枪的状态
	if (canPlayerSet)
	{
		_player->setGun(_player->getGun());
		canPlayerSet = false;
	}
	if (canEnemySet)
	{
		_enemy->setGun(_enemy->getGun());
		canEnemySet = false;

	}


	_player->actByKeyBoard(_keyMap);
	_player->actByMouse(_mouseMap);

	//重生机制
	_player->reLive(true);
	_enemy->reLive();


	_player->changeBitMask();
	_enemy->changeBitMask();
	_player->setActorInformation();
	_enemy->getPlayerInformation(_player);
	_enemy->actByAI();


	return;
}

//
bool GameScene::responseContact(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() <= BULLET)
		{
			int damage = nodeA->getTag();
			if (nodeB->getTag() != GUN)
				nodeA->removeFromParentAndCleanup(true);
			if (nodeB->getTag() == PLAYER || nodeB->getTag() == ENEMY)
			{
				Actor* actor = dynamic_cast<Actor*>(nodeB);
				actor->damagedEffect(damage);
			}

			return true;
		}
		if (nodeB->getTag() <= BULLET)
		{
			int damage = nodeB->getTag();
			if (nodeA->getTag() != GUN)
				nodeB->removeFromParentAndCleanup(true);
			if (nodeA->getTag() == PLAYER || nodeA->getTag() == ENEMY) 
			{
				Actor* actor = dynamic_cast<Actor*>(nodeA);
				actor->damagedEffect(damage);
			}

			return true;
		}

		//玩家触地
		if (nodeA->getTag() == PLAYER && nodeB->getTag() == FOOTSTEP)
		{
			log("contactground");
			dynamic_cast<Actor*>(nodeA)->contactGround();
			return true;
		}
		if (nodeB->getTag() == PLAYER && nodeA->getTag() == FOOTSTEP) {
			log("contactground");
			dynamic_cast<Actor*>(nodeB)->contactGround();
			return true;
		}

		//AI触地
		if (nodeA->getTag() == ENEMY && nodeB->getTag() == FOOTSTEP)
		{
			log("contactground");
			dynamic_cast<Actor*>(nodeA)->contactGround();
			return true;
		}
		if (nodeB->getTag() == ENEMY && nodeA->getTag() == FOOTSTEP) {
			log("contactground");
			dynamic_cast<Actor*>(nodeB)->contactGround();
			return true;
		}


		if (nodeA->getTag() == BOX && (nodeB->getTag() == PLAYER || nodeB->getTag() == ENEMY))
		{
			Gun* gun=gunOfBox.front();
			if (nodeB->getTag() == PLAYER)
			{
				_player->setGun(gun);
				canPlayerSet = true;
			}
			else
			{
				_enemy->setGun(gun);
				canEnemySet = true;
			}

			gunOfBox.pop();
			_box->setVisible(false);
			_box->getPhysicsBody()->setCategoryBitmask(BOX_CHANGED_CATEGORY_BITMASK);
			_box->getPhysicsBody()->setCollisionBitmask(BOX_CHANGED_COLLISION_BITMASK);
			_box->getPhysicsBody()->setContactTestBitmask(0);

		}
		if (nodeB->getTag() == BOX && (nodeA->getTag() == PLAYER || nodeA->getTag() == ENEMY))
		{
			Gun* gun = gunOfBox.front();
			if (nodeA->getTag() == PLAYER)
			{
				_player->setGun(gun);
				canPlayerSet = true;
			}
			else
			{
				_enemy->setGun(gun);
				canEnemySet = true;
			}

			gunOfBox.pop();
			_box->setVisible(false);
			_box->getPhysicsBody()->setCategoryBitmask(BOX_CHANGED_CATEGORY_BITMASK);
			_box->getPhysicsBody()->setCollisionBitmask(BOX_CHANGED_COLLISION_BITMASK);
			_box->getPhysicsBody()->setContactTestBitmask(0);
		}
	}
	return true;
}

bool GameScene::responseSeparate(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == ACTOR && nodeB->getTag() == FOOTSTEP)
		{
			log("renew");
			dynamic_cast<Actor*>(nodeA)->renewBitMask();
			if (!dynamic_cast<Actor*>(nodeA)->getIsDowning())
				dynamic_cast<Actor*>(nodeA)->setIsIntheAir(true);
			return true;
		}
		if (nodeB->getTag() == ACTOR && nodeA->getTag() == FOOTSTEP) {
			log("renew");
			dynamic_cast<Actor*>(nodeB)->renewBitMask();
			if (!dynamic_cast<Actor*>(nodeB)->getIsDowning())
				dynamic_cast<Actor*>(nodeB)->setIsIntheAir(true);
			return true;
		}

		//AI触地
		if (nodeA->getTag() == ENEMY && nodeB->getTag() == FOOTSTEP)
		{
			log("renew");
			dynamic_cast<Actor*>(nodeA)->renewBitMask();
			if (!dynamic_cast<Actor*>(nodeA)->getIsDowning())
				dynamic_cast<Actor*>(nodeA)->setIsIntheAir(true);
			return true;
		}
		if (nodeB->getTag() == ENEMY && nodeA->getTag() == FOOTSTEP) {
			log("renew");
			dynamic_cast<Actor*>(nodeB)->renewBitMask();
			if (!dynamic_cast<Actor*>(nodeB)->getIsDowning())
				dynamic_cast<Actor*>(nodeB)->setIsIntheAir(true);
			return true;
		}
	}
	return true;
}
//随机掉落箱子
void GameScene::randomFallGun( Vec2 v)
{
	while (gunOfBox.size() < 3)
	{
		std::string gunType[3] = { HANDGUN_FILENAME,SNIPERGUN_FILENAME ,ARGUN_FILENAME };
		int choose = rand() % 3;
		auto gun = Gun::createGunWithPhysicsBody(gunType[choose]);
		gun->setVisible(true);
		gun->setTag(GUN);
		addChild(gun);
		gun->addBulletWithPhysicsBody("bullet.png");
		gun->setAttribute(gunAttribute[choose]);
		gun->setBullets(gun->getAttribute().maxCapacity);
		gunOfBox.push(gun);
	}
	_box->getPhysicsBody()->setCategoryBitmask(BOX_CATEGORY_BITMASK);
	_box->getPhysicsBody()->setCollisionBitmask(BOX_COLLISION_BITMASK);
	_box->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	_box->setPosition(v);
	_box->setVisible(true);
	return;

}
void GameScene::bulletsReloading(float dt)
{
	log("enter the schedule function ");
	this->_player->getGun()->setBullets(this->_player->getGun()->getAttribute().maxCapacity);

	if (this->_player->getGun()->getIsReloading())
	{
		this->_player->getGun()->setIsReloading(false);
	}
	if (!this->_player->getGun()->getFirable())
	{
		this->_player->getGun()->_firable = true;//记得修改
	}

	return;
}