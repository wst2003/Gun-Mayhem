#pragma once
#ifndef __CHAT_SCENE_H__
#define __CHAT_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class ChatScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void chatCallBack(Ref* r);
	void sendTextCallBack(Ref* r);
	//ͨ����ǩ�����Ƿ���Ӻ��ѳɹ���״̬����
	void updateAddFriendStatus(float dt);

	void updateNewTextFromFriend(float dt);

	ui::EditBox* IDQueryEdixBox;
	Label* addFriendStatusLabel;

	Text* chatText;
	ui::EditBox* sendTextEdixBox;
	
	CREATE_FUNC(ChatScene);
};

#endif