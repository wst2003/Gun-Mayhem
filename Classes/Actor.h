#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
USING_NS_CC; 


class Actor :public Sprite
{
public:
	static Actor* createActorWithPhysicsBody(const std::string& filename);
	void setGun(Gun* gun);	//无枪，则设置枪；有枪，则删除旧枪
	Gun* getGun();
	void throwGun();	//把枪丢掉

	virtual void fire()=0;		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire() = 0;//调用枪的stopfire函数，同时开始停火的动画

	void moveOnGround(Vec2 speed);	//平地移动，speed为速度矢量
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//落地的效果
	void damagedEffect();	//受伤的效果
	void killedEffect();	//死亡的效果
	

protected:
	virtual Animate* createFireAnimate(int gunType) {};		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) {};

	void startAnimation(bool isFire);
	void stopAnimation();
protected:
	Gun* gun;
	ActorInformation actorInformation;

};
