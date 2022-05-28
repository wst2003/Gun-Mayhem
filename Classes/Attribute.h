#pragma once
#include "cocos2d.h"
USING_NS_CC;

//must be edited
#define HANDGUN_ARR {0,0,0,0,0}
#define SNIPERGUN_ARR {0,0,0,0,0}
#define ARGUN_ARR {0,0,0,0,0}
struct GunAttribute
{
	int maxCapacity;	//弹夹容量
	float fireRate;		//射速
	float damageValue;	//伤害值
	float recoilValue;	//后坐力值
	float velocity;		//运动(初)速度
};



#define HANDGUN_TYPE 1;
#define SNIPERGUN_TYPE 2;
#define ARGUN_TYPE 3;
class ActorInformation
{
	/*记载人物的属性类*/
public:
	ActorInformation(const Vec2& v = Vec2::ZERO, const bool isFire = 0, const int gunType = 0) :
		_position(v), _isFire(isFire), _gunType(gunType) {};
	void changePosition(Vec2 newVec2);
	void changeIsFire(bool isFire);
	void changeGunType(int gunType);
	std::string toString();		//转换成字符串(for net)
	static ActorInformation toActorInformation(const std::string& s);	//从字符串转回(for net)

private:
	Vec2 _position;
	bool _isFire;
	int _gunType;
};

