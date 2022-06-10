#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "CreateRoomScene.h"
#include "GameScene.h"
USING_NS_CC;
using namespace  cocos2d::network;

int CreateRoomScene::myNum = 0;
int CreateRoomScene::friendNum = 0;
int CreateRoomScene::AIorPerson = 0;
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
	//添加背景
	auto bgForRoom = Sprite::create("roomBG.png");
	bgForRoom->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bgForRoom,0);

	
	auto P1MenuItem = MenuItemImage::create("plusButton.png", "plusButton.png",
		CC_CALLBACK_1(CreateRoomScene::toFirstPlayer, this));
	//P1MenuItem->setPosition(Vec2(-200, 100));
	auto P1menu = Menu::create(P1MenuItem, NULL);
	P1menu->setPosition(Vec2(300, 640));
	this->addChild(P1menu);

	auto P2MenuItem = MenuItemImage::create("plusButton.png", "plusButton.png",
		CC_CALLBACK_1(CreateRoomScene::toSecondPlayer, this));
	auto P2menu = Menu::create(P2MenuItem, NULL);
	P2menu->setPosition(Vec2(1100, 450));
	this->addChild(P2menu);

	firstPlayer->setPosition(PosP1);
	secondPlayer->setPosition(PosP2);
	aiPlayer_first->setPosition(PosP1);
	aiPlayer_second->setPosition(PosP2);
    firstPlayer->setVisible(false);
	secondPlayer->setVisible(false);
	aiPlayer_first->setVisible(false);
	aiPlayer_second->setVisible(false);

    TTFConfig ttfConfig{ "fonts/Marker Felt.ttf",60 };
	myPlayerLabel = Label::createWithTTF(ttfConfig, "");
	friendPlayerLabel = Label::createWithTTF(ttfConfig, "");
	//myPlayerLabel->setSystemFontSize(60);
	myPlayerLabel->setColor(Color3B::BLACK);
	//friendPlayerLabel->setSystemFontSize(60);
	friendPlayerLabel->setColor(Color3B::BLACK);
	//friendPlayerLabel->setSystemFontName("Marker Felt.ttf");
	myPlayerLabel->setVisible(false);
	friendPlayerLabel->setVisible(false);

	this->addChild(firstPlayer, 2);
	this->addChild(secondPlayer, 2);
	this->addChild(aiPlayer_first, 2);
	this->addChild(aiPlayer_second, 2);
	this->addChild(myPlayerLabel, 3);
	this->addChild(friendPlayerLabel, 3);

	auto AIMenuItem = MenuItemFont::create("+AI",
		CC_CALLBACK_1(CreateRoomScene::aiPlayerCallBack, this));
	auto AIMenu = Menu::create(AIMenuItem, NULL);
     AIMenu->setPosition(Vec2(450, 260));
	this->addChild(AIMenu, 2);

	IDQueryEdixBox = ui::EditBox::create(Size(150, 50), ui::Scale9Sprite::create("chatBg.png"));
	IDQueryEdixBox->setAnchorPoint(Point(0, 0));
	IDQueryEdixBox->setPosition(Vec2(visibleSize.width * 1 / 9 + 745, visibleSize.height * 7 / 10 + 102 - 495));
	IDQueryEdixBox->setPlaceHolder("Enter ID:");//占位字符
	IDQueryEdixBox->setMaxLength(25);
	IDQueryEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	IDQueryEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	this->addChild(IDQueryEdixBox, 1);

	auto queryMenuItem = MenuItemFont::create("Add", CC_CALLBACK_1(CreateRoomScene::findCallBack, this));
	queryMenuItem->setColor(Color3B::BLACK);
	auto queryMenu = Menu::create(queryMenuItem, NULL);
	queryMenu->setPosition(visibleSize.width * 1 / 9 - 35 + 985, visibleSize.height * 7 / 10 + 140 - 505);
	this->addChild(queryMenu, 2);

	findFriendStatusLabel->setPosition(Vec2(800, 400));
	this->addChild(findFriendStatusLabel, 1);

	
	auto backMenuItem = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(CreateRoomScene::backCallBack, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
    backMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 30, visibleSize.height * 1 / 8 - 50));
	this->addChild(backMenu, 2);

	auto startMenuItem = MenuItemImage::create
	("start button.png", "start button selected.png", "start button.png",
		CC_CALLBACK_1(CreateRoomScene::startGameCallBack, this));
	auto startMenu = Menu::create(startMenuItem, NULL);
    startMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 1030, visibleSize.height * 1 / 8 -40));
	this->addChild(startMenu, 2);

	this->schedule(CC_CALLBACK_1(CreateRoomScene::updateGetInvited, this), 0.1, "updateGetInvited");

	return true;
}

void CreateRoomScene::toFirstPlayer(Ref* r)
{
	if (!AIPlayerAdded && !friendPlayerAdded)
	{
		this->firstPlayer->setVisible(true);
		this->secondPlayer->setVisible(false);
		myPlayerAdded = true;
		CreateRoomScene::myNum = 1;
		CreateRoomScene::friendNum = 2;

		this->myPlayerLabel->setPosition(PosL1);
		this->myPlayerLabel->setVisible(true);
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);
		this->friendPlayerLabel->setPosition(PosL2);
	}
}

void CreateRoomScene::toSecondPlayer(Ref* r)
{
	if (!AIPlayerAdded && !friendPlayerAdded)
	{
		this->firstPlayer->setVisible(false);
		this->secondPlayer->setVisible(true);
		myPlayerAdded = true;
		CreateRoomScene::myNum = 2;
		CreateRoomScene::friendNum = 1;

		this->myPlayerLabel->setPosition(PosL2);
		this->myPlayerLabel->setVisible(true);
		this->myPlayerLabel->setString("" + Client::getInstance()->myID);

		this->friendPlayerLabel->setPosition(PosL1);
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
		this->firstPlayer->setVisible(true);
		this->secondPlayer->setVisible(true);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto friendMenuItem = MenuItemFont::create(Client::getInstance()->friendID,
			[this](Ref* r) {this->friendPlayerLabel->setVisible(true),
			this->friendPlayerLabel->setString(Value(this->friendNum).asString() + "P:" + Client::getInstance()->friendID)
			, AIorPerson = 2, Client::getInstance()->inviteFriend(Client::getInstance()->friendID); });

		friendMenuItem->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 150));
		auto friendMenu = Menu::create(friendMenuItem, NULL);
		this->addChild(friendMenu, 2);
	}
	else {
		findFriendStatusLabel->setString("Friend " + Client::getInstance()->friendID + "\n is not found!");
	}
}

void CreateRoomScene::updateGetInvited(float dt)
{
	if (isInvited) {
		this->firstPlayer->setVisible(true);
		this->secondPlayer->setVisible(false);
		if (myNum == 1) {
			this->myPlayerLabel->setPosition(Vec2(this->firstPlayer->getPosition()) + Vec2(100, 20));
			this->myPlayerLabel->setVisible(true);
			this->myPlayerLabel->setString("1P: " + Client::getInstance()->myID);

			this->friendPlayerLabel->setPosition(Vec2(this->secondPlayer->getPosition()) + Vec2(100, 20));
			this->friendPlayerLabel->setVisible(true);
			this->friendPlayerLabel->setString("2P: " + Client::getInstance()->friendID);
		}
		else {
			this->myPlayerLabel->setPosition(Vec2(this->secondPlayer->getPosition()) + Vec2(100, 20));
			this->myPlayerLabel->setVisible(true);
			this->myPlayerLabel->setString("2P: " + Client::getInstance()->myID);

			this->friendPlayerLabel->setPosition(Vec2(this->firstPlayer->getPosition()) + Vec2(100, 20));
			this->friendPlayerLabel->setVisible(true);
			this->friendPlayerLabel->setString("1P: " + Client::getInstance()->friendID);
		}
	}
}

void CreateRoomScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}

void CreateRoomScene::startGameCallBack(Ref* r)
{
	if (AIorPerson == 2) {
		Client::getInstance()->startGame("");
	}
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}

void CreateRoomScene::aiPlayerCallBack(Ref* r)
{
	//ai键只有在自己角色已经添加，并且朋友角色未添加,ai未添加的时候起效
	if (myPlayerAdded&&!friendPlayerAdded&&!AIPlayerAdded)
	{
		if (myPlayerLabel->getPosition() == PosL1)
		{
			aiPlayer_second->setVisible(true);
			friendPlayerLabel->setString("AI");
			friendPlayerLabel->setVisible(true);
			AIPlayerAdded = true;
		}
		else
		{
			aiPlayer_first->setVisible(true);
			friendPlayerLabel->setString("AI");
			friendPlayerLabel->setVisible(true);
			AIPlayerAdded = true;
		}
		AIorPerson = 1;
	}
}