#include<SelectMapScene.h>
#include<cstring>
#include"GameScene.h"
#include "SystemHeader.h"
#include "CreateRoomScene.h"
#include "StartGameScene.h"
USING_NS_CC;

int numberOfMap = 111;
Scene* SelectMapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectMapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SelectMapScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	numberOfMap = 111;
	maxNumberOfMap = 114;
	minNumberOfMap = 111;
	map_Position = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	map_int.insert({ 111,"map_1.png" });
	map_int.insert({ 112,"map_2.png" });
	map_int.insert({ 113,"map_3.png" });
	map_int.insert({ 114,"map_4.png" });
	auto map_1 = Sprite::create("map_1.png");
	map_1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(map_1, 0);

	auto arrowMenuRight = MenuItemImage::create
	("arrow_right.png", "arrow_right.png", "arrow_right.png",
		CC_CALLBACK_1(SelectMapScene::arrowRightCallBack, this));
	auto arrowMenuLeft = MenuItemImage::create
	("arrow_left.png", "arrow_left.png", "arrow_left.png",
		CC_CALLBACK_1(SelectMapScene::arrowLeftCallBack, this));
	auto mnArrowRight = Menu::create(arrowMenuRight, NULL);
	auto mnArrowLeft = Menu::create(arrowMenuLeft, NULL);

	mnArrowRight->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height / 2));
	this->addChild(mnArrowRight, 1);
	mnArrowLeft->setPosition(Vec2(visibleSize.width * 1 / 10, visibleSize.height / 2));
	this->addChild(mnArrowLeft, 1);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(SelectMapScene::backToMenuCallBack, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 30, visibleSize.height * 1 / 8 - 50));
	this->addChild(mnBackMenu, 1);

	auto startButton = MenuItemImage::create
	("start button.png", "start button selected.png", "start button.png",
		CC_CALLBACK_1(SelectMapScene::startCallBack, this));
	auto mnStartMenu = Menu::create(startButton, NULL);
	mnStartMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 1030, visibleSize.height * 1 / 8 - 40));
	this->addChild(mnStartMenu, 1);

	return true;
}

void SelectMapScene::onEnterTransitionDidFinish()
{
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
		if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING)
			UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(BACKGROUNDA));
	}
}

void SelectMapScene::arrowRightCallBack(Ref* r)
{
	if (numberOfMap <= maxNumberOfMap) {
		this->removeChildByTag(numberOfMap);
		if (numberOfMap == 114)
			numberOfMap = 111;
		else
			numberOfMap++;
		auto map = Sprite::create(map_int[numberOfMap].c_str());
		map->setPosition(map_Position);
		this->addChild(map);
	}
}
void SelectMapScene::arrowLeftCallBack(Ref* r)
{
	if (numberOfMap >= minNumberOfMap) {
		this->removeChildByTag(numberOfMap);
		if (numberOfMap == 111)
			numberOfMap = 114;
		else
			numberOfMap--;
		auto map = Sprite::create(map_int[numberOfMap].c_str());
		map->setPosition(map_Position);
		this->addChild(map);
	}
}
void SelectMapScene::backToMenuCallBack(Ref* r)
{
	Director::getInstance()->replaceScene(StartGameScene::createScene());
}
void SelectMapScene::startCallBack(Ref* r)
{
	UserDefault::getInstance()->setBoolForKey(ISPLAYGAME, false);
	UserDefault::getInstance()->setIntegerForKey(MAPID, numberOfMap);
	auto scene = CreateRoomScene::createScene();
	Director::getInstance()->pushScene(scene);
}


