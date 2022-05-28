#include "cocos2d.h"
#include "StartGameScene.h"
#include "HandGun.h"
#include "CharEncodingConvert.h"
#include "GameScene.h"
USING_NS_CC;

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

	auto selectMapSceneMenuItem = MenuItemFont::create(a2u("单机游戏"), 
		CC_CALLBACK_1(StartGameScene::selectMapSceneCallBack, this));
	auto settingSceneMenuItem = MenuItemFont::create(a2u("设置"), 
		CC_CALLBACK_1(StartGameScene::settingsSceneCallBack, this));
	auto exitCallBackMenuItem=MenuItemFont::create(a2u("退出游戏"), 
		CC_CALLBACK_1(StartGameScene::exitCallBack, this));

	selectMapSceneMenuItem->setPosition(visibleSize.width / 2, visibleSize.height * 5 / 6);
	settingSceneMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	exitCallBackMenuItem->setPosition(visibleSize.width / 2, visibleSize.height / 6);
	
	auto menu = Menu::create(selectMapSceneMenuItem, settingSceneMenuItem, exitCallBackMenuItem, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);
	return true;
}

//
void StartGameScene::selectMapSceneCallBack(Ref* r)
{
	//创造要到达的新场景及动画
	Scene* divisionScene = GameScene::createScene();
	TransitionJumpZoom* divisionTran = TransitionJumpZoom::create(1.0f, divisionScene);

	Director::getInstance()->replaceScene(divisionTran);
}

//
void StartGameScene::settingsSceneCallBack(Ref* r)
{

}

//
void StartGameScene::exitCallBack(Ref* r)
{
	Director::getInstance()->end();
}

//
void StartGameScene::NetSceneCallBack(Ref* r)
{

}
