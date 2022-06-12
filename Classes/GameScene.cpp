#include "cocos2d.h"
#include "StartGameScene.h"
#include "Player.h"
#include "Actor.h"
#include "GameScene.h"
#include "Enemy.h"
#include "Gun.h"
#include"winScene.h"
#include"loseScene.h"
#include "SystemHeader.h"
#include "ui/UIScrollView.h"
#include "CreateRoomScene.h"
#include "OptionScene.h"
#include "PauseScene.h"
#include <fstream>


USING_NS_CC;

//static������ʼ�������ڴ�
PhysicsWorld* GameScene::physicsWorld = nullptr;
Sprite* GameScene::_box = nullptr;
std::string GameScene::info = "";

//̨��λ��
std::vector <std::vector< EdgePosition >> GameScene::mapEdge = {
	{
		{Vec2(660, 290),1332 },
		{Vec2(900, 438), 426},
		{Vec2(400, 510), 413},
		{Vec2(900, 575), 426},
		{Vec2(400, 647), 413}

	},
	{
		{Vec2(675, 140), 1045},
		{Vec2(297, 286), 420},
		{Vec2(1076, 286), 420},
		{Vec2(675, 438), 515},
		{Vec2(297, 577), 420},
		{Vec2(1076, 577), 420},
		{Vec2(675, 720), 1045}
	},
	{
		{Vec2(675, 237), 1350},
		{Vec2(190, 350), 225},
		{Vec2(1150, 350), 225},
		{Vec2(190, 490), 225},
		{Vec2(1150, 490), 225}
	},
	{

		{Vec2(188, 140), 320},
		{Vec2(540, 140), 260},
		{Vec2(880, 140), 260},
		{Vec2(1215, 140), 245},
		{Vec2(865, 280), 178},
		{Vec2(520, 290), 178},
		{Vec2(163, 395), 262},
		{Vec2(687, 400), 180},
		{Vec2(1180, 410), 245},
		{Vec2(400, 510), 182},
		{Vec2(890, 540), 176},
		{Vec2(175, 647), 255},
		{Vec2(610, 647), 272},
		{Vec2(1082, 650), 260}
	}
};

//��ͼ����
std::map<int, std::string> GameScene::mapBGM = {
	{111,BACKGROUNDA},
	{112,BACKGROUNDB},
	{113,BACKGROUNDC},
	{114,BACKGROUNDD}
};

//��������
Scene* GameScene::createScene()
{

	auto scene = Scene::createWithPhysics();	//��������
	scene->getPhysicsWorld()->setGravity({ 0,-2000 });
	scene->getPhysicsWorld()->setSubsteps(10.0f);
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	physicsWorld = scene->getPhysicsWorld();
	auto gameLayer = GameScene::create();
	scene->addChild(gameLayer);

	return scene;
}

bool GameScene::init()
{
	//��������
	if (!Scene::init())
	{
		return false;
	}

	

	//��ӵ�����
	this->scheduleUpdate();

	//�Ӵ���С��ԭ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	initMap();

	//��ͣ��ť
	auto pauseButton = Button::create("pause.png");
	pauseButton->setPosition(Vec2(1350, 900));
	log("%f  %f", pauseButton->getContentSize().width, pauseButton->getContentSize().height);
	pauseButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	pauseButton->addTouchEventListener(CC_CALLBACK_2(GameScene::settingSceneCallBack, this));
	addChild(pauseButton, 3);

	//����
	auto box = Sprite::create("box.png");
	_box = box;
	_box->setVisible(false);
	auto boxBody = PhysicsBody::createBox(_box->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
	_box->addComponent(boxBody);
	boxBody->setDynamic(true);
	boxBody->setRotationEnable(false);
	box->setScale(0.5f);

	box->setTag(BOX);
	addChild(_box);

	//����ӵ�����������
	Gun::addBulletWithPhysicsBody("bullet.png");
	Gun::addBulletWithPhysicsBody("bomb.png");

	//�����������ǹ�ĳ�ʼ��
	auto enemyGun=Gun::createGunWithPhysicsBody(HANDGUN_FILENAME);
	enemyGun->setPosition(visibleSize.width / 4 + 300, visibleSize.height);
	enemyGun->setTag(GUN);
	addChild(enemyGun);
	enemyGun->setAttribute(HANDGUN_ARR);
	enemyGun->setBullets(enemyGun->getAttribute().maxCapacity);

	auto playerGun = Gun::createGunWithPhysicsBody(HANDGUN_FILENAME);
	playerGun->setPosition(visibleSize.width / 4 + 300, visibleSize.height);
	playerGun->setTag(GUN);
	addChild(playerGun);
	playerGun->setAttribute(HANDGUN_ARR);
	playerGun->setBullets(playerGun->getAttribute().maxCapacity);

	//�������һ��ǹ
	randomFallGun();

	//���ﴴ��
	auto player = Player::createWithActor(Actor::createActorWithPhysicsBody("playerA.png"));
	if (CreateRoomScene::AIorPerson == 1) 
	{
		player->setPosition(visibleSize.width / 4, visibleSize.height + player->getContentSize().height);
	}
	else 
	{
		if (CreateRoomScene::myNum == 1) 
		{
			player->setPosition(visibleSize.width / 4, visibleSize.height + player->getContentSize().height);
		}
		else 
		{
			player->setPosition(visibleSize.width * 3 / 4, visibleSize.height + player->getContentSize().height);
		}
	}
	if (CreateRoomScene::AIorPerson == 1) {
		player->setRemainingLive(5);
	}
	else 
	{
		player->setRemainingLive(6);
	}
	addChild(player);
	player->setGun(playerGun);
	player->setID(0);     //����ID
	player->initActor();
	this->_player = player;
	player->getBloodBar()->setColor(Color3B::GREEN);

	//���˴���
	auto enemy = Enemy::createWithActor(Actor::createActorWithPhysicsBody("playerB.png"));
	if (CreateRoomScene::AIorPerson == 1) 
	{
		enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height + enemy->getContentSize().height);
	}
	else 
	{
		if (CreateRoomScene::myNum == 1) 
		{
			enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height + enemy->getContentSize().height);
		}
		else 
		{
			enemy->setPosition(visibleSize.width / 4, visibleSize.height + enemy->getContentSize().height);
		}
	}
	if (CreateRoomScene::AIorPerson == 1) {
		enemy->setRemainingLive(5);
	}
	else {
		enemy->setRemainingLive(6);
	}
	addChild(enemy);
	this->_enemy = enemy;
	enemy->setGun(enemyGun);
	enemy->setID(3);       //����ID
	enemy->initActor();
	enemy->getBloodBar()->setColor(Color3B::RED);

	//���︽����Ʒ����������
	createBrand(_enemy);
	createBrand(_player);
	_player->getPhysicsBody()->setVelocityLimit(800.0f);
	_enemy->getPhysicsBody()->setVelocityLimit(800.0f);

	//��������
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseDown = [=](EventMouse* event) {
		if (!(event->getCursorX() >= visibleSize.width - 64 && event->getCursorX() <= visibleSize.width && event->getCursorY() <= visibleSize.height && event->getCursorY() >= visibleSize.height - 64))
		{
			_mouseMap[MOUSE_DOWN] = true;
			_mouseMap[MOUSE_UP] = false;
		}
	};
	//��һ��reloadiing�ĺ���
	myMouseListener->onMouseMove = [=](EventMouse* event) {
		_mouseMap[MOUSE_MOVE] = true;

	};

	myMouseListener->onMouseUp = [=](EventMouse* event) {
		_mouseMap[MOUSE_DOWN] = false;
		_mouseMap[MOUSE_UP] = true;
	};

	//���̼�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = true;
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = false;
	};


	//��ײ������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::responseContact, this);
	contactListener->onContactSeparate=CC_CALLBACK_1(GameScene::responseSeparate, this);

	//��Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this); 

	return true;
}

//��ʼ����ͼ����
void GameScene::initMap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//����ƽ̨
	switch (UserDefault::getInstance()->getIntegerForKey(MAPID)) {
		case MAP1:
			map = Sprite::create("map1.png");
			break;
		case MAP2:
			map = Sprite::create("map2.png");
			break;
		case MAP3:
			map = Sprite::create("map3.png");
			break;
		case MAP4:
			map = Sprite::create("map4.png");
			break;
	}
	for (EdgePosition const& i : mapEdge[UserDefault::getInstance()->getIntegerForKey(MAPID) - MAP1])
		createGround(i.edgePos, i.edgeLength);

	//���� map ��С
	map->setScaleX(visibleSize.width / map->getContentSize().width);
	map->setScaleY(visibleSize.height / map->getContentSize().height);
	map->setPosition(visibleSize / 2);

	this->addChild(map);

	//����Ѫ������
	auto bloodBackGroundPlayer = Sprite::create("bloodBarBG.png");
	bloodBackGroundPlayer->setPosition(Vec2(visibleSize.width * (2 * 0 + 1) / 8, visibleSize.height * 1 / 8 - 80));
	this->addChild(bloodBackGroundPlayer);

	auto bloodBackGroundEnemy = Sprite::create("bloodBarBG.png");
	bloodBackGroundEnemy->setPosition(Vec2(visibleSize.width * (2 * 3 + 1) / 8, visibleSize.height * 1 / 8 - 80));
	this->addChild(bloodBackGroundEnemy);


}

//����̨��λ��
void GameScene::createGround(Vec2 pos, float length)
{
	//��̨ͨ�׵Ĵ���
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

	//����Ĵ������ʼ��
	auto spaySprite = Sprite::create("ground.jpg");
	auto spayEdge = PhysicsBody::createBox(stoneSprite->getContentSize());
	spaySprite->setPhysicsBody(spayEdge);
	spayEdge->setDynamic(false);
	spaySprite->setPosition(Vec2(pos.x, pos.y - 10.0f));
	spaySprite->setScaleX(length / stoneSprite->getContentSize().width * 1.2);
	spaySprite->setScaleY(0.1f);
	spayEdge->setCategoryBitmask(0xFFFFFFFF);
	spayEdge->setCollisionBitmask(0);
	spayEdge->setContactTestBitmask(0xFFFFFFFF);
	spaySprite->setTag(SPAY);
	spaySprite->setVisible(false);
	this->addChild(spaySprite);

	return;
}

//�������Ա�ǩ
void GameScene::createBrand(Actor* actor)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	addChild(actor->nameLabel, 2, BRAND_NAME + actor->getID());
	addChild(actor->livesLeftLabel, 2, BRAND_LIFELEFT + actor->getID());
	actor->addChild(actor->bulletsLeftLabel, 2, BRAND_BULLETLEFT + actor->getID());
	addChild(actor->getBloodBar(), 2, BRAND_BLOODPERCENT + actor->getID());
	return;
}

//��������˵Ļ״̬����
void GameScene::update(float dt)
{
	//�������Ա�ǩ
	_player->renewBrand();
	_enemy->renewBrand();

	//��ǹ����
	clock_t now = clock();
	if (now - _lastTime > 10000.0f)
	{
		randomFallGun();
		_lastTime = now;

	}

	//ˢ��ǹ��״̬
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

	//�����˶�
	_player->actByKeyBoard(_keyMap);
	_player->actByMouse(_mouseMap);

	//��������
	_player->reLive(true);
	_enemy->reLive();

	//��������˵���ײ�����޸�
	_player->changeBitMask();
	_enemy->changeBitMask();

	//������������
	_player->setActorInformation();
	_enemy->getPlayerInformation(_player);

	//���˵ķ�Ӧ
	if (CreateRoomScene::AIorPerson == 1)
		_enemy->actByAI();
	else
		_enemy->actByFriend(info);

	
	return;
}

//��Ӧ��ײ�Ӵ�
bool GameScene::responseContact(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();


	if (nodeA && nodeB)
	{
		//�����ĽӴ�
		if ((nodeA->getTag() == SPAY && nodeB->getTag() == ACTOR) ||
			(nodeB->getTag() == SPAY && nodeA->getTag() == ACTOR))
		{
			playerContectTimes++;
			_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
			log("spay works");
			return true;
		}
		if ((nodeA->getTag() == SPAY && nodeB->getTag() == ENEMY) ||
			(nodeB->getTag() == SPAY && nodeA->getTag() == ENEMY))
		{
			enemyContectTimes++;
			_enemy->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			_enemy->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
			log("spay works");
			return true;
		}

		//�ӵ�����ײ
		if (nodeA->getTag() <= BULLET)
		{
			int damage = nodeA->getTag();
			bool can = true;
			if (nodeB->getTag() != GUN)
				if ((nodeA->getTag() == 53 || nodeA->getTag() == 50) && nodeB->getTag() > 100)
				{
					if (nodeB->getTag() == SPAY)
						return true;
					can = false;
					nodeA->setVisible(false);
					auto emitter = ParticleExplosion::create();
					emitter->setLife(0.3f);
					emitter->setLifeVar(0.3f);
					emitter->setPosition(nodeA->getPosition());
					emitter->setStartColor(Color4F::YELLOW);
					emitter->setEndColor(Color4F::YELLOW);
					this->getScene()->addChild(emitter);

					auto enemyPosition = _enemy->getPosition();
					auto playerPosition = _player->getPosition();
					auto enemyDown = enemyPosition.y - _enemy->getContentSize().height / 2;
					auto enemyUp = enemyPosition.y + _enemy->getContentSize().height / 2;
					auto playerDown = playerPosition.y - _player->getContentSize().height / 2;
					auto playerUp = playerPosition.y + _player->getContentSize().height / 2;
					if ( enemyPosition.x<nodeA->getPosition().x + 200 && enemyPosition.x>nodeA->getPosition().x - 200 && nodeA->getPosition().y >= enemyDown && nodeA->getPosition().y <= enemyUp)
					{
						_enemy->damagedEffect(nodeA->getTag() == 50 ? 50 : 0);
						_enemy->getPhysicsBody()->setVelocity({ (enemyPosition.x < nodeA->getPosition().x ? -800.0f : 800.0f), _enemy->getPhysicsBody()->getVelocity().y });
					}
					if (playerPosition.x<nodeA->getPosition().x + 200 && playerPosition.x>nodeA->getPosition().x - 200 && nodeA->getPosition().y >= playerDown && nodeA->getPosition().y <= playerUp)
					{
						_player->damagedEffect(nodeA->getTag() == 53 ? 50 : 0);
						_player->getPhysicsBody()->setVelocity({ (playerPosition.x < nodeA->getPosition().x ? -800.0f : 800.0f), _player->getPhysicsBody()->getVelocity().y });
					}

				}


			nodeA->removeFromParentAndCleanup(true);
			if ((nodeB->getTag() == PLAYER || nodeB->getTag() == ENEMY) && can)
			{
				Actor* actor = dynamic_cast<Actor*>(nodeB);
				actor->damagedEffect(damage);
			}

			return true;
		}
		if (nodeB->getTag() <= BULLET)
		{
			bool can = true;
			int damage = nodeB->getTag();

			if (nodeA->getTag() != GUN)
				if ((nodeB->getTag() == 53 || nodeB->getTag() == 50) && nodeA->getTag() > 100 )
				{
					if (nodeA->getTag() == SPAY)
						return true;
					can = false;
					nodeB->setVisible(false);
					auto emitter = ParticleExplosion::create();
					emitter->setLife(0.3f);
					emitter->setLifeVar(0.3f);
					emitter->setPosition(nodeB->getPosition());
					emitter->setStartColor(Color4F::YELLOW);
					emitter->setEndColor(Color4F::YELLOW);
					this->getScene()->addChild(emitter);

					auto enemyPosition = _enemy->getPosition();
					auto playerPosition = _player->getPosition();
					auto enemyDown = enemyPosition.y - _enemy->getContentSize().height / 2;
					auto enemyUp= enemyPosition.y + _enemy->getContentSize().height / 2;
					auto playerDown= playerPosition.y - _player->getContentSize().height / 2;
					auto playerUp = playerPosition.y + _player->getContentSize().height / 2;
					if ( enemyPosition.x<nodeB->getPosition().x + 200 && enemyPosition.x>nodeB->getPosition().x - 200 && nodeB->getPosition().y >= enemyDown && nodeB->getPosition().y <= enemyUp)
					{
						_enemy->damagedEffect(nodeB->getTag() == 50 ? 50 : 0);
						_enemy->getPhysicsBody()->setVelocity({ (enemyPosition.x < nodeB->getPosition().x ? -800.0f : 800.0f), _enemy->getPhysicsBody()->getVelocity().y });
					}
					if (playerPosition.x<nodeB->getPosition().x + 200 && playerPosition.x>nodeB->getPosition().x - 200 && nodeB->getPosition().y >= playerDown && nodeB->getPosition().y <= playerUp)
					{
						_player->damagedEffect(nodeB->getTag() == 53 ? 50 : 0);
						_player->getPhysicsBody()->setVelocity({ (playerPosition.x < nodeB->getPosition().x ? -800.0f : 800.0f), _player->getPhysicsBody()->getVelocity().y });
					}
				}

			nodeB->removeFromParentAndCleanup(true);
			if ((nodeA->getTag() == PLAYER || nodeA->getTag() == ENEMY) && can)
			{
				Actor* actor = dynamic_cast<Actor*>(nodeA);
				actor->damagedEffect(damage);
			}
			return true;
		}

		//AI����
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

		//��ǹ����
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

//�����ײ���뺯��
bool GameScene::responseSeparate(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		//�������ķ���
		if (nodeA->getTag() == SPAY && nodeB->getTag() == ACTOR ||
			(nodeB->getTag() == SPAY && nodeA->getTag() == ACTOR))
		{
			playerContectTimes--;
			if (playerContectTimes)
				return true;
			_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
			_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
			log("spay works");
			return true;
		}

		if (nodeA->getTag() == SPAY && nodeB->getTag() == ENEMY ||
			(nodeB->getTag() == SPAY && nodeA->getTag() == ENEMY))
		{
			enemyContectTimes--;
			if (enemyContectTimes)
				return true;
			_enemy->getPhysicsBody()->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
			_enemy->getPhysicsBody()->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
			log("spay works");
			return true;
		}

		//AI����
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

//�����������
void GameScene::randomFallGun()
{
	int floor = 0;
	int mapId = UserDefault::getInstance()->getIntegerForKey(MAPID) - MAP1;

	//α�������ǹ
	circleRandom %= 30;
	floor = randomNum[circleRandom++] % (mapEdge[mapId].size());
	Vec2 v = { mapEdge[mapId][floor].edgePos.x - mapEdge[mapId][floor].edgeLength / 4, mapEdge[mapId][floor].edgePos.y + _box->getContentSize().height / 2 };
	
	//�ǹ֧�����еĿ�ȱ
	while (gunOfBox.size() < 4)
	{
		std::string gunType[4] = { HANDGUN_FILENAME,SNIPERGUN_FILENAME ,ARGUN_FILENAME,BOMB_FILENAME };
		int choose = gunTypes[gunChoose++];
		gunChoose %= static_cast<int>(gunTypes.size());
		auto gun = Gun::createGunWithPhysicsBody(gunType[choose]);
		gun->setVisible(true);
		gun->setTag(GUN);
		addChild(gun);
		
		gun->setAttribute(gunAttribute[choose]);
		gun->setBullets(gun->getAttribute().maxCapacity);
		gunOfBox.push(gun);
	}

	//���ú�������
	_box->getPhysicsBody()->setCategoryBitmask(BOX_CATEGORY_BITMASK);
	_box->getPhysicsBody()->setCollisionBitmask(BOX_COLLISION_BITMASK);
	_box->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	_box->setPosition(v);
	_box->setVisible(true);
	return;

}

//Ԥ�����ӵ�
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
		this->_player->getGun()->_firable = true;//�ǵ��޸�
	}

	return;
}


//���������л�
void GameScene::onEnterTransitionDidFinish()
{
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
		//��һ�ν�����Ϸ�������л�BGM
		if (AudioEngine::getState(audioId) == AudioEngine::AudioState::PLAYING) {
			//��ISPLAYGAME���ó�true����ֻ֤�е�һ�ν���ʱ�Ქ�ŵ�ǰ��ͼ����
			if (!UserDefault::getInstance()->getBoolForKey(ISPLAYGAME)) {
				AudioEngine::stop(UserDefault::getInstance()->getIntegerForKey(MUSICID));
				UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(mapBGM[UserDefault::getInstance()->getIntegerForKey(MAPID)], true));
				AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
				UserDefault::getInstance()->setBoolForKey(ISPLAYGAME, true);
			}
		}
		else {
			UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(mapBGM[UserDefault::getInstance()->getIntegerForKey(MAPID)], true));
			AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
		}
	}
	return;
}

//��ͣ��ť�Ļص�����
void GameScene::settingSceneCallBack(Ref* ref, Button::TouchEventType type)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	
	if (type == Button::TouchEventType::ENDED) 
	{
		//������Ϸ
		auto OptionScene = PauseScene::createScene(renderTexture);
		Director::getInstance()->pushScene(OptionScene);
	}
}

//���ý��淵��ʱ�����Գ�ʼ��
void GameScene::onExit()
{
	Scene::onExit();

	//������������
	_keyMap.clear();
	_mouseMap.clear();

	//����ǹ֧״̬����
	_player->setGun(_player->getGun());
	_enemy->setGun(_enemy->getGun());
	return;
}
