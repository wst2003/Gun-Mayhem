#pragma once
#include "cocos2d.h"
#include "Attribute.h"
USING_NS_CC;

class Gun :public Sprite
{
	/*ǹ��*/
public:
	/*ǹҲ������������Լ����Ϊǹ����������ܹؽ�����*/
	static Gun* createGunWithPhysicsBody(const std::string& filename);	

	void setAttribute(GunAttribute attr);
	GunAttribute getAttribute();

	//�����ӵ����������ᳬ�����ֵ
	void setBullets(int num);
	int getBullets();
	virtual void fire();
	virtual void stopFire() {};
	void addBulletWithPhysicsBody(const std::string& filename);
protected:
//	void addBulletWithPhysicsBody(const std::string& filename);

	/*���ɴ����ӵ�ʱ��Ӧʹ�þ���֡�����Լ�ڴ�*/
	virtual void setFireParticleSystem() {};

	int bulletsLeft;
	GunAttribute attr;
	PhysicsBody* _physicsBody;
	
};