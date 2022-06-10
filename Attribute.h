#pragma once
#include "cocos2d.h"
USING_NS_CC;

struct GunAttribute
{
	int maxCapacity;	//��������
	float fireRate;		//����
	float damageValue;	//�˺�ֵ
	float recoilValue;	//������ֵ
	float velocity;		//�˶�(��)�ٶ�
	float impulse;
};

class ActorInformation
{
	/*���������������*/
public:
	ActorInformation(const Vec2& v = Vec2::ZERO, const bool isFire = 0, const int gunType = 0) :
		_position(v), _isFire(isFire), _gunType(gunType) {};
	void changePosition(Vec2 newVec2);
	void changeIsFire(bool isFire);
	void changeGunType(int gunType);
	void changeLeftOrRight(int leftOrRight);
	std::string toString();		//ת�����ַ���(for net)
	static ActorInformation toActorInformation(const std::string& s);	//���ַ���ת��(for net)
	Vec2 getPosition();
private:
	Vec2 _position;
	bool _isFire;
	int _gunType;
	int remainLive;
	int leftOrRight = 2;
};

