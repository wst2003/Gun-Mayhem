#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
USING_NS_CC;

class AIEnemy :public Actor
{
public:
	virtual void fire();		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire();//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���
public:
	//��Щ��������������update����,���ǽ�����Actor��fire��jump�Ⱥ���
	ActorInformation getPlayerInformation();	//��ȡ��ҵ�������Ϣ
	void actByAI();	//AI�㷨�������û���Ϊ������Ӧ
protected:
	virtual Animate* createFireAnimate(int gunType) {};		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) {};
private:
	int difficulty;//ѡ��AI�Ѷȣ����ݲ�ʵ��
	ActorInformation informationOfPlayer;
}; 