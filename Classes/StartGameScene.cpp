#include "cocos2d.h"
#include "StartGameScene.h"
#include "RegisterOrLoginScene.h"
#include "Client.h"
#include"chatScene.h"
#include"RankingScene.h"
#include"OptionScene.h"
#include"SelectMapScene.h"
#include "SystemHeader.h"
#include<cstring>
USING_NS_CC;
bool isLogin = false;
Scene* StartGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool StartGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("originalbg.png");
	backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround, 0);

	auto startButton = MenuItemImage::create("startgamebutton.png", "startgamebuttonselected.png", "startgamebutton.png",
		CC_CALLBACK_1(StartGameScene::selectMapSceneCallBack, this));
	auto startMn = Menu::create(startButton, NULL);
	startMn->setPosition(Vec2(visibleSize.width * 5 / 7+150, visibleSize.height * 5 / 7));
	this->addChild(startMn);

	auto ROLButton = MenuItemImage::create("ROLbuttonnormal.png", "ROLbuttonselected.png", "ROLbuttonnormal.png",
		CC_CALLBACK_1(StartGameScene::registerOrLoginCallBack, this));
	auto ROLMn = Menu::create(ROLButton, NULL);
	ROLMn->setPosition(Vec2(visibleSize.width * 5 / 7 + 150, visibleSize.height * 5 / 7-90));
	this->addChild(ROLMn);

	auto optionsButton = MenuItemImage::create("optionbuttonnormal.png", "optionbuttonselected.png", "optionbuttonnormal.png",
		CC_CALLBACK_1(StartGameScene::settingsSceneCallBack, this));
	auto optionsMn = Menu::create(optionsButton, NULL);
	optionsMn->setPosition(Vec2(visibleSize.width * 5 / 7 + 150, visibleSize.height * 5 / 7 - 180));
	this->addChild(optionsMn);

	auto chatButton = MenuItemImage::create("chatscenebuttonnormal.png", "chatscenebuttonselected.png", "chatscenebuttonnormal.png",
		CC_CALLBACK_1(StartGameScene::chatSceneCallBack, this));
	auto chatMn = Menu::create(chatButton, NULL);
	chatMn->setPosition(Vec2(visibleSize.width * 5 / 7 + 150, visibleSize.height * 5 / 7 - 270));
	this->addChild(chatMn);

	auto quitButton = MenuItemImage::create("quitbuttonnormal.png", "quitbuttonselected.png", "quitbuttonnormal.png",
		CC_CALLBACK_1(StartGameScene::exitCallBack, this));
	auto quitMn = Menu::create(quitButton, NULL);
	quitMn->setPosition(Vec2(visibleSize.width * 5 / 7 + 150, visibleSize.height * 5 / 7 - 450));
	this->addChild(quitMn);

	auto rankButton = MenuItemImage::create("rankbuttonnormal.png", "rankbuttonnormalselected.png", "rankbuttonnormal.png",
		CC_CALLBACK_1(StartGameScene::rankingSceneCallBack, this));
	auto rankMn = Menu::create(rankButton, NULL);
	rankMn->setPosition(Vec2(visibleSize.width * 5 / 7 + 150, visibleSize.height * 5 / 7 - 360));
	this->addChild(rankMn);
	return true;
}
void StartGameScene::exitCallBack(Ref* r)
{
	Director::getInstance()->end();
}


void StartGameScene::selectMapSceneCallBack(Ref* r)
{
	auto SelectMapScene = SelectMapScene::createScene();
	Director::getInstance()->pushScene(SelectMapScene);
}
void StartGameScene::registerOrLoginCallBack(Ref* r)
{
	auto RegisterOrLoginScene = RegisterOrLoginScene::createScene();
	Director::getInstance()->pushScene(RegisterOrLoginScene);
}
void StartGameScene::chatSceneCallBack(Ref* r)
{
	auto ChatScene = ChatScene::createScene();
	Director::getInstance()->pushScene(ChatScene);
}
void StartGameScene::settingsSceneCallBack(Ref* r)
{
	auto OptionScene = OptionScene::createScene();
	Director::getInstance()->pushScene(OptionScene);
}
void StartGameScene::rankingSceneCallBack(Ref* r)
{
	auto RankingScene = RankingScene::createScene();
	Director::getInstance()->pushScene(RankingScene);
}