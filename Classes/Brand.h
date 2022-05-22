#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class Brand:public Node
{
public:
	Brand(int actorNum, std::string name, int bulletsLeft, int livesLeft, int lifePercent = 100);
	//构造函数里部署相对位置
	void changeName(std::string name);
	void changeBulletsLeft(int bulletsLeft);
	void changeLivesLeft(int livesLeft);
	void changeLifePercent(int lifePercent);
private:
	Sprite* s;
	Label* nameLabel;
	Label* bulletsLeftLabel;
	Label* livesLeftLabel;
	LoadingBar* bloodBar;
};