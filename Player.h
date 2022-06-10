#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
USING_NS_CC;

class Player : public Actor
{
public:
	static Player* createWithActor(Actor* actor);
	virtual void fire() ;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() {};//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���
public:
	//��Щ��������������update����,���ǽ�����Actor��fire��jump�Ⱥ���
	ActorInformation sendPlayerInformation();	//������ҵ�������Ϣ
	void actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap);
	void actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap);

protected:
	virtual Animate* createFireAnimate(int gunType) { return nullptr; };		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) { return nullptr; };
private:
	
};