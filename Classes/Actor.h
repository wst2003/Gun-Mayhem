#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
USING_NS_CC; 


class Actor :public Sprite
{
public:
	static Actor* createActorWithPhysicsBody(const std::string& filename);
	void setGun(Gun* gun);	//��ǹ��������ǹ����ǹ����ɾ����ǹ
	Gun* getGun();
	void throwGun();	//��ǹ����

	virtual void fire() ;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() {};//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���

	void moveOnGround(Vec2 speed);	//ƽ���ƶ���speedΪ�ٶ�ʸ��
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//��ص�Ч��
	void damagedEffect();	//���˵�Ч��
	void killedEffect();	//������Ч��


	void setIsJumping(bool isJumping);
	bool getIsJumping();
	void setIsDowning(bool isDowning);
	bool getIsDowning();
	void setJumpTime(int times);  //�޸Ĵ���
	int getJumpTime();
	PhysicsJointFixed* _joint;
protected:
	virtual Animate* createFireAnimate(int gunType) { return 0; };		//�������𶯻�
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
