#ifndef __SETTINGS_SCENE_H__
#define __SETTINGS_SCENE_H__

#include "cocos2d.h"


class SettingsScene : public cocos2d::Layer
{
    /*����ҳ��*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void backToMenuCallBack(Ref* r);
    /*����ʵ����Ч�������ֲ��ŵ�����*/

    CREATE_FUNC(SettingsScene);

};

#endif // __SETTINGS_SCENE_H__
