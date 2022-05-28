#include "cocos2d.h"
#include "HandGun.h"
#include "StartGameScene.h"
#include "Player.h"
#include "Actor.h"
#include "GameScene.h"
#include "AIEnemy.h"
#include "Gun.h"

USING_NS_CC;

PhysicsWorld* GameScene::physicsWorld = nullptr;

//��������
Scene* GameScene::createScene()
{

	auto scene = Scene::createWithPhysics();	//��������
	scene->getPhysicsWorld()->setGravity({ 0,-2000 });
	scene->getPhysicsWorld()->setSubsteps(3.0f);
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

	/*--------------------------------------------------*/
	//����4��ƽ̨
	float pos[4][2] = { visibleSize.width / 4 ,visibleSize.height / 4 ,visibleSize.width * 3 / 4 ,visibleSize.height / 4 ,visibleSize.width / 4,visibleSize.height * 2 / 4 ,visibleSize.width * 3 / 4,visibleSize.height * 2 / 4 };
	for (int i = 0; i < 4; i++)
	{
		auto stoneSprite = Sprite::create("ground.jpg");
		stoneSprite->setScaleX(7.0f);
		stoneSprite->setScaleY(2.0f);
		stoneSprite->setPosition(origin.x + pos[i][0], origin.y + pos[i][1]);
		auto stoneBody = PhysicsBody::createBox(stoneSprite->getContentSize(), PhysicsMaterial(0.1f, 0.0f, 1.0f));
		stoneBody->setDynamic(false);
		stoneSprite->setTag(FOOTSTEP);
		stoneSprite->setPhysicsBody(stoneBody);
		this->addChild(stoneSprite);

		stoneBody->setCategoryBitmask(FOOTSTEP_CATEGORY_BITMASK);
		stoneBody->setCollisionBitmask(FOOTSTEP_COLLISION_BITMASK);
		stoneSprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	}
	/*--------------------------------------------------*/

	// ����һ��������� EdgeBox��һ�����ĵľ��� �൱�ڱ߿�Ч�� 
	auto node = Node::create();
	auto bound = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height * 3 / 2), PhysicsMaterial(0.1f, 0.0f, 1.0f));
	bound->setContactTestBitmask(0xFFFFFFFF);
	bound->setCategoryBitmask(EDGE_CATEGORY_BITMASK);
	bound->setCollisionBitmask(EDGE_COLLISION_BITMASK);
	node->setPhysicsBody(bound);
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(node);

	//
	auto gun = Gun::createGunWithPhysicsBody("369.png");
	gun->setPosition(visibleSize.width / 4 + 300, visibleSize.height);
	gun->setTag(GUN);
	addChild(gun);
	gun->addBulletWithPhysicsBody("bullet.png");

	this->handGun = gun;
	this->arGun = gun;
	this->sniperGun = gun;

	randomFallGun("369.png", { visibleSize.width / 4 + 300, visibleSize.height });

	//����
	auto player = Player::createActorWithPhysicsBody("172.png");
	player->setPosition(visibleSize.width / 4, visibleSize.height + player->getContentSize().height);
	player->setTag(ACTOR);
	addChild(player);
	player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	player->setGun(gun);
	this->_player = player;

	//����
	auto enemy = AIEnemy::createActorWithPhysicsBody("166.png");
	enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height + enemy->getContentSize().height);
	enemy->setTag(ACTOR);
	addChild(enemy);
	enemy->getPhysicsBody()->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	enemy->getPhysicsBody()->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	enemy->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	this->_enemy = enemy;

	//��������
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseDown = [=](EventMouse* event) {
		//��֤����
		if (!_mouseMap[MOUSE_DOWN])
			_player->fire();
		_mouseMap[MOUSE_DOWN] = true;
		_mouseMap[MOUSE_UP] = false;
	};

	myMouseListener->onMouseMove = [=](EventMouse* event) {
		_mouseMap[MOUSE_MOVE] = true;

	};

	myMouseListener->onMouseUp = [=](EventMouse* event) {
		_mouseMap[MOUSE_DOWN] = true;
		_mouseMap[MOUSE_DOWN] = false;

	};

	//���̼�����
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = true;
		if (keyCode == UP_KEY || keyCode == W_KEY)
			_player->jumpUp();
		if (keyCode == DOWN_KEY)
			_player->jumpDown();

	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		_keyMap[keyCode] = false;
	};


	//��ײ������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::responseContact, this);

	//��Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	return true;
}

//
void GameScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (_keyMap[LEFT_KEY] || _keyMap[A_KEY])
		_player->moveOnGround({ -400,_player->getPhysicsBody()->getVelocity().y });
		
	if (_keyMap[RIGHT_KEY] || _keyMap[D_KEY])
		_player->moveOnGround({ 400,_player->getPhysicsBody()->getVelocity().y });

	
	if (_player->getPosition().y < 0)
	{
		_player->setPosition(visibleSize.width / 4, visibleSize.height + _player->getContentSize().height);
		_player->getPhysicsBody()->setVelocity({ 0,0 });
	}
	if (_enemy->getPosition().y < 0)
	{
		_enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height + _enemy->getContentSize().height);
		_enemy->getPhysicsBody()->setVelocity({ 0,0 });
	}

	//���ڵ���������Ծ/������Ծ/�������б�ı���
	if (_player->getPhysicsBody()->getVelocity().y < 0) 
	{
		if (_player->getIsJumping()) {
			_player->setIsJumping(false);

			_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
			_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);


		}
		if (_player->getIsDowning()) 
		{
			_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
			_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);


			_player->setIsDowning(false);
		}
	}
	else if (_player->getPhysicsBody()->getVelocity().y == 0) 
	{
		_player->setJumpTime(0);
		if (_player->getIsJumping())
			_player->setIsJumping(false);
		if (_player->getIsDowning())
			_player->setIsDowning(false);
	}



	return;
}

//
bool GameScene::responseContact(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == BULLET )
		{
			if(nodeB->getTag()!=GUN)
				nodeA->removeFromParentAndCleanup(true);
			if (nodeB->getTag() == ACTOR)
				dynamic_cast<Actor*>(nodeB)->damagedEffect();

			return true;
		}
		if (nodeB->getTag() == BULLET)
		{
			if(nodeA->getTag()!=GUN)
				nodeB->removeFromParentAndCleanup(true);
			if (nodeA->getTag() == ACTOR)
				dynamic_cast<Actor*>(nodeA)->damagedEffect();

			return true;
		}
		if (nodeA->getTag() == ACTOR && nodeB->getTag() == GUN)
		{
			log("666");
//			nodeB->removeFromParentAndCleanup(true);

			switch (rand() % 3 + 1) {
				case 1:
					_player->setGun(handGun);
					break;
				case 2:
					_player->setGun(sniperGun);
					break;
				case 3:
					_player->setGun(arGun);
					break;
			}
			return true;
		}
		if (nodeB->getTag() == ACTOR && nodeA->getTag() == GUN)
		{

			switch (rand() % 3 + 1) {
				case 1:
					_player->setGun(handGun);
					break;
				case 2:
					_player->setGun(sniperGun);
					break;
				case 3:
					_player->setGun(arGun);
					break;
			}
			return true;
		}

		//��Ҵ���
		if (nodeA->getTag() == ACTOR && nodeB->getTag() == FOOTSTEP) 
		{
			log("contactground");
			Vec2 currentVelovity = _player->getPhysicsBody()->getVelocity();
			if (currentVelovity.y <= 0)
				_player->setJumpTime(0);
			if (_player->getIsJumping()) 
			{
				if (currentVelovity.y > 0) 
				{
					_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
					_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
				}
				else 
				{
					_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
					_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
					_player->setIsJumping(false);
				}
			}
			if (_player->getIsDowning()) 
			{
				log("downing");
				_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
				_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);
			}
			else 
			{
				_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
				_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);

				_player->setIsDowning(false);
			}
			return true;
		}
		if (nodeB->getTag() == ACTOR && nodeA->getTag() == FOOTSTEP) {
			log("contactground");
			Vec2 currentVelovity = _player->getPhysicsBody()->getVelocity();
			if (currentVelovity.y <= 0)
				_player->setJumpTime(0);
			if (_player->getIsJumping()) 
			{
				if (currentVelovity.y > 0) 
				{
					_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
					_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);

				}
				else 
				{
					_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
					_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);

					_player->setIsJumping(false);
				}
			}
			if (_player->getIsDowning()) 
			{
				log("downing");
				_player->getPhysicsBody()->setCollisionBitmask(ACTOR_CHANGED_COLLISION_BITMASK);
				_player->getPhysicsBody()->setCategoryBitmask(ACTOR_CHANGED_CATEGORY_BITMASK);

			}
			else 
			{
				_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
				_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);

				_player->setIsDowning(false);
			}

			return true;
		}



	}

	return true;
}


bool GameScene::responseSeparate(PhysicsContact& contact)
{
	//��������һ����棬��������ָ�
	if (_keyMap[W_KEY] == false) 
	{
		log("separate uperground");
		_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
		_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);

		_player->setIsJumping(false);
	}
	//����
	if (_player->getIsDowning()) 
	{
		if (_player->getPhysicsBody()->getVelocity().y < 0) 
		{
			log("separate current ground");
			_player->setIsDowning(false);
			_player->getPhysicsBody()->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
			_player->getPhysicsBody()->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);

		}

	}

	return true;
}

//�����������
void GameScene::randomFallGun(const std::string& filename, Vec2 v)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto gun = Gun::createGunWithPhysicsBody(filename);
	gun->setPosition(v);
	gun->setTag(GUN);
	addChild(gun);
	gun->addBulletWithPhysicsBody("bullet.png");

	this->handGun = gun;
	this->arGun = gun;
	this->sniperGun = gun;
	
}