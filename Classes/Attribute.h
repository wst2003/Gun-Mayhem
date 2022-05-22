#pragma once
#include "cocos2d.h"
USING_NS_CC;

//must be edited
#define HANDGUN_ARR GunAttribute(0,0,0,0,0);
#define SNIPERGUN_ARR GunAttribute(0,0,0,0,0);
#define ARGUN_ARR GunAttribute(0,0,0,0,0);
struct GunAttribute
{
	int maxCapacity;	//��������
	float fireRate;		//����
	float damageValue;	//�˺�ֵ
	float recoilValue;	//������ֵ
	float velocity;		//�˶�(��)�ٶ�
};



#define HANDGUN_TYPE 1;
#define SNIPERGUN_TYPE 2;
#define ARGUN_TYPE 3;
class ActorInformation
{
	/*���������������*/
public:
	ActorInformation(const Vec2& v, const bool isFire, const int gunType) :
		position(v), isFire(isFire), gunType(gunType) {};
	void changePosition(Vec2 newVec2);
	void changeIsFire(bool isFire);
	void changeGunType(int gunType);

	std::string toString();		//ת�����ַ���(for net)
	static ActorInformation toActorInformation(const std::string& s);	//���ַ���ת��(for net)
private:
	Vec2 position;
	bool isFire;
	int gunType;
};

