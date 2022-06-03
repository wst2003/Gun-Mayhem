#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"

USING_NS_CC;
#define LEFT_KEY EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define RIGHT_KEY EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define UP_KEY EventKeyboard::KeyCode::KEY_UP_ARROW
#define A_KEY EventKeyboard::KeyCode::KEY_A
#define W_KEY EventKeyboard::KeyCode::KEY_W
#define D_KEY EventKeyboard::KeyCode::KEY_D
#define DOWN_KEY EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define S_KEY EventKeyboard::KeyCode::KEY_S
#define P_KEY EventKeyboard::KeyCode::KEY_P

#define MOUSE_DOWN EventMouse::MouseEventType::MOUSE_DOWN
#define MOUSE_UP EventMouse::MouseEventType::MOUSE_UP
#define MOUSE_MOVE EventMouse::MouseEventType::MOUSE_MOVE

class Player : public Actor
{
public:
	virtual void fire() ;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() ;//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���
public:
	//��Щ��������������update����,���ǽ�����Actor��fire��jump�Ⱥ���
	ActorInformation sendPlayerInformation();	//������ҵ�������Ϣ
	void actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap);
	void actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap);
protected:
	virtual Animate* createFireAnimate(int gunType) {};		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) {};
private:
	
};