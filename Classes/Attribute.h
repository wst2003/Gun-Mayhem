#pragma once
#include "cocos2d.h"
USING_NS_CC;

struct GunAttribute
{
	int maxCapacity;	//弹夹容量
	float fireRate;		//射速
	float damageValue;	//伤害值
	float recoilValue;	//后坐力值
	float velocity;		//运动(初)速度
	float impulse;
};

class ActorInformation
{
	/*记载人物的属性类*/
public:
	ActorInformation(const Vec2& v = Vec2::ZERO, const bool isFire = 0, const int gunType = 0) :
		_position(v), _isFire(isFire), _gunType(gunType) {};
	void changePosition(Vec2 newVec2);
	void changeIsFire(bool isFire);
	void changeGunType(int gunType);
	void changeLeftOrRight(int leftOrRight);
	std::string toString();		//转换成字符串(for net)
	static ActorInformation toActorInformation(const std::string& s);	//从字符串转回(for net)
	Vec2 getPosition();
private:
	Vec2 _position;
	bool _isFire;
	int _gunType;
	int remainLive;
	int leftOrRight = 2;
};

