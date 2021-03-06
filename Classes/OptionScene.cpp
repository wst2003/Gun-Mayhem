#include"OptionScene.h"
#include "ui/UISlider.h"
#include "GameScene.h"
#include "SystemHeader.h"
USING_NS_CC;
using namespace ui;

Scene* OptionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = OptionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool OptionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = Sprite::create("optionScene.png");
	bg->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 1 / 2));
	this->addChild(bg, 0);

	onButtonMusic = MenuItemImage::create("ON_able.png", "ON_selected.png", "ON_un.png",
		CC_CALLBACK_1(OptionScene::musicButtonOnCallBack, this));
	offButtonMusic = MenuItemImage::create("OFF_able.png", "OFF_selected.png", "OFF_un.png",
		CC_CALLBACK_1(OptionScene::musicButtonOffCallBack, this));
	//this->addChild(offButtonMusic, 1, 124);
	offButtonMusic->setEnabled(false);
	auto mnMusic = Menu::create(onButtonMusic, offButtonMusic, NULL);
	mnMusic->setPosition(Vec2(visibleSize.width * 1 / 7 + 70, visibleSize.height * 1 / 8 + 15));
	mnMusic->alignItemsHorizontally();
	this->addChild(mnMusic, 1);

	onButtonSound = MenuItemImage::create("ON_able.png", "ON_selected.png", "ON_un.png",
		CC_CALLBACK_1(OptionScene::soundButtonOnCallBack, this));
	offButtonSound = MenuItemImage::create("OFF_able.png", "OFF_selected.png", "OFF_un.png",
		CC_CALLBACK_1(OptionScene::soundButtonOffCallBack, this));
	//this->addChild(offButtonMusic, 1, 124);
	offButtonSound->setEnabled(false);
	auto mnSound = Menu::create(onButtonSound, offButtonSound, NULL);
	mnSound->setPosition(Vec2(visibleSize.width * 1 / 7 + 390, visibleSize.height * 1 / 8 + 15));
	mnSound->alignItemsHorizontally();
	this->addChild(mnSound, 1);

	//????????????????????????????
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		onButtonMusic->setEnabled(true);
		offButtonMusic->setEnabled(false);
	}
	else {
		onButtonMusic->setEnabled(false);
		offButtonMusic->setEnabled(true);
	}
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		onButtonSound->setEnabled(true);
		offButtonSound->setEnabled(false);
	}
	else {
		onButtonSound->setEnabled(false);
		offButtonSound->setEnabled(true);
	}

	

	auto volumeSprite = Sprite::create("volume.png");
	volumeSprite->setPosition(Vec2(900, 200));
	addChild(volumeSprite);
	auto musicVolumeSlider = Slider::create();
	musicVolumeSlider->loadBarTexture("musicVolumeBg.png");
	musicVolumeSlider->loadSlidBallTextures("musicVolumeBall.png");
	musicVolumeSlider->loadProgressBarTexture("musicVolume.png");
	musicVolumeSlider->setMaxPercent(100.0f);
	musicVolumeSlider->setPosition(Vec2(volumeSprite->getContentSize().width + musicVolumeSlider->getContentSize().width / 2, volumeSprite->getContentSize().height / 2));
	musicVolumeSlider->addEventListener(CC_CALLBACK_2(OptionScene::changeMusicVolumeSlider, this));
	musicVolumeSlider->setPercent(UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME));
	volumeSprite->addChild(musicVolumeSlider);

	musicVolumeSlider->setPercent(UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME));


	auto backButton = MenuItemImage::create("back.png", "back_selected.png", "back.png",
		CC_CALLBACK_1(OptionScene::backCallBack, this));
	auto mnBackMenu = Menu::create(backButton, NULL);
	mnBackMenu->setPosition(Vec2(visibleSize.width * 8 / 10, visibleSize.height * 1 / 8));
	this->addChild(mnBackMenu, 1);
	return true;
}
void OptionScene::musicButtonOnCallBack(Ref* r)
{
	MenuItemImage* onButton = (MenuItemImage*)r;
	offButtonMusic->setEnabled(true);
	onButton->setEnabled(false);
	UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
	AudioEngine::stop(UserDefault::getInstance()->getIntegerForKey(MUSICID));
}
void OptionScene::musicButtonOffCallBack(Ref* r)
{

	MenuItemImage* offButton = (MenuItemImage*)r;
	onButtonMusic->setEnabled(true);
	offButton->setEnabled(false);
	UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
	int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
	if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING) {
		UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(BACKGROUNDA, true));
		AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
	}
}
void OptionScene::soundButtonOnCallBack(Ref* r)
{
	MenuItemImage* onButton = (MenuItemImage*)r;
	offButtonSound->setEnabled(true);
	onButton->setEnabled(false);
	UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
}
void OptionScene::soundButtonOffCallBack(Ref* r)
{
	MenuItemImage* offButton = (MenuItemImage*)r;
	onButtonSound->setEnabled(true);
	offButton->setEnabled(false);
	UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
}
void OptionScene::backCallBack(Ref* r)
{
	Director::getInstance()->popScene();

}


void OptionScene::onEnterTransitionDidFinish()
{
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		int audioId = UserDefault::getInstance()->getIntegerForKey(MUSICID);
		if (AudioEngine::getState(audioId) != AudioEngine::AudioState::PLAYING) {
			UserDefault::getInstance()->setIntegerForKey(MUSICID, AudioEngine::play2d(BACKGROUNDA, true));
			AudioEngine::setVolume(UserDefault::getInstance()->getIntegerForKey(MUSICID), UserDefault::getInstance()->getIntegerForKey(MUSICVOLUME) * 0.01f);
		}
	}
}


void OptionScene::changeMusicVolumeSlider(Ref* r, Slider::EventType type)
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