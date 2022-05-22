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

	virtual void fire()=0;		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire() = 0;//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���

	void moveOnGround(Vec2 speed);	//ƽ���ƶ���speedΪ�ٶ�ʸ��
	void jumpUp();
	void jumpDown();
	void fallOnGroundEffect();	//��ص�Ч��
	void damagedEffect();	//���˵�Ч��
	void killedEffect();	//������Ч��
	

protected:
	virtual Animate* createFireAnimate(int gunType) {};		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) {};

	void startAnimation(bool isFire);
	void stopAnimation();
protected:
	Gun* gun;
	ActorInformation actorInformation;

};
