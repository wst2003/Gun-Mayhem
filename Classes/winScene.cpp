#include"Client.h"
#include "cocos2d.h"
#include"StartGameScene.h"
#include "winScene.h"
#include "SystemHeader.h"
#include"CreateRoomScene.h"
#include "RankingScene.h"
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

	//Ê¤Àû±³¾°
	auto win = Sprite::create("win.png");
	win->setScaleY(visibleSize.height / win->getContentSize().height);
	win->setPosition(visibleSize / 2);
	addChild(win);


	auto label = Label::createWithTTF("YOU WIN ", "fonts/Arial.ttf", 35);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	label->setSystemFontSize(25);
	this->addChild(label);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png", CC_CALLBACK_1(winScene::backToMenu, this));
	auto backToMenu = Menu::create(backButton, NULL);
	backToMenu->setPosition(Vec2(visibleSize.width * 3 / 10, visibleSize.height * 1 / 8));
	this->addChild(backToMenu, 1);

	if (CreateRoomScene::AIorPerson == 2) {
		auto myScoreLabel = Label::createWithTTF(Client::getInstance()->myID + " +10", "fonts/Arial.ttf", 35);
		auto enemyScoreLabel = Label::createWithTTF(Client::getInstance()->friendID + " -10", "fonts/Arial.ttf", 35);
		myScoreLabel->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2));
		enemyScoreLabel->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 100));
		RankingScene::isMeWin = 1;
	}

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