#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
class StartGameScene : public cocos2d::Layer
{
    /*游戏开始界面，包括主菜单和设置页面*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void settingsSceneCallBack(Ref* r);     //设置场景
    void selectMapSceneCallBack(Ref* r);    //点击单机游戏，直接跳转到选择地图的场景
    void exitCallBack(Ref* r);              //退出游戏
    void NetSceneCallBack(Ref* r);  //网络场景，从缓实现
    void registerOrLoginCallBack(Ref* r);
    void chatSceneCallBack(Ref* r);
    void rankingSceneCallBack(Ref* r);
    //virtual void onEnter();
    //Label* loginStatusLabel;
    CREATE_FUNC(StartGameScene);

};

#endif // __STARTGAME_SCENE_H__