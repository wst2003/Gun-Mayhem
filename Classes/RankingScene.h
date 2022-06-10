#pragma once
#ifndef __RANKING_SCENE_H__
#define __RANKING_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class RankingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	static std::vector<Label*> rankingLabels;
	static std::vector<std::string>rankingData;
	std::vector<std::string>rankingData1;
	void updateRankingLabels(float dt);

	void backCallBack(Ref* r);

	static int isMeWin;
	CREATE_FUNC(RankingScene);
private:
	std::vector<std::string> reshapeRankingData(std::vector<std::string>rankingData);
};


#endif