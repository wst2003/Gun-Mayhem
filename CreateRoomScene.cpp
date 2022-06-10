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

	auto P1MenuItem = MenuItemImage::create("elements//add1p.png", "elements//add1p.png",
		CC_CALLBACK_1(CreateRoomScene::toFirstPlayer, this));
	P1MenuItem->setPosition(Vec2(-200, 100));
	auto P2MenuItem = MenuItemImage::create("elements//add2p.png", "elements//add2p.png",
		CC_CALLBACK_1(CreateRoomScene::toSecondPlayer, this));
	P2MenuItem->setPosition(Vec2(-200, 100 - P1MenuItem->getContentSize().height));

	auto selectPlayerMenu = Menu::create(P1MenuItem, P2MenuItem, NULL);
	this->addChild(selectPlayerMenu, 1);

	firstPlayer->setPosition(Vec2(P1MenuItem->getPosition().x + visibleSize.width / 2, P1MenuItem->getPosition().y + visibleSize.height / 2));
	secondPlayer->setPosition(Vec2(P2MenuItem->getPosition().x + visibleSize.width / 2, P2MenuItem->getPosition().y + visibleSize.height / 2));
	firstPlayer->setVisible(false);
	secondPlayer->setVisible(false);

	myPlayerLabel->setSystemFontSize(30);
	friendPlayerLabel->setSystemFontSize(30);
	myPlayerLabel->setVisible(false);
	friendPlayerLabel->setVisible(false);

	this->addChild(firstPlayer, 2);
	this->addChild(secondPlayer, 2);
	this->addChild(myPlayerLabel, 3);
	this->addChild(friendPlayerLabel, 3);

	auto AIMenuItem = MenuItemFont::create("AI",
		[this](Ref* r) {this->friendPlayerLabel->setVisible(true),
		this->friendPlayerLabel->setString(Value(this->friendNum).asString() + "P: AI"), AIorPerson = 1; });

	AIMenuItem->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100));

	auto AIMenu = Menu::create(AIMenuItem, NULL);
	this->addChild(AIMenu, 2);

	IDQueryEdixBox = ui::EditBox::create(Size(200, 70), ui::Scale9Sprite::create("chatBg.png"));
	IDQueryEdixBox->setAnchorPoint(Point(0, 0));
	IDQueryEdixBox->setPosition(Vec2(visibleSize.width * 1 / 9 - 35, visibleSize.height * 7 / 10 + 102));
	IDQueryEdixBox->setPlaceHolder("Enter ID:");//占位字符
	IDQueryEdixBox->setMaxLength(25);
	IDQueryEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	IDQueryEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	this->addChild(IDQueryEdixBox, 1);

	auto queryMenuItem = MenuItemFont::create("find", CC_CALLBACK_1(CreateRoomScene::findCallBack, this));
	queryMenuItem->setPosition(Vec2(400, 350));
	auto queryMenu = Menu::create(queryMenuItem, NULL);
	this->addChild(queryMenu, 2);

	findFriendStatusLabel->setPosition(Vec2(800, 400));
	this->addChild(findFriendStatusLabel, 1);

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
	this->firstPlayer->setVisible(true);
	this->secondPlayer->setVisible(false);
	CreateRoomScene::myNum = 1;
	CreateRoomScene::friendNum = 2;

	this->myPlayerLabel->setPosition(Vec2(this->firstPlayer->getPosition()) + Vec2(100, 20));
	this->myPlayerLabel->setVisible(true);
	this->myPlayerLabel->setString("1P: " + Client::getInstance()->myID);

	this->friendPlayerLabel->setPosition(Vec2(this->secondPlayer->getPosition()) + Vec2(100, 20));
}

void CreateRoomScene::toSecondPlayer(Ref* r)
{
	this->firstPlayer->setVisible(false);
	this->secondPlayer->setVisible(true);
	CreateRoomScene::myNum = 2;
	CreateRoomScene::friendNum = 1;

	this->myPlayerLabel->setPosition(Vec2(this->secondPlayer->getPosition()) + Vec2(100, 20));
	this->myPlayerLabel->setVisible(true);
	this->myPlayerLabel->setString("2P: " + Client::getInstance()->myID);

	this->friendPlayerLabel->setPosition(Vec2(this->firstPlayer->getPosition()) + Vec2(100, 20));
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