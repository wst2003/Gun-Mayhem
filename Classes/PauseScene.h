/*游戏进行时的暂停页面*/
#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ui/UISlider.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;
USING_NS_CC_EXT;

class PauseScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);
    virtual bool init();
    virtual void onEnterTransitionDidFinish();
    void againCallBack(Ref* pSender);
    void backCallBack(Ref* pSender);
    void startMenuCallBack(Ref* pSender);
    void musicSwitch(Ref* pSender, Control::EventType controlEvent);
    void soundSwitch(Ref* pSender, Control::EventType controlEvent);
    void changeMusicVolumeSlider(Ref* r, Slider::EventType type);
    CREATE_FUNC(PauseScene);

};

#endif // __PAUSE_SCENE_H__

