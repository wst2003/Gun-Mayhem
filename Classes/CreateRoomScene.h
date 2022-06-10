#pragma once
#ifndef __CREATROOM_SCENE_H__
#define __CREATROOM_SCENE_H__
#include"Client.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

#define PosP1 Vec2(300.0f, 630.0f) 
#define PosP2 Vec2(1100.0f, 450.0f) 
#define PosL1 Vec2(460.0f,625.0f)
#define PosL2 Vec2(980.0f,435.0f)

class CreateRoomScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();


	void sendInvitionCallBack(Ref* r);

	void toFirstPlayer(Ref* r);
	void toSecondPlayer(Ref* r);
	//������Ӧ���AI���Ļص�����
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

	//1p��2p�ı���
	Sprite* firstPlayer = Sprite::create("player1.png");
	Sprite* secondPlayer = Sprite::create("player2.png");
	Sprite* aiPlayer_first = Sprite::create("AitowardsRight.png");
	Sprite* aiPlayer_second = Sprite::create("AitowardsLeft.png");

	//�ж�������
	bool myPlayerAdded = false;
	bool friendPlayerAdded = false;
	bool AIPlayerAdded = false;

	//1p��2p�ı�ǩ
	Label* myPlayerLabel;
	Label* friendPlayerLabel;

	//��ʾ��Ϣ���Ƿ��ҵ�����
	Label* findFriendStatusLabel = Label::create();
	static int myNum;
	static int friendNum;
	static int AIorPerson;


};

#endif
