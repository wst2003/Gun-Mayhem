#pragma once
#include "cocos2d.h"
#include "Attribute.h"
USING_NS_CC;

//ǹ֧�࣬���ǹ֧��������Ҫ������
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
	//�õ�ʣ���ӵ�
	int getBullets();
	virtual bool fire();
	virtual void stopFire() {};
	static void addBulletWithPhysicsBody(const std::string& filename);
	void bulletReloading(float dt);
	bool getIsReloading();
	void setIsReloading(bool isReloading);
	bool getFirable();

	//�Ƿ���Կ���
    bool _firable;
protected:

	virtual void setFireParticleSystem() {};
	bool _isReloading;
	
	//ʣ���ӵ���
	int bulletsLeft = 0;
	GunAttribute attr;
	PhysicsBody* _physicsBody;
	
	//�ϴο����ʱ��
	clock_t last;
};