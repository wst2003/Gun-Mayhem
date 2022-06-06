#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"Actor.h"
#include "cocos2d.h"
#include "Brand.h"
#include "Player.h"
#include "AIEnemy.h"
#include "SystemHeader.h"

#include<fstream>
USING_NS_CC;
#define SPAY 45456


class GameScene : public Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void initMap();
	void createGround(Vec2 pos, float length);
	
	void createBrand(Actor* actor);
	CREATE_FUNC(GameScene);

	bool responseContact(PhysicsContact& contact);	//碰撞监听器的响应函数，用作onContactBegin属性
	bool responseSeparate(PhysicsContact& contact);
	void update(float dt);		//用于响应鼠标键盘事件、传递消息给敌方玩家(AI)
	void randomFallGun( Vec2 v);	//掉落物品的函数
	static PhysicsWorld* physicsWorld;
	void bulletsReloading(float dt);
	static Sprite* _box;

	static std::string info;
private:
	std::map<EventKeyboard::KeyCode, bool> _keyMap;
	std::map<EventMouse::MouseEventType, bool> _mouseMap;
	Sprite* map;
	Player* _player;
	AIEnemy* _enemy;
	Brand* _playerBrand;
	Brand* _enemyBrand;

	std::vector<Gun*> gunOfAllUser;
	std::queue<Gun*> gunOfBox;
	std::vector<GunAttribute>gunAttribute = { HANDGUN_ARR, SNIPERGUN_ARR, ARGUN_ARR };

	clock_t _lastTime;
	
	std::ofstream ofs;
	std::ifstream ifs;
	bool canPlayerSet = 0;
	bool canEnemySet = 0;

	int kk = 0;
};

#endif
