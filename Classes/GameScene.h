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

	void responseContact(PhysicsContact& contact);	//碰撞监听器的响应函数，用作onContactBegin属性

	void update(float dt);		//用于响应鼠标键盘事件、传递消息给敌方玩家(AI)

	void randomFallGun(const std::string& filename, Vec2 v);	//掉落物品的函数

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
	
	auto scene = cocos2d::Scene::createWithPhysics();	//物理引擎
	auto gameLayer = GameScene::create();
	scene->addChild(gameLayer,0);

	
	return scene;
}
#endif
