
#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "RankingScene.h"

#include<map>

USING_NS_CC;
using namespace  cocos2d::network;

std::vector<Label*> RankingScene::rankingLabels = {};
std::vector<std::string>RankingScene::rankingData = {};
int RankingScene::isMeWin = 0;

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

	auto bg = Sprite::create("backgroundforRK.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(RankingScene::backCallBack, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 8 / 10, visibleSize.height * 1 / 8));
	this->addChild(mnBackMenu, 1);


	//rankingData1 = { "1   600","23   500","345   400" ,"2052","200","110","100","123","456" };

	this->schedule(CC_CALLBACK_1(RankingScene::updateRankingLabels, this), 0.1, "upNewText");

	return true;
}
void RankingScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();
}

void RankingScene::updateRankingLabels(float dt)
{
	rankingData1 = reshapeRankingData(rankingData);

	this->rankingLabels.clear();
	for (auto ranking : this->rankingData1) {
		auto aLabel = Label::create();
		aLabel->setString(ranking);
		this->rankingLabels.push_back(aLabel);
	}
	std::reverse(this->rankingLabels.begin(), this->rankingLabels.end());

	this->rankingLabels[1]->setTextColor(Color4B::BLACK);
	this->rankingLabels[1]->setScaleX(4);
	this->rankingLabels[1]->setScaleY(4);
	this->rankingLabels[1]->setPosition(680, 740);
	this->addChild(rankingLabels[1], 1);

	this->rankingLabels[0]->setTextColor(Color4B::BLACK);
	this->rankingLabels[0]->setScaleX(3.8);
	this->rankingLabels[0]->setScaleY(3.8);
	this->rankingLabels[0]->setPosition(765, 670);
	this->addChild(rankingLabels[0], 1);

	this->rankingLabels[3]->setTextColor(Color4B::BLACK);
	this->rankingLabels[3]->setScaleX(4);
	this->rankingLabels[3]->setScaleY(4);
	this->rankingLabels[3]->setPosition(520, 550);
	this->addChild(rankingLabels[3], 1);

	this->rankingLabels[2]->setTextColor(Color4B::BLACK);
	this->rankingLabels[2]->setScaleX(3.8);
	this->rankingLabels[2]->setScaleY(3.8);
	this->rankingLabels[2]->setPosition(615, 485);
	this->addChild(rankingLabels[2], 1);

	this->rankingLabels[5]->setTextColor(Color4B::BLACK);
	this->rankingLabels[5]->setScaleX(4);
	this->rankingLabels[5]->setScaleY(4);
	this->rankingLabels[5]->setPosition(970, 550);
	this->addChild(rankingLabels[5], 1);

	this->rankingLabels[4]->setTextColor(Color4B::BLACK);
	this->rankingLabels[4]->setScaleX(3.8);
	this->rankingLabels[4]->setScaleY(3.8);
	this->rankingLabels[4]->setPosition(1055, 485);
	this->addChild(rankingLabels[4], 1);

	for (unsigned int i = 0; i < this->rankingLabels.size() - 6; i++) {
		this->rankingLabels[i + 6]->setTextColor(Color4B::BLACK);
		this->rankingLabels[i + 6]->setScaleX(3);
		this->rankingLabels[i + 6]->setScaleY(3);
		this->rankingLabels[i + 6]->setPosition(680, 400 - 105 * i);
		this->addChild(rankingLabels[i + 6], 1);
	}
}

std::vector<std::string> RankingScene::reshapeRankingData(std::vector<std::string>rankingData)
{

	std::vector<std::string> data = {};
	for (unsigned int i = 0; i < (rankingData.size() >= 6 ? 6 : rankingData.size()); i++) {
		auto index = rankingData[i].find_first_of(' ', 0);
		auto index1 = rankingData[i].find_last_of(' ');
		auto ID = rankingData[i].substr(0, index);
		auto score = rankingData[i].substr(index1 + 1, rankingData[i].length() - index1 - 1);
		if (isMeWin == 1 && (ID.compare(Value(Client::getInstance()->myID).asString()) == 0)) {
			score = Value(Value(score).asInt() + 10).asString();
		}
		else if (isMeWin == 2 && (ID.compare(Value(Client::getInstance()->myID).asString()) == 0)) {
			score = Value(Value(score).asInt() - 10).asString();
		}

		if (isMeWin == 1 && (ID.compare(Value(Client::getInstance()->friendID).asString()) == 0)) {
			score = Value(Value(score).asInt() - 10).asString();
		}
		else if (isMeWin == 2 && (ID.compare(Value(Client::getInstance()->friendID).asString()) == 0)) {
			score = Value(Value(score).asInt() + 10).asString();
		}

		if (i < 3) {
			//后面三个
			data.push_back(ID + "   " + score);
		}
		else {
			data.push_back(ID);
			data.push_back(score);
		}
	}
	return data;
}
