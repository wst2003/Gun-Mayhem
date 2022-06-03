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
	virtual void fire() ;		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire() ;//调用枪的stopfire函数，同时开始停火的动画
public:
	//这些函数将被场景的update调用,它们将调用Actor的fire、jump等函数
	ActorInformation sendPlayerInformation();	//发送玩家的人物信息
	void actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap);
	void actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap);
protected:
	virtual Animate* createFireAnimate(int gunType) {};		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) {};
private:
	
};