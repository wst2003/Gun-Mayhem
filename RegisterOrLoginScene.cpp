#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "RegisterOrLoginScene.h"
#include "SystemHeader.h"

USING_NS_CC;
using namespace  cocos2d::network;

Scene* RegisterOrLoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = RegisterOrLoginScene::create();

	scene->addChild(layer);

	return scene;
}

bool RegisterOrLoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("ReOrLogbg.png");
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(RegisterOrLoginScene::backToMenu, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width-200, 50));
	this->addChild(mnBackMenu, 1);
	/*
	auto backMenuItem = MenuItemFont::create("Back",CC_CALLBACK_1(RegisterOrLoginScene::backToMenu,this));
	backMenuItem->setFontSize(35);
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setPosition(Vec2(visibleSize.width - 100, 50));
	this->addChild(backMenu);
*/
	auto scroll = Sprite::create("Scroll.png");
	scroll->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 70));
	this->addChild(scroll);

	registerEdixBox = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create("chatBg.png"));
	registerEdixBox->setAnchorPoint(Point(0, 0));
	registerEdixBox->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 60));
	registerEdixBox->setPlaceHolder("Please Enter Your ID:");//ռλ�ַ�
	registerEdixBox->setMaxLength(25);
	registerEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	registerEdixBox->setFontColor(Color3B::BLACK);//���������������ɫ
	registerEdixBox->setTag(1);
	this->addChild(registerEdixBox, 1);

	auto registerMenuItem = MenuItemFont::create("Register!", CC_CALLBACK_1(RegisterOrLoginScene::registerCallBack, this));
	registerMenuItem->setFontSize(35);
	auto registerMenu = Menu::create(registerMenuItem, NULL);
	registerMenu->setPosition(Vec2(visibleSize.width/2,420));
	this->addChild(registerMenu, 1);

	registerStatusLabel = Label::createWithTTF(" ","fonts/Arial.ttf",35);
	registerStatusLabel->setPosition(Vec2(visibleSize.width / 2 +350, visibleSize.height / 2 + 80));
	registerStatusLabel->setSystemFontSize(25);
	this->addChild(registerStatusLabel,1);
	
	auto scrollSub = Sprite::create("Scroll.png");
	scrollSub->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 120));
	this->addChild(scrollSub);

	loginEdixBox = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create("chatBg.png"));
	loginEdixBox->setAnchorPoint(Point(0, 0));
	loginEdixBox->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 -130));
	loginEdixBox->setPlaceHolder("Please Enter Your ID:");//ռλ�ַ�
	loginEdixBox->setMaxLength(25);
	loginEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	loginEdixBox->setFontColor(Color3B::BLACK);//���������������ɫ
	loginEdixBox->setTag(1);
	this->addChild(loginEdixBox, 1);

	auto loginMenuItem = MenuItemFont::create("Login!", CC_CALLBACK_1(RegisterOrLoginScene::loginCallBack, this));
	loginMenuItem->setFontSize(35);
	auto loginMenu = Menu::create(loginMenuItem, NULL);
	loginMenu->setPosition(Vec2(visibleSize.width / 2, 230));
	this->addChild(loginMenu, 1);

	loginStatusLabel = Label::createWithTTF(" ", "fonts/Arial.ttf", 35);
	loginStatusLabel->setPosition(Vec2(visibleSize.width / 2 +350, visibleSize.height / 2 - 110));
	loginStatusLabel->setSystemFontSize(25);
	this->addChild(loginStatusLabel, 1);
	Client::getInstance();

	return true;

}
void RegisterOrLoginScene::backToMenu(Ref* r)
{
	Director::getInstance()->popScene();
}
void RegisterOrLoginScene::registerCallBack(Ref* r)
{
	auto ID = registerEdixBox->getText();
	Client::getInstance()->registerIDRequest(ID);
	registerStatusLabel->setString("Loading...");
	this->scheduleOnce(CC_CALLBACK_1(RegisterOrLoginScene::updateRegisterStatus,this), 0.5,"upRe");
}

void RegisterOrLoginScene::updateRegisterStatus(float dt)
{
	if (Client::getIsRegister()) {
		registerStatusLabel->setString("Register Succeed!");
	}
	else {
		registerStatusLabel->setString("Register Failed!\nThis ID has been registered!");
	}
}

void RegisterOrLoginScene::loginCallBack(Ref* r)
{
	auto ID = loginEdixBox->getText();
	Client::getInstance()->loginRequest(ID);
	loginStatusLabel->setString("Loading...");
	this->scheduleOnce(CC_CALLBACK_1(RegisterOrLoginScene::updateLoginStatus, this), 0.5, "upLo");
}

void RegisterOrLoginScene::updateLoginStatus(float dt)
{
	if (Client::getIsLogin()) {
		loginStatusLabel->setString("Login Succeed!");
	}
	else {
		loginStatusLabel->setString("Login Failed!\nThis ID has not been registered!");
	}
}