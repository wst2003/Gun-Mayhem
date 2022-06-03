
#include "cocos2d.h"
#include "loseScene.h"

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

	return true;

}
void loseScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}