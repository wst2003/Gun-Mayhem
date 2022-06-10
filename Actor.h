#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"ui/UILoadingBar.h"

USING_NS_CC; 


class Actor :public Sprite
{
public:
	static Actor* createActorWithPhysicsBody(const std::string& filename);
	void initActor();
	void setGun(Gun* gun);	//无枪，则设置枪；有枪，则删除旧枪
	Gun* getGun();
	void throwGun();	//把枪丢掉

	virtual void fire() ;		//调用枪的fire函数，同时开始开枪的动画
	virtual void stopFire() {};//调用枪的stopfire函数，同时开始停火的动画

	void moveOnGround(Vec2 speed);	//平地移动，speed为速度矢量
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//落地的效果
	void damagedEffect(int damage);	//受伤的效果
	void killedEffect();	//死亡的效果
	void changeBitMask();
	void renewBitMask();
	void contactGround();

	void setIsJumping(bool isJumping);
	bool getIsJumping();
	void setIsDowning(bool isDowning);
	bool getIsDowning();
	void setJumpTime(int times);  //修改次数
	int getJumpTime();
	PhysicsJointFixed* _joint;
	void setIsIntheAir(bool _isInTheAir);
	bool getIsIntheAir();
	int getRemainingLive();
	void setRemainingLive(int num);

	int getBloodLeft();
	void setBloodLeft(int num);

	int getID();
	void setID(int id);
	void setActorInformation();

	void reLive(bool flag = false);

	void renewBrand();

	cocos2d::ui::LoadingBar* getBloodBar();
	Label* nameLabel;
	Label* bulletsLeftLabel;
	Label* livesLeftLabel;
	static bool isDie5 ;
protected:
	virtual Animate* createFireAnimate(int gunType) { return 0; };		//创建开火动画
	virtual Animate* createStopFireAnimate(int gunType) { return 0; };

	void startAnimation(bool isFire);
	void stopAnimation();

	Gun* gun;
	ActorInformation actorInformation;
	PhysicsBody* _physicsBody;
	int ID;
	bool _isJumping;
	bool _isDowning;
	int _jumpTime;
	bool _isInTheAir=true;
	int _remainingLive;

	int _bloodLeft = 100;

	ui::LoadingBar* bloodBar;

	clock_t damageTime;
	clock_t fireTime;

	bool isLive = true;
	
};
