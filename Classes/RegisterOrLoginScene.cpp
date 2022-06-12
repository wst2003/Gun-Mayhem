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

	auto bg = Sprite::create("ROLBackGround.png");
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(RegisterOrLoginScene::backToMenu, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 30, visibleSize.height * 1 / 8 - 50));
	this->addChild(mnBackMenu, 1);
	/*
	auto backMenuItem = MenuItemFont::create("Back",CC_CALLBACK_1(RegisterOrLoginScene::backToMenu,this));
	backMenuItem->setFontSize(35);
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setPosition(Vec2(visibleSize.width - 100, 50));
	this->addChild(backMenu);
*/


	registerEdixBox = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create("chatBg.png"));
	registerEdixBox->setAnchorPoint(Point(0, 0));
	registerEdixBox->setPosition(Vec2(visibleSize.width / 2 - 450, visibleSize.height / 2 + 70));
	registerEdixBox->setPlaceHolder("Please Enter Your ID:");//占位字符
	registerEdixBox->setMaxLength(25);
	registerEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	registerEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	registerEdixBox->setTag(1);
	this->addChild(registerEdixBox, 1);

	auto registerMenuItem = MenuItemImage::create("registerButtonNormal.png", "registerButtonSelected.png", CC_CALLBACK_1(RegisterOrLoginScene::registerCallBack, this));
	//registerMenuItem->setFontSize(35);
	auto registerMenu = Menu::create(registerMenuItem, NULL);
	registerMenu->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 96));
	this->addChild(registerMenu, 1);
	TTFConfig ttfConfig{ "fonts/Marker Felt.ttf",35 };
	registerStatusLabel = Label::createWithTTF(ttfConfig, "");
	registerStatusLabel->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 30));
	registerStatusLabel->setSystemFontSize(25);
	registerStatusLabel->setColor(Color3B::BLACK);
	this->addChild(registerStatusLabel, 1);


	loginEdixBox = ui::EditBox::create(Size(400, 50), ui::Scale9Sprite::create("chatBg.png"));
	loginEdixBox->setAnchorPoint(Point(0, 0));
	loginEdixBox->setPosition(Vec2(visibleSize.width / 2 - 350, visibleSize.height / 2 - 125));
	loginEdixBox->setPlaceHolder("Please Enter Your ID:");//占位字符
	loginEdixBox->setMaxLength(25);
	loginEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	loginEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	loginEdixBox->setTag(1);
	this->addChild(loginEdixBox, 1);

	auto loginMenuItem = MenuItemImage::create("loginButtonNormal.png", "loginButtonSelected.png", CC_CALLBACK_1(RegisterOrLoginScene::loginCallBack, this));
	//loginMenuItem->setFontSize(35);
	auto loginMenu = Menu::create(loginMenuItem, NULL);
	loginMenu->setPosition(Vec2(visibleSize.width / 2 + 240, visibleSize.height / 2 - 92));
	this->addChild(loginMenu, 1);

	loginStatusLabel = Label::createWithTTF(ttfConfig, "");
	loginStatusLabel->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 - 170));
	loginStatusLabel->setSystemFontSize(25);
	loginStatusLabel->setColor(Color3B::BLACK);
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
	this->scheduleOnce(CC_CALLBACK_1(RegisterOrLoginScene::updateRegisterStatus, this), 0.5, "upRe");
}

void RegisterOrLoginScene::updateRegisterStatus(float dt)
{
	if (!Client::getIsServerConnected()) {
		registerStatusLabel->setString("Server is not\n connected!");
		return;
	}
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
	if (!Client::getIsServerConnected()) {
		loginStatusLabel->setString("Server is not\n connected!");
		return;
	}
	if (Client::getIsLogin()) {
		loginStatusLabel->setString("Login Succeed!");
	}
	else {
		loginStatusLabel->setString("Login Failed!\nThis ID has not been registered!");
	}
}