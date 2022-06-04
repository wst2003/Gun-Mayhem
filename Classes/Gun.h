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
	virtual bool fire();
	virtual void stopFire() {};
	void addBulletWithPhysicsBody(const std::string& filename);
	void bulletReloading(float dt);
	bool getIsReloading();
	void setIsReloading(bool isReloading);
	bool getFirable();


    bool _firable;
protected:
//	void addBulletWithPhysicsBody(const std::string& filename);

	/*���ɴ����ӵ�ʱ��Ӧʹ�þ���֡�����Լ�ڴ�*/
	virtual void setFireParticleSystem() {};
	bool _isReloading;
	
	int bulletsLeft = 0;
	GunAttribute attr;
	PhysicsBody* _physicsBody;
	
	clock_t last;
};