#include "cocos2d.h"
#include "Attribute.h"
#include "SystemHeader.h"
USING_NS_CC;


//�ƶ�λ�ø���
void ActorInformation::changePosition(Vec2 newVec2)
{
	_position = newVec2;

	return;
}

//��������״̬
void ActorInformation::changeIsFire(bool isFire)
{
	_isFire = isFire;
	return;
}

//������ǹ����
void ActorInformation::changeGunType(int gunType)
{
	_gunType = gunType;

	return;
}
void ActorInformation::changeLeftOrRight(int leftOrRight)
{
	this->leftOrRight = leftOrRight;
}

//��������Ϣת��Ϊstring
std::string ActorInformation::toString()
{
	auto xstr = Value(_position.x).asString();
	if (xstr.length() < 12) {
		auto del = 12 - xstr.length();
		std::string  tmp= "0";
		for (int i = 0; i < del; i++) {
			xstr += tmp;
		}
	}
	auto ystr = Value(_position.y).asString();
	if (ystr.length() < 12) {
		auto del = 12 - ystr.length();
		std::string  tmp = "0";
		for (int i = 0; i <del; i++) {
			ystr += tmp;
		}
	}
	return xstr+"|"+ ystr + "|"+Value(_isFire).asString()+"|"
		+Value(leftOrRight).asString();
}

//���ַ���ת��Ϊ������Ϣ
ActorInformation ActorInformation::toActorInformation(const std::string& s)
{
	return { 0,0,0 };
}

Vec2 ActorInformation::getPosition()
{
	return _position;
}
