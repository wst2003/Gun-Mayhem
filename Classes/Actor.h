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

	virtual void fire() ;		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire() {};//调用枪的stopfire函数，同时开始停火的动画

	void moveOnGround(Vec2 speed);	//平地移动，speed为速度矢量
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//落地的效果
	void damagedEffect();	//受伤的效果
	void killedEffect();	//死亡的效果


	void setIsJumping(bool isJumping);
	bool getIsJumping();
	void setIsDowning(bool isDowning);
	bool getIsDowning();
	void setJumpTime(int times);  //修改次数
	int getJumpTime();
	PhysicsJointFixed* _joint;
protected:
	virtual Animate* createFireAnimate(int gunType) { return 0; };		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) { return 0; };

	void startAnimation(bool isFire);
	void stopAnimation();

	Gun* gun;
	ActorInformation actorInformation;
	PhysicsBody* _physicsBody;

	bool _isJumping;
	bool _isDowning;
	int _jumpTime;
};
