#include"OptionScene.h"
USING_NS_CC;

Scene* OptionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool OptionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = Sprite::create("optionScene.png");
	bg->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 1 / 2));
	this->addChild(bg,0);

	onButtonMusic = MenuItemImage::create("ON_able.png", "ON_selected.png", "ON_un.png",
		CC_CALLBACK_1(OptionScene::musicButtonOnCallBack, this));
	offButtonMusic = MenuItemImage::create("OFF_able.png", "OFF_selected.png", "OFF_un.png",
		CC_CALLBACK_1(OptionScene::musicButtonOffCallBack, this));
	//this->addChild(offButtonMusic, 1, 124);
	offButtonMusic->setEnabled(false);
	auto mnMusic = Menu::create(onButtonMusic, offButtonMusic, NULL);
	mnMusic->setPosition(Vec2(visibleSize.width * 1 / 7+70, visibleSize.height * 1 / 8+15));
	mnMusic->alignItemsHorizontally();
	this->addChild(mnMusic,1);

	onButtonSound = MenuItemImage::create("ON_able.png", "ON_selected.png", "ON_un.png",
		CC_CALLBACK_1(OptionScene::soundButtonOnCallBack, this));
	offButtonSound = MenuItemImage::create("OFF_able.png", "OFF_selected.png", "OFF_un.png",
		CC_CALLBACK_1(OptionScene::soundButtonOffCallBack, this));
	//this->addChild(offButtonMusic, 1, 124);
	offButtonSound->setEnabled(false);
	auto mnSound = Menu::create(onButtonSound, offButtonSound, NULL);
	mnSound->setPosition(Vec2(visibleSize.width * 1 / 7 + 260, visibleSize.height * 1 / 8 + 15));
	mnSound->alignItemsHorizontally();
	this->addChild(mnSound, 1);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(OptionScene::backCallBack, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 8 / 10, visibleSize.height * 1 / 8));
	this->addChild(mnBackMenu, 1);
	return true;
}
void OptionScene::musicButtonOnCallBack(Ref* r)
{
	MenuItemImage* onButton = (MenuItemImage*)r;
	offButtonMusic->setEnabled(true);
	onButton->setEnabled(false);
}
void OptionScene::musicButtonOffCallBack(Ref* r)
{

	MenuItemImage* offButton = (MenuItemImage*)r;
	onButtonMusic->setEnabled(true);
	offButton->setEnabled(false);
}
void OptionScene::soundButtonOnCallBack(Ref* r)
{
	MenuItemImage* onButton = (MenuItemImage*)r;
	offButtonSound->setEnabled(true);
	onButton->setEnabled(false);
}
void OptionScene::soundButtonOffCallBack(Ref* r)
{
	MenuItemImage* offButton = (MenuItemImage*)r;
	onButtonSound->setEnabled(true);
	offButton->setEnabled(false);
}
void OptionScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}


