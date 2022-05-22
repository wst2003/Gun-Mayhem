#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
USING_NS_CC;

class Player :public Actor
{
public:
	virtual void fire() ;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() ;//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���
public:
	//��Щ��������������update����,���ǽ�����Actor��fire��jump�Ⱥ���
	ActorInformation sendPlayerInformation();	//������ҵ�������Ϣ
	ActorInformation actByKeyBoard(std::map<EventKeyboard::KeyCode, bool> keyMap);
	ActorInformation actByMouse(std::map<EventMouse::MouseEventType, bool> mouseMap);
protected:
	virtual Animate* createFireAnimate(int gunType) {};		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) {};
};