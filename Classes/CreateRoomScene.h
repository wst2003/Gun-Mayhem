#pragma once
#ifndef __CREATROOM_SCENE_H__
#define __CREATROOM_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

#define Pos1 Vec2(300, 630) 
#define Pos2 Vec2(1080, 450) 


class CreateRoomScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();


	void sendInvitionCallBack(Ref* r);

	void toFirstPlayer(Ref* r) ;
	void toSecondPlayer(Ref* r) ;
	void aiPlayerCallBack(Ref* r);

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
	Sprite* myPlayer = Sprite::create("player1.png");
	Sprite* enemyPlayer = Sprite::create("player2.png");
	Sprite* AIPlayer=Sprite::create("AI.png");
	bool myPlayerAdded = false;
	bool enemyPlayerAdded = false;
	bool AIPlayerAdded = false;
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
