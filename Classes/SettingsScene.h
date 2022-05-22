#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"


class SettingsScene : public cocos2d::Layer
{
    /*设置页面*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void backToMenuCallBack(Ref* r);
    /*自行实现音效音量音乐播放等设置*/

    CREATE_FUNC(SettingsScene);

};

#endif // __SETTINGS_SCENE_H__
