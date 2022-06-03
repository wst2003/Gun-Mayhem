
#include "cocos2d.h"

#include "winScene.h"

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

	return true;

	return true;

}
void winScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}