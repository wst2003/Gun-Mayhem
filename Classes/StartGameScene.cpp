#include "cocos2d.h"
#include "StartGameScene.h"
#include "RegisterOrLoginScene.h"
#include "Client.h"
#include"chatScene.h"
#include"RankingScene.h"
#include<cstring>
USING_NS_CC;

bool isLogin = false;
Scene* StartGameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartGameScene::create();

	scene->addChild(layer);

	return scene;
}

void StartGameScene::onEnter()
{
	Layer::onEnter();
	if (Client::getInstance()->getIsLogin()) {
		loginStatusLabel->setString("Login!\n" + Client::getInstance()->myID);
		isLogin = true;
	}
	else {
		loginStatusLabel->setString("Not Logged in!");
	}
}

bool StartGameScene::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto registerOrLoginMenuItem = MenuItemFont::create("Register /\nLogin", CC_CALLBACK_1(StartGameScene::registerOrLoginCallBack, this));
	registerOrLoginMenuItem->setFontSize(35);
	auto registerOrLoginMenu = Menu::create(registerOrLoginMenuItem, NULL);
	registerOrLoginMenu->setPosition(Vec2(100,300));
	this->addChild(registerOrLoginMenu, 1);

	loginStatusLabel = Label::createWithTTF("", "fonts/Arial.ttf",  30);
	loginStatusLabel->setPosition(Vec2(visibleSize.width - 100, 60));
	this->addChild(loginStatusLabel, 1);

	auto chatMenuItem = MenuItemFont::create("Chat", CC_CALLBACK_1(StartGameScene::chatSceneCallBack, this));
	chatMenuItem->setFontSize(35);
	auto chatMenu = Menu::create(chatMenuItem, NULL);
	chatMenu->setPosition(Vec2(260, 300));
	this->addChild(chatMenu, 1);

	auto rankingMenuItem = MenuItemFont::create("Ranking", CC_CALLBACK_1(StartGameScene::rankingSceneCallBack, this));
	rankingMenuItem->setFontSize(35);
	auto rankingMenu = Menu::create(rankingMenuItem, NULL);
	rankingMenu->setPosition(Vec2(380, 300));
	this->addChild(rankingMenu, 1);

	return true;
}

void StartGameScene::registerOrLoginCallBack(Ref* r)
{
	auto registerOrLoginScene = RegisterOrLoginScene::createScene();
	Director::getInstance()->pushScene(registerOrLoginScene);
}

void StartGameScene::chatSceneCallBack(Ref* r)
{
	auto chatScene = ChatScene::createScene();
	Director::getInstance()->pushScene(chatScene);
}

void StartGameScene::rankingSceneCallBack(Ref* r)
{
	if (isLogin) {
		auto rankingScene = RankingScene::createScene();
		Director::getInstance()->pushScene(rankingScene);
	}
}