#ifndef __STARTGAME_SCENE_H__
#define __STARTGAME_SCENE_H__

#include "ui/CocosGUI.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;


class StartGameScene : public cocos2d::Layer
{
    /*��Ϸ��ʼ���棬�������˵�������ҳ��*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();

    void settingsSceneCallBack(Ref* r);     //���ó���
    void selectMapSceneCallBack(Ref* r);    //���������Ϸ��ֱ����ת��ѡ���ͼ�ĳ���
    void exitCallBack(Ref* r);              //�˳���Ϸ

    void NetSceneCallBack(Ref* r);  //���糡�����ӻ�ʵ��
    void registerOrLoginCallBack(Ref* r);
    void chatSceneCallBack(Ref* r);
    void rankingSceneCallBack(Ref* r);

    Label* loginStatusLabel;
    CREATE_FUNC(StartGameScene);

};

#endif // __STARTGAME_SCENE_H__