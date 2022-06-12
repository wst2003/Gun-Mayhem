#pragma once
#include "cocos2d.h"
#include "Attribute.h"
USING_NS_CC;

//枪支类，存放枪支的所有需要的属性
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
	//得到剩余子弹
	int getBullets();
	virtual bool fire();
	virtual void stopFire() {};
	static void addBulletWithPhysicsBody(const std::string& filename);
	void bulletReloading(float dt);
	bool getIsReloading();
	void setIsReloading(bool isReloading);
	bool getFirable();

	//是否可以开火
    bool _firable;
protected:

	virtual void setFireParticleSystem() {};
	bool _isReloading;
	
	//剩余子弹数
	int bulletsLeft = 0;
	GunAttribute attr;
	PhysicsBody* _physicsBody;
	
	//上次开火的时间
	clock_t last;
};