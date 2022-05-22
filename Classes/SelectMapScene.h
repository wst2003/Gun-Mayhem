#ifndef __SelectMap_SCENE_H__
#define __SelectMap_SCENE_H__

#include "cocos2d.h"
int numberOfMap;    //全局变量，记载地图序号

class SelectMapScene : public cocos2d::Layer
{
    /*选择地图页面*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void mapOneCallBack(Ref* r);    //选择第一张地图的回调函数

    CREATE_FUNC(SelectMapScene);

};

#endif // __SelectMap_SCENE_H__
