#pragma once
#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class winScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void backToMenu(Ref* r);
	void backCallBack(Ref* r);

	CREATE_FUNC(winScene);
};

#endif