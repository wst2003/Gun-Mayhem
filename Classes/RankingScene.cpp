#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "RankingScene.h"

#include<map>

USING_NS_CC;
using namespace  cocos2d::network;

std::vector<Label*> RankingScene::rankingLabels = {};
std::vector<std::string>RankingScene::rankingData = {};

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

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(RankingScene::backCallBack, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 1 / 10 + 30, visibleSize.height * 1 / 8 - 50));
	this->addChild(mnBackMenu, 1);

	/*吴冠亚启用以下注释*/
	//rankingData = { "1   600","23   500","345   400" ,"2052995   200","110    100"};

	this->schedule(CC_CALLBACK_1(RankingScene::updateRankingLabels, this), 0.1, "upNewText");

	return true;

}
void RankingScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}

void RankingScene::updateRankingLabels(float dt)
{
	this->rankingLabels.clear();
	for (auto ranking : this->rankingData) {
		auto aLabel = Label::create();
		aLabel->setString(ranking);
		this->rankingLabels.push_back(aLabel);
	}
	std::reverse(this->rankingLabels.begin(), this->rankingLabels.end());

	for (int i = 0; i < this->rankingLabels.size(); i++) {
		this->rankingLabels[i]->setPosition(200, 500 - 50 * i);
		this->addChild(rankingLabels[i], 1);
	}
}