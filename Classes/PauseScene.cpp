#include "PauseScene.h"
#include "SelectMapScene.h"
#include "StartGameScene.h"
#include "ui/CocosGUI.h"
#include "ui/UISlider.h"
#include "extensions/cocos-ext.h"
#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
//创建场景
Scene* PauseScene::createScene(RenderTexture* sqr)
{
	
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer,1);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//将游戏场景截图作为当前场景背景
	Sprite* prtScene = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	prtScene->setPosition(visibleSize / 2);
	prtScene->setFlippedY(true);
	//灰化处理，实现暂停时背景模糊
	prtScene->setColor(Color3B::GRAY);
	scene->addChild(prtScene);
	return scene;
}

void PauseScene::onEnterTransitionDidFinish()
{
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
		if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING) {
			UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(GameScene::mapBGM[UserDefault::getInstance()->getIntegerForKey(MAPID)], true));
			AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
		}
	}
	return;
}

bool PauseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//一个条形背景，装饰用
	auto barBackground = Sprite::create("pauseBackground.png");
	barBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	barBackground->setColor(Color3B::GRAY);
	this->addChild(barBackground, 2);
	//重新开始、回到游戏、返回主菜单
	MenuItemImage* againMenuItem = MenuItemImage::create("againNormal.png","againSelected.png",
		CC_CALLBACK_1(PauseScene::againCallBack,this));
	againMenuItem->setPosition(barBackground->getContentSize().width / 6, barBackground->getContentSize().height / 6 * 5);
	MenuItemImage* backMenuItem = MenuItemImage::create("backNormal.png", "backSelected.png",
		CC_CALLBACK_1(PauseScene::backCallBack, this));
	backMenuItem->setPosition(barBackground->getContentSize().width / 6*3, barBackground->getContentSize().height / 6 * 5);
	MenuItemImage* startMenuCallBackMenuItem = MenuItemImage::create("startMenuCallBackNormal.png", "startMenuCallBackSelected.png",
		CC_CALLBACK_1(PauseScene::startMenuCallBack, this));
	startMenuCallBackMenuItem->setPosition(barBackground->getContentSize().width / 6*5, barBackground->getContentSize().height / 6 * 5);
	Menu* pauseMenu = Menu::create(againMenuItem, backMenuItem, startMenuCallBackMenuItem, NULL);
	pauseMenu->setPosition(Vec2::ZERO);
	barBackground->addChild(pauseMenu);
	//音乐开关
	Label* musicLabel = Label::createWithSystemFont("Music", "Times New Roman", 50);
	musicLabel->setColor(Color3B::BLACK);
	musicLabel->setPosition(Vec2(barBackground->getContentSize().width / 4, barBackground->getContentSize().height / 12 * 7));
	barBackground->addChild(musicLabel);
	ControlSwitch* musicButtonSwitch = ControlSwitch::create(
		Sprite::create("bg_ButtonSwitch.png"),
		Sprite::create("on_ButtonSwitch.png"),
		Sprite::create("off_ButtonSwitch.png"),
		Sprite::create("switch.png"),
		Label::createWithSystemFont("on", "Times New Roman", 30),
		Label::createWithSystemFont("off", "Times New Roman", 30));
	musicButtonSwitch->setPosition(Vec2(barBackground->getContentSize().width /4, barBackground->getContentSize().height / 12*5));
	musicButtonSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(PauseScene::musicSwitch), Control::EventType::VALUE_CHANGED);
	musicButtonSwitch->setEnabled(true);
	barBackground->addChild(musicButtonSwitch);
	//音效开关
	Label* soundLabel = Label::createWithSystemFont("Sound", "Times New Roman", 50);
	soundLabel->setColor(Color3B::BLACK);
	soundLabel->setPosition(Vec2(barBackground->getContentSize().width / 4*3, barBackground->getContentSize().height / 12 * 7));
	barBackground->addChild(soundLabel);
	ControlSwitch* soundButtonSwitch = ControlSwitch::create(
		Sprite::create("bg_ButtonSwitch.png"),
		Sprite::create("on_ButtonSwitch.png"),
		Sprite::create("off_ButtonSwitch.png"),
		Sprite::create("switch.png"),
		Label::createWithSystemFont("on", "Times New Roman", 30),
		Label::createWithSystemFont("off", "Times New Roman", 30));
	soundButtonSwitch->setPosition(Vec2(barBackground->getContentSize().width / 4*3, barBackground->getContentSize().height / 12*5));
	soundButtonSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(PauseScene::soundSwitch), Control::EventType::VALUE_CHANGED);
	soundButtonSwitch->setEnabled(true);
	barBackground->addChild(soundButtonSwitch);
	//读取上次退出时，两按钮的状态
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
		musicButtonSwitch->setOn(true);
	else
		musicButtonSwitch->setOn(false);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
		soundButtonSwitch->setOn(true);
	else
		soundButtonSwitch->setOn(false);
	//音量控制
	auto volumeSprite = Sprite::create("volume.png");
	volumeSprite->setPosition(barBackground->getContentSize().width / 6, barBackground->getContentSize().height / 6);
	barBackground->addChild(volumeSprite);
	auto musicVolumeSlider = Slider::create();
	musicVolumeSlider->loadBarTexture("musicVolumeBg.png");
	musicVolumeSlider->loadSlidBallTextures("CloseNormal.png");
	musicVolumeSlider->loadProgressBarTexture("musicVolume.png");
	musicVolumeSlider->setMaxPercent(100.0f);
	musicVolumeSlider->setPosition(Vec2(barBackground->getContentSize().width / 2, barBackground->getContentSize().height / 6));
	musicVolumeSlider->addEventListener(CC_CALLBACK_2(PauseScene::changeMusicVolumeSlider, this));
	musicVolumeSlider->setPercent(UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME));
	barBackground->addChild(musicVolumeSlider);
	
	return true;
}
//重新开始的回调
void PauseScene::againCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setBoolForKey(ISPLAYGAME, false);
	Director::getInstance()->replaceScene(SelectMapScene::createScene());
}
//回到游戏的回调
void PauseScene::backCallBack(Ref* pSender)
{
	Director::getInstance()->popScene();
}
//返回主菜单的回调
void PauseScene::startMenuCallBack(Ref* pSender)
{
	UserDefault::getInstance()->setBoolForKey(ISPLAYGAME, false);
	Director::getInstance()->replaceScene(StartGameScene::createScene());
}
//音乐开关切换的回调
void PauseScene::musicSwitch(Ref* pSender, Control::EventType controlEvent)
{
	if (controlEvent == Control::EventType::VALUE_CHANGED) {
		ControlSwitch* control = dynamic_cast<ControlSwitch*>(pSender);
		if (control->isOn()) {
			log("music-on");
			UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
			int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
			if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING) {
				UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(GameScene::mapBGM[UserDefault::getInstance()->getIntegerForKey(MAPID)], true));
				AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
			}
		}
		else {
			log("music-off");
			UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
			AudioEngine::stop(UserDefault::getInstance()->getIntegerForKey(MUSICID));
		}
	}
	return;
}
//音效开关切换的回调
void PauseScene::soundSwitch(Ref* pSender, Control::EventType controlEvent)
{
	if (controlEvent == Control::EventType::VALUE_CHANGED) {
		ControlSwitch* control = dynamic_cast<ControlSwitch*>(pSender);
		if (control->isOn()) {
			log("sound-on");
			UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
		}
		else {
			log("sound-off");
			UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
		}
	}
}
//音量改变时的回调
void PauseScene::changeMusicVolumeSlider(Ref* r, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(r);
		int percent = slider->getPercent();
		UserDefault::getInstance()->setIntegerForKey(MUSICVOLUME, percent);
		UserDefault::getInstance()->flush();
		AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), percent * 0.01f);
		log("change volume%f", percent);
	}
}
