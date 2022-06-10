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
	void setGun(Gun* gun);	//��ǹ��������ǹ����ǹ����ɾ����ǹ
	Gun* getGun();
	void throwGun();	//��ǹ����

	virtual void fire() ;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() {};//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���

	void moveOnGround(Vec2 speed);	//ƽ���ƶ���speedΪ�ٶ�ʸ��
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//��ص�Ч��
	void damagedEffect(int damage);	//���˵�Ч��
	void killedEffect();	//������Ч��
	void changeBitMask();
	void renewBitMask();
	void contactGround();

	void setIsJumping(bool isJumping);
	bool getIsJumping();
	void setIsDowning(bool isDowning);
	bool getIsDowning();
	void setJumpTime(int times);  //�޸Ĵ���
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
	virtual Animate* createFireAnimate(int gunType) { return 0; };		//�������𶯻�
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
