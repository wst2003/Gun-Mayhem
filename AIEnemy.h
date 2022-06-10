#pragma once
#include "cocos2d.h"
#include"Attribute.h"
#include "Gun.h"
#include"Actor.h"
#include "Player.h"
USING_NS_CC;

class AIEnemy :public Actor
{
public:
	static AIEnemy* createWithActor(Actor* actor);

	virtual void fire();		//����ǹ��fire������ͬʱ��ʼ��ǹ�Ķ���
	virtual void stopFire();//����ǹ��stopfire������ͬʱ��ʼͣ��Ķ���
public:
	//��Щ��������������update����,���ǽ�����Actor��fire��jump�Ⱥ���
	void getPlayerInformation(Player* player);	//��ȡ��ҵ�������Ϣ
	void actByAI();	//AI�㷨�������û���Ϊ������Ӧ
	void actByFriend(std::string info);
	static int leftOrRight;
protected:
	virtual Animate* createFireAnimate(int gunType) { return nullptr; };		//�������𶯻�
	virtual Animate* createStopFireAnimate(int gunType) { return nullptr; };
private:
	int difficulty;//ѡ��AI�Ѷȣ����ݲ�ʵ��
	ActorInformation informationOfPlayer;
	int flag;
	int jumpFlag = 1;
};