#include "cocos2d.h"
#include "Attribute.h"

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

//��������Ϣת��Ϊstring
std::string ActorInformation::toString()
{
	return "666";
}

//���ַ���ת��Ϊ������Ϣ
ActorInformation ActorInformation::toActorInformation(const std::string& s)
{
	return { 0,0,0 };
}
