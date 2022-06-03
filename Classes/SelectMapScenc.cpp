#include<SelectMapScene.h>
#include<cstring>
#include"GameScene.h"
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
	this->addChild(map_1,0);

	auto arrowMenuRight = MenuItemImage::create
	("arrow_right.png", "arrow_right.png", "arrow_right.png",
		CC_CALLBACK_1(SelectMapScene::arrowRightCallBack, this));
	auto arrowMenuLeft = MenuItemImage::create
	("arrow_left.png", "arrow_left.png", "arrow_left.png",
		CC_CALLBACK_1(SelectMapScene::arrowLeftCallBack, this));
	auto mnArrowRight = Menu::create(arrowMenuRight,NULL);
	auto mnArrowLeft = Menu::create(arrowMenuLeft, NULL);

    mnArrowRight->setPosition(Vec2(visibleSize.width*9 / 10, visibleSize.height/2));
	this->addChild(mnArrowRight,1);
	mnArrowLeft->setPosition(Vec2(visibleSize.width * 1 / 10, visibleSize.height / 2));
	this->addChild(mnArrowLeft, 1);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(SelectMapScene::backToMenuCallBack, this));
	auto mnBackMenu = Menu::create(backButton,NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 3 / 10, visibleSize.height*1 /8 ));
	this->addChild(mnBackMenu,1);

	auto startButton = MenuItemImage::create
	("start button.png", "start button selected.png", "start button.png",
		CC_CALLBACK_1(SelectMapScene::startCallBack, this));
	auto mnStartMenu = Menu::create(startButton, NULL);
	mnStartMenu->setPosition(Vec2(visibleSize.width * 7 / 10, visibleSize.height * 1 / 8));
	this->addChild(mnStartMenu,1);

	return true;
}
void SelectMapScene::arrowRightCallBack(Ref* r)
{
	if (numberOfMap < maxNumberOfMap) {
		this->removeChildByTag(numberOfMap);
        numberOfMap++;
		auto map = Sprite::create(map_int[numberOfMap].c_str());
		map->setPosition(map_Position);
		this->addChild(map);
	}
}
void SelectMapScene::arrowLeftCallBack(Ref* r)
{
	if (numberOfMap>minNumberOfMap) {
		this->removeChildByTag(numberOfMap);
        numberOfMap--;
		auto map = Sprite::create(map_int[numberOfMap].c_str());
		map->setPosition(map_Position);
		this->addChild(map);
	}
}
void SelectMapScene::backToMenuCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}
void SelectMapScene::startCallBack(Ref* r)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->pushScene(scene);
}


