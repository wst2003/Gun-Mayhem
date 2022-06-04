#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace cocos2d::ui;

class RegisterOrLoginScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	void backToMenu(Ref* r);
	//通过标签更新是否注册成功的状态函数
	void updateRegisterStatus(float dt);
	//提交注册请求的回调函数
	void registerCallBack(Ref* r);
	//通过标签更新是否登录成功的状态函数
	void updateLoginStatus(float dt);
	//提交登录请求的回调函数
	void loginCallBack(Ref* r);
	//输入框(register)
	ui::EditBox* registerEdixBox;
	//输入框(login)
	ui::EditBox* loginEdixBox;
	//标签，显示是否注册成功
	Label* registerStatusLabel;
	//标签，显示是否登录成功
	Label*loginStatusLabel;
	CREATE_FUNC(RegisterOrLoginScene);
};
#endif
