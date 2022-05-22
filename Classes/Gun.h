#pragma once
#include "cocos2d.h"
#include"Attribute.h"
USING_NS_CC;

class Gun :public Sprite
{
	/*ǹ��*/
public:
	/*ǹҲ������������Լ����Ϊǹ����������ܹؽ�����*/
	static Gun* createGunWithPhysicsBody(const std::string& filename);	

	void setAttribute(GunAttribute attr);
	GunAttribute getAttribute();
	void setBullets(int num);
	int getBullets();

	virtual void fire() = 0;
	virtual void stopFire() = 0;
	
protected:
	void addBulletWithPhysicsBody(const std::string& filename);
	/*���ɴ����ӵ�ʱ��Ӧʹ�þ���֡�����Լ�ڴ�*/
	virtual void setFireParticleSystem() {};

	int bulletsLeft;
	GunAttribute attr;
	
};