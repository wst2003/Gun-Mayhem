
#include "cocos2d.h"
#include"StartGameScene.h"
#include "winScene.h"
#include "SystemHeader.h"
USING_NS_CC;



Scene* winScene::createScene()
{
	auto scene = Scene::create();

	auto layer = winScene::create();

	scene->addChild(layer);

	return scene;
}

bool winScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("YOU WIN ", "fonts/Arial.ttf", 35);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	label->setSystemFontSize(25);
	this->addChild(label);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png", CC_CALLBACK_1(winScene::backToMenu, this));
	auto backToMenu = Menu::create(backButton, NULL);
	backToMenu->setPosition(Vec2(visibleSize.width * 3 / 10, visibleSize.height * 1 / 8));
	this->addChild(backToMenu, 1);

	return true;

}
void winScene::backToMenu(Ref* r)
{
	Director::getInstance()->popScene();
	auto startGameScene = StartGameScene::createScene();
	Director::getInstance()->pushScene(startGameScene);
	return;
}
void winScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}