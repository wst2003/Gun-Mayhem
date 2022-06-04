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
	//ͨ����ǩ�����Ƿ�ע��ɹ���״̬����
	void updateRegisterStatus(float dt);
	//�ύע������Ļص�����
	void registerCallBack(Ref* r);
	//ͨ����ǩ�����Ƿ��¼�ɹ���״̬����
	void updateLoginStatus(float dt);
	//�ύ��¼����Ļص�����
	void loginCallBack(Ref* r);
	//�����(register)
	ui::EditBox* registerEdixBox;
	//�����(login)
	ui::EditBox* loginEdixBox;
	//��ǩ����ʾ�Ƿ�ע��ɹ�
	Label* registerStatusLabel;
	//��ǩ����ʾ�Ƿ��¼�ɹ�
	Label*loginStatusLabel;
	CREATE_FUNC(RegisterOrLoginScene);
};
#endif
