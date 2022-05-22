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
	void onMouseScroll(Event* event);
	void backToMenu(Ref* r);


	CREATE_FUNC(RankingScene);
};

#endif