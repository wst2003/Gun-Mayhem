#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"Actor.h"
#include "cocos2d.h"
#include "Brand.h"
USING_NS_CC;
class GameScene : cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

	void responseContact(PhysicsContact& contact);	//��ײ����������Ӧ����������onContactBegin����

	void update(float dt);		//������Ӧ�������¼���������Ϣ���з����(AI)

	void randomFallGun(const std::string& filename, Vec2 v);	//������Ʒ�ĺ���

private:
	std::map<EventKeyboard::KeyCode, bool> keyMap;
	std::map<EventMouse::MouseEventType, bool> mouseMap;

	Actor* player;
	Actor* enemy;

	Brand* playerBrand;
	Brand* enemyBrand;
};

cocos2d::Scene*  GameScene::createScene()
{
	
	auto scene = cocos2d::Scene::createWithPhysics();	//��������
	auto gameLayer = GameScene::create();
	scene->addChild(gameLayer,0);

	
	return scene;
}
#endif
