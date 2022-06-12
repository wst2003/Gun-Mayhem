#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include"Actor.h"
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "SystemHeader.h"
#include<fstream>
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
//台阶的位置属性
typedef struct EdgePosition
{
	Vec2 edgePos;
	int edgeLength;
}EdgePosition;

//游戏场景，用于所有游戏场景的建立
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
	bool responseSeparate(PhysicsContact& contact); //检测分离
	void update(float dt);		//用于响应鼠标键盘事件、传递消息给敌方玩家(AI)
	void randomFallGun();	//掉落物品的函数
	static PhysicsWorld* physicsWorld;
	void bulletsReloading(float dt);
	static Sprite* _box;
	static std::vector <std::vector< EdgePosition >>mapEdge;
	virtual void onEnterTransitionDidFinish();
	static std::string info;

	void settingSceneCallBack(Ref* ref, Button::TouchEventType type);
	virtual void onExit();

	static std::map<int, std::string>mapBGM;

private:
	
	Sprite* map;
	Player* _player = nullptr;
	Enemy* _enemy = nullptr;

	//键盘与鼠标
	std::map<EventKeyboard::KeyCode, bool> _keyMap;
	std::map<EventMouse::MouseEventType, bool> _mouseMap;

	//伪随机数存储
	int randomNum[30] = { 28051,11134,10701,18780,4905,5256,11142,12011,16012,10603,9726,6498,25036,18177,10612,9109,2485,28411,30887,28116,23470,24113,5601,1749,10977,23863,8500,24814,26780,32561 };
	int circleRandom = 0;
	std::vector<Gun*> gunOfAllUser;

	//队列，用于存储将会被得到的所有枪支
	std::queue<Gun*> gunOfBox;
	std::vector<GunAttribute>gunAttribute = { HANDGUN_ARR, SNIPERGUN_ARR, ARGUN_ARR ,BOMB }; 
	std::vector<int>gunTypes = { 3,0,2,3,2,0,3,2,2,1,3,1,1 };
	int gunChoose = 0;

	clock_t _lastTime;
	
	std::ofstream ofs;
	std::ifstream ifs;

	bool canPlayerSet = 0;
	bool canEnemySet = 0;

	//检测层的辅助参数
	int playerContectTimes = 0;
	int enemyContectTimes = 0;
};

#endif
