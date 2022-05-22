#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "RankingScene.h"

USING_NS_CC;
using namespace  cocos2d::network;


Scene* RankingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = RankingScene::create();

	scene->addChild(layer);

	return scene;
}

bool RankingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Client::getInstance()->readRankingRequest(Client::getInstance()->myID);


	return true;

}