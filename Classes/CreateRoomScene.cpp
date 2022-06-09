#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "CreateRoomScene.h"
#include "GameScene.h"
#include "GameNetScene.h"

USING_NS_CC;
using namespace  cocos2d::network;

int CreateRoomScene::myNum = 0;
int CreateRoomScene::friendNum = 0;
int CreateRoomScene::AIorPerson= 0;
bool CreateRoomScene::isInvited = 0;

Scene* CreateRoomScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CreateRoomScene::create();

	scene->addChild(layer);

	return scene;
}

bool CreateRoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bgForRoom = Sprite::create("roomBg.png");
	bgForRoom->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgForRoom);
	auto P1MenuItem = MenuItemImage::create("plusButton.png", "plusButton.png",
		CC_CALLBACK_1(CreateRoomScene::toFirstPlayer, this));
	//P1MenuItem->setPosition(Vec2(-200, 100));
	auto P1menu = Menu::create(P1MenuItem,NULL);
	P1menu->setPosition(Vec2(300, 640));
	this->addChild(P1menu);
	auto P2MenuItem = MenuItemImage::create("plusButton.png", "plusButton.png",
		CC_CALLBACK_1(CreateRoomScene::toSecondPlayer, this));
	auto P2menu = Menu::create(P2MenuItem, NULL);
	P2menu->setPosition(Vec2(1075, 450));
	this->addChild(P2menu);


	myPlayer->setPosition(Pos1);
	enemyPlayer->setPosition(Pos2);
	myPlayer->setVisible(false);
	enemyPlayer->setVisible(false);
	AIPlayer->setVisible(false);

	myPlayerLabel->setSystemFontSize(50);
	friendPlayerLabel->setSystemFontSize(50);
	myPlayerLabel->setVisible(false);
	friendPlayerLabel->setVisible(false);

	this->addChild(myPlayer, 2);
	this->addChild(enemyPlayer, 2);
    this->addChild(AIPlayer, 2);
	this->addChild(myPlayerLabel, 3);
	this->addChild(friendPlayerLabel, 3);

	auto AIMenuItem = MenuItemFont::create("+AI",
		CC_CALLBACK_1(CreateRoomScene::aiPlayerCallBack, this));
	AIMenuItem->setScaleX(2.0f);
	AIMenuItem->setScaleY(2.0f);


	auto AIMenu = Menu::create(AIMenuItem, NULL);
	AIMenu->setPosition(Vec2(450, 260));
	this->addChild(AIMenu, 2);

	IDQueryEdixBox = ui::EditBox::create(Size(150,50), ui::Scale9Sprite::create("chatBg.png"));
	IDQueryEdixBox->setAnchorPoint(Point(0, 0));
	IDQueryEdixBox->setPosition(Vec2(visibleSize.width * 1 / 9 +745, visibleSize.height * 7 / 10 + 102-495));
	IDQueryEdixBox->setPlaceHolder("Enter ID:");//占位字符
	IDQueryEdixBox->setMaxLength(25);
	IDQueryEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	IDQueryEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	this->addChild(IDQueryEdixBox, 1);

	auto queryMenuItem = MenuItemFont::create("Add",CC_CALLBACK_1(CreateRoomScene::findCallBack,this));
	auto queryMenu = Menu::create(queryMenuItem, NULL);
	queryMenu->setPosition(visibleSize.width * 1 / 9 - 35 + 980, visibleSize.height * 7 / 10 + 140 - 500);
	this->addChild(queryMenu, 2);
	
	findFriendStatusLabel->setPosition(Vec2(800, 400));
	this->addChild(findFriendStatusLabel,1);

	auto backMenuItem = MenuItemFont::create("BACK", CC_CALLBACK_1(CreateRoomScene::backCallBack, this));
	backMenuItem->setPosition(Vec2(-400, -350));
	auto backMenu = Menu::create(backMenuItem, NULL);
	this->addChild(backMenu, 2);

	auto startMenuItem = MenuItemFont::create("Start Game!", CC_CALLBACK_1(CreateRoomScene::startGameCallBack, this));
	startMenuItem->setPosition(Vec2(400, -350));
	auto startMenu = Menu::create(startMenuItem, NULL);
	this->addChild(startMenu, 2);

	this->schedule(CC_CALLBACK_1(CreateRoomScene::updateGetInvited, this), 0.1, "updateGetInvited");

	return true;
}

void CreateRoomScene::toFirstPlayer(Ref* r)
{
	if (myPlayerAdded == false&&!AIPlayerAdded&&!enemyPlayerAdded)
	{
		this->myPlayer->setFlippedX(false);
		this->myPlayer->setVisible(true);
		this->myPlayer->setPosition(Pos1);
		this->enemyPlayer->setVisible(false);
		CreateRoomScene::myNum = 1;
		CreateRoomScene::friendNum = 2;
		this->myPlayerAdded = true;
		this->myPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
		this->myPlayerLabel->setVisible(true);
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);
		this->friendPlayerLabel->setPosition(Pos2+Vec2(-110,0));
		
	}
	else if(!AIPlayerAdded && !enemyPlayerAdded)
	{
		CreateRoomScene::myNum = 1;
		CreateRoomScene::friendNum = 2;
		this->myPlayer->setFlippedX(false);
        this->myPlayer->setPosition(Pos1);
		this->myPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);
		//this->myPlayerLabel->setVisible(true);
		this->friendPlayerLabel->setPosition(Pos2 + Vec2(-110, 0));
	}
	/*
	else
	{
		enemyPlayer->setPosition(Pos1);
		this->enemyPlayer->setVisible(true);
		CreateRoomScene::myNum = 1;
		CreateRoomScene::friendNum = 2;

		this->friendPlayerLabel->setPosition(Vec2(this->enemyPlayer->getPosition()) + Vec2(100, 20));
		this->friendPlayerLabel->setVisible(true);
		this->friendPlayerLabel->setString("2P: " + Client::getInstance()->myID);
		this->friendPlayerLabel->setPosition(Vec2(this->enemyPlayer->getPosition()) + Vec2(100, 20));
	}*/
}

void CreateRoomScene::toSecondPlayer(Ref* r)
{
	if (myPlayerAdded == false && !AIPlayerAdded && !enemyPlayerAdded)
	{
		this->myPlayer->setFlippedX(true);
		this->myPlayer->setVisible(true);
		this->myPlayer->setPosition(Pos2);
		this->enemyPlayer->setVisible(false);
		CreateRoomScene::myNum = 2;
		CreateRoomScene::friendNum = 1;
		this->myPlayerAdded = true;
		this->myPlayerLabel->setPosition(Pos2 + Vec2(-110, 0));
		this->myPlayerLabel->setVisible(true);
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);
		this->friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
	}
	else if (!AIPlayerAdded && !enemyPlayerAdded)
	{
		CreateRoomScene::myNum = 2;
		CreateRoomScene::friendNum = 1;
		this->myPlayer->setFlippedX(true);
		this->myPlayer->setPosition(Pos2);
		this->myPlayerLabel->setPosition(Pos2 + Vec2(-110, 0));
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);
		this->friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
	}
}

void CreateRoomScene::findCallBack(Ref* r)
{
	auto ID = IDQueryEdixBox->getText();
	Client::getInstance()->addFriendRequest(ID);
	findFriendStatusLabel->setString("Loading...");
	this->scheduleOnce(CC_CALLBACK_1(CreateRoomScene::updateFindFriendStatus, this), 0.5, "upAdd");
}

void CreateRoomScene::updateFindFriendStatus(float dt)
{
	/*刷新是否找到好友，若找到则附加一个菜单项在AI下面*/
	if (Client::getInstance()->friendID.length() > 0) {
		findFriendStatusLabel->setString("Friend " + Client::getInstance()->friendID + "\n is found!");
		if(!myPlayerAdded&&!AIPlayerAdded)
		{
			this->myPlayer->setVisible(true);
			this->enemyPlayer->setVisible(true);
			myPlayerAdded = true;
			CreateRoomScene::myNum = 1;
			CreateRoomScene::friendNum = 2;
			this->myPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			this->myPlayerLabel->setString("1P: " + Client::getInstance()->myID);
			this->friendPlayerLabel->setPosition(Pos2 + Vec2(-60, 0));
			this->friendPlayerLabel->setVisible(true);
		}
		else if (myPlayerAdded && !AIPlayerAdded)
		{
			if (this->myPlayer->getPosition() == Pos1)
			{
				this->enemyPlayer->setVisible(true);
				this->friendPlayerLabel->setPosition(Pos2 + Vec2(-60, 0));
			}
			else
			{
				this->enemyPlayer->setFlippedX(true);
				this->enemyPlayer->setPosition(Pos1);
				this->enemyPlayer->setVisible(true);
				this->friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			}
		}
		else if (myPlayerAdded && AIPlayerAdded)
		{
			if (this->AIPlayer->getPosition() == Pos2)
			{
				this->AIPlayer->setVisible(false);
				this->enemyPlayer->setVisible(true);
				this->friendPlayerLabel->setPosition(Pos2 + Vec2(-60, 0));
			}
			else
			{
				this->AIPlayer->setVisible(false);
				this->enemyPlayer->setFlippedX(true);
				this->enemyPlayer->setPosition(Pos1);
				this->enemyPlayer->setVisible(true);
				this->friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			}
			AIPlayerAdded = false;
		}
		enemyPlayerAdded = true;

		//this->friendPlayerLabel->setVisible(true);
		this->friendPlayerLabel->setString(Value(this->friendNum).asString() + "P:" + Client::getInstance()->friendID);
		AIorPerson = 2;
	}
	else {
		findFriendStatusLabel->setString("Friend " + Client::getInstance()->friendID + "\n is not found!");
	}
}
void CreateRoomScene::updateGetInvited(float dt)
{
	if (isInvited) {
	//	this->myPlayer->setVisible(true);
	//	this->enemyPlayer->setVisible(false);
		if (myNum == 1) {

			this->myPlayer->setVisible(true);
			this->enemyPlayer->setVisible(true);

			this->myPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			this->myPlayerLabel->setVisible(true);
			this->myPlayerLabel->setString("1P: " + Client::getInstance()->myID);

			this->friendPlayerLabel->setPosition(Pos2 + Vec2(-60, 0));
			this->friendPlayerLabel->setVisible(true);
			this->friendPlayerLabel->setString("2P: " + Client::getInstance()->friendID);
		}
		else {
			this->myPlayer->setVisible(true);
			this->enemyPlayer->setVisible(true);

			this->friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			this->friendPlayerLabel->setVisible(true);
			this->friendPlayerLabel->setString("1P: " + Client::getInstance()->myID);

			this->myPlayerLabel->setPosition(Pos2 + Vec2(-60, 0));
			this->myPlayerLabel->setVisible(true);
			this->myPlayerLabel->setString("2P: " + Client::getInstance()->friendID);
		}
	}
}
void CreateRoomScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}

void CreateRoomScene::startGameCallBack(Ref* r)
{
	if (AIorPerson == 1) {
		auto scene = GameScene::createScene();
		Director::getInstance()->pushScene(scene);
	}
	if (AIorPerson == 2) {
		auto scene = GameNetScene::createScene();
		Director::getInstance()->pushScene(scene);
	}
	
}
void CreateRoomScene::aiPlayerCallBack(Ref* r)
{
	if (myPlayerAdded && !enemyPlayerAdded)
	{
		if (this->myPlayer->getPosition() == Pos1)
		{
			AIPlayer->setFlippedX(false);
			AIPlayer->setVisible(true);
			AIPlayer->setPosition(Pos2);
			friendPlayerLabel->setVisible(true);
			friendPlayerLabel->setString("AI");
			friendPlayerLabel->setPosition(Pos2+ Vec2(-110, 0));
			AIPlayerAdded = true;

		}
		else
		{
			AIPlayer->setFlippedX(true);
			AIPlayer->setVisible(true);
			AIPlayer->setPosition(Pos1);
			friendPlayerLabel->setVisible(true);
			friendPlayerLabel->setString("AI");
			friendPlayerLabel->setPosition(Pos1 + Vec2(140, 0));
			AIPlayerAdded = true;
		}
		AIorPerson = 1;
	}
}