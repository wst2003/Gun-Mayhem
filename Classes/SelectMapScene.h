#ifndef __SelectMap_SCENE_H__
#define __SelectMap_SCENE_H__

#include "cocos2d.h"
int numberOfMap;    //ȫ�ֱ��������ص�ͼ���

class SelectMapScene : public cocos2d::Layer
{
    /*ѡ���ͼҳ��*/
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void mapOneCallBack(Ref* r);    //ѡ���һ�ŵ�ͼ�Ļص�����

    CREATE_FUNC(SelectMapScene);

};

#endif // __SelectMap_SCENE_H__
