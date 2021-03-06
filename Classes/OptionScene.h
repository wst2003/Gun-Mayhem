
#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ui/UISlider.h"
USING_NS_CC;
using namespace ui;

class OptionScene : public cocos2d::Layer
{
    MenuItemImage* onButtonMusic;
    MenuItemImage* offButtonMusic;
    MenuItemImage* onButtonSound;
    MenuItemImage* offButtonSound;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void musicButtonOnCallBack(Ref* r);
    void musicButtonOffCallBack(Ref* r);
    void soundButtonOnCallBack(Ref* r);
    void soundButtonOffCallBack(Ref* r);
    void backCallBack(Ref* r);

    virtual void onEnterTransitionDidFinish();
    void changeMusicVolumeSlider(Ref* r, Slider::EventType type);

    CREATE_FUNC(OptionScene);

};

#endif // __OPTION_SCENE_H__

