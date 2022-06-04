
#include "cocos2d.h"
#include "loseScene.h"
#include "StartGameScene.h"
#include "SystemHeader.h"
USING_NS_CC;


Scene*loseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = loseScene::create();

	scene->addChild(layer);

	return scene;
}

bool loseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("YOU LOSE ", "fonts/Arial.ttf", 35);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 ));
	label->setSystemFontSize(25);
	this->addChild(label);


	auto backButton = MenuItemImage::create("back.png", "back_selected.png","back.png", CC_CALLBACK_1(loseScene::backToMenu, this));
	auto backToMenu = Menu::create(backButton, NULL);
	backToMenu->setPosition(Vec2(visibleSize.width * 3 / 10, visibleSize.height * 1 / 8));
	this->addChild(backToMenu, 1);
	return true;

}
void loseScene::backToMenu(Ref* r)
{
	Director::getInstance()->popScene();
	auto startGameScene = StartGameScene::createScene();
	Director::getInstance()->pushScene(startGameScene);
	return;
}
void loseScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}