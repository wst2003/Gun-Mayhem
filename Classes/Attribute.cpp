#include "cocos2d.h"
#include "Attribute.h"

USING_NS_CC;


//移动位置更新
void ActorInformation::changePosition(Vec2 newVec2)
{
	_position = newVec2;

	return;
}

//调整开火状态
void ActorInformation::changeIsFire(bool isFire)
{
	_isFire = isFire;
	return;
}

//调整手枪类型
void ActorInformation::changeGunType(int gunType)
{
	_gunType = gunType;

	return;
}

//将人物信息转换为string
std::string ActorInformation::toString()
{
	return "666";
}

//将字符串转换为人物信息
ActorInformation ActorInformation::toActorInformation(const std::string& s)
{
	return { 0,0,0 };
}
