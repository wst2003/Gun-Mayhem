#ifndef __SelectMap_SCENE_H__
#define __SelectMap_SCENE_H__
#include "cocos2d.h"
#include<map>
#include<iostream>
USING_NS_CC;
extern int numberOfMap;    //全局变量，记载地图序号
typedef enum {
    MAP_1 = 111,
    MAP_2,
    MAP_3,
    MAP_4
}mapIndex;

class SelectMapScene : public cocos2d::Layer
{
    void backToMenuCallBack(Ref* r);
    void startCallBack(Ref* r);
    int maxNumberOfMap;
    int minNumberOfMap;
    Vec2 map_Position;
    /*选择地图页面*/
    void arrowRightCallBack(Ref* r);
    void arrowLeftCallBack(Ref* r);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    //std::vector<Sprite*>map_all;
    //std::vector<Sprite*>::iterator iter;
    void mapOneCallBack(Ref* r);    //选择第一张地图的回调函数
    CREATE_FUNC(SelectMapScene);
    std::map<int, std::string> map_int;

};

#endif // __SelectMap_SCENE_H__