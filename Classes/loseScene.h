#pragma once
#ifndef __LOSE_SCENE_H__
#define __LOSE_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class loseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	static std::vector<Label*> rankingLabels;
	void onMouseScroll(Event* event);
	void backToMenu(Ref* r);
	void backCallBack(Ref* r);

	CREATE_FUNC(loseScene);
};

#endif