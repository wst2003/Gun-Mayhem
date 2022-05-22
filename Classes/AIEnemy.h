#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
USING_NS_CC;

class AIEnemy :public Actor
{
public:
	virtual void fire();		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire();//调用枪的stopfire函数，同时开始停火的动画
public:
	//这些函数将被场景的update调用,它们将调用Actor的fire、jump等函数
	ActorInformation getPlayerInformation();	//获取玩家的人物信息
	void actByAI();	//AI算法，根据用户行为做出响应
protected:
	virtual Animate* createFireAnimate(int gunType) {};		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) {};
private:
	int difficulty;//选择AI难度，可暂不实现
	ActorInformation informationOfPlayer;
}; 