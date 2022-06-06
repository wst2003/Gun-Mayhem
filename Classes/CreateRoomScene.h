#pragma once
#ifndef __CREATROOM_SCENE_H__
#define __CREATROOM_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class CreateRoomScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();


	void sendInvitionCallBack(Ref* r);

	void toFirstPlayer(Ref* r) ;
	void toSecondPlayer(Ref* r) ;


	ui::EditBox* IDQueryEdixBox;
	Label* inviteFriendStatusLabel;

	void findCallBack(Ref* r);
	
	static bool isInvited;
	void updateGetInvited(float dt);

	void backCallBack(Ref* r);
	void startGameCallBack(Ref* r);

	void updateFindFriendStatus(float dt);
	CREATE_FUNC(CreateRoomScene);

	//1p、2p的背景
	Sprite* firstPlayer = Sprite::create("elements//1pbg.png");
	Sprite* secondPlayer = Sprite::create("elements//2pbg.png");
	//1p、2p的标签
	Label* myPlayerLabel = Label::create();
	Label* friendPlayerLabel = Label::create();
	//提示信息，是否找到好友
	Label* findFriendStatusLabel=Label::create();
	static int myNum;
	static int friendNum;
	static int AIorPerson;


};

#endif
#pragma once
