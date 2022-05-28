#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"Actor.h"
#include "cocos2d.h"
#include "Brand.h"
USING_NS_CC;

#define FOOTSTEP 0
#define ACTOR 1
#define ENEMY 4
#define GUN 5
#define EDGE 2
#define BULLET 3
#define BOX 6

//category 与 collision 做  & 不为0
#define PLAYER_COLLISION_BITMASK 1
#define PLAYER_CATEGORY_BITMASK 1

#define ENEMY_COLLISION_BITMASK 2
#define	ENEMY_CATEGORY_BITMASK 2

#define ACTOR_CHANGED_COLLISION_BITMASK 16
#define ACTOR_CHANGED_CATEGORY_BITMASK 16

#define	FOOTSTEP_COLLISION_BITMASK 47
#define FOOTSTEP_CATEGORY_BITMASK 47

#define EDGE_COLLISION_BITMASK 0xFFFFFFFF
#define EDGE_CATEGORY_BITMASK 0xFFFFFFFF

#define	BULLET_COLLISION_BITMASK 15
#define BULLET_CATEGORY_BITMASK 15

#define GUN_COLLISION_BITMASK 32
#define GUN_CATEGORY_BITMASK 32

#define GUN_CHANGED_COLLISION_BITMASK 16
#define GUN_CHANGED_CATEGORY_BITMASK 16



class GameScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

	bool responseContact(PhysicsContact& contact);	//碰撞监听器的响应函数，用作onContactBegin属性
	bool responseSeparate(PhysicsContact& contact);
	
	void update(float dt);		//用于响应鼠标键盘事件、传递消息给敌方玩家(AI)
	void randomFallGun(const std::string& filename, Vec2 v);	//掉落物品的函数
	static PhysicsWorld* physicsWorld;

private:
	std::map<EventKeyboard::KeyCode, bool> _keyMap;
	std::map<EventMouse::MouseEventType, bool> _mouseMap;
	Actor* _player;
	Actor* _enemy;
	Brand* _playerBrand;
	Brand* _enemyBrand;

	//地图上盒子中的
	Gun* handGun;
	Gun* sniperGun;
	Gun* arGun;
};

#endif
