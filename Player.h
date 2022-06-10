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
	virtual void fire() ;		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire() {};//调用枪的stopfire函数，同时开始停火的动画
public:
	//这些函数将被场景的update调用,它们将调用Actor的fire、jump等函数
	ActorInformation sendPlayerInformation();	//发送玩家的人物信息
	void actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap);
	void actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap);

protected:
	virtual Animate* createFireAnimate(int gunType) { return nullptr; };		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) { return nullptr; };
private:
	
};