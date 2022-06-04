#pragma once
#include "cocos2d.h"
#include "Attribute.h"
USING_NS_CC;

class Gun :public Sprite
{
	/*枪类*/
public:
	/*枪也受物理引擎制约，因为枪与人物必须受关节连接*/
	static Gun* createGunWithPhysicsBody(const std::string& filename);	

	void setAttribute(GunAttribute attr);
	GunAttribute getAttribute();

	//增加子弹数量，不会超过最大值
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

	/*生成大量子弹时，应使用精灵帧对象节约内存*/
	virtual void setFireParticleSystem() {};
	bool _isReloading;
	
	int bulletsLeft = 0;
	GunAttribute attr;
	PhysicsBody* _physicsBody;
	
	clock_t last;
};