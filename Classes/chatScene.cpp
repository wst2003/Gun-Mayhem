#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "ChatScene.h"

USING_NS_CC;
using namespace  cocos2d::network;

Scene* ChatScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ChatScene::create();

	scene->addChild(layer);

	return scene;
}

bool ChatScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("backgrounds/ReOrLogbg.png");
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);

	IDQueryEdixBox = ui::EditBox::create(Size(300, 50), ui::Scale9Sprite::create("chatBg.png"));
	IDQueryEdixBox->setAnchorPoint(Point(0, 0));
	IDQueryEdixBox->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 + 100));
	IDQueryEdixBox->setPlaceHolder("Please Enter ID:");//占位字符
	IDQueryEdixBox->setMaxLength(25);
	IDQueryEdixBox->setInputMode(EditBox::InputMode::NUMERIC);
	IDQueryEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	this->addChild(IDQueryEdixBox, 1);

	auto chatMenuItem = MenuItemFont::create("Chat!", CC_CALLBACK_1(ChatScene::chatCallBack, this));
	chatMenuItem->setFontSize(35);
	auto chatMenu = Menu::create(chatMenuItem, NULL);
	chatMenu->setPosition(Vec2(visibleSize.width / 2, 480));
	this->addChild(chatMenu, 1);

	addFriendStatusLabel = Label::createWithTTF(" ", "fonts/Arial.ttf", 35);
	addFriendStatusLabel->setPosition(Vec2(100, 400));
	addFriendStatusLabel->setSystemFontSize(25);
	this->addChild(addFriendStatusLabel, 1);

	auto chatTextBg = Sprite::create("chatTextBg.png");
	chatTextBg->setScaleX(600 / chatTextBg->getContentSize().width);
	chatTextBg->setScaleY(300 / chatTextBg->getContentSize().height);
	chatTextBg->setPosition(Vec2(visibleSize.width / 2+150, 170));
	this->addChild(chatTextBg, 1);

	chatText = Text::create();
	chatText->setAnchorPoint(Vec2(0, 1));
	chatText->setPosition(Vec2(370, 340));
	chatText->setColor(Color3B::WHITE);
	chatText->setContentSize(Size(360, 230));
	chatText->setFontSize(25);
	chatText->setString("input..");
	this->addChild(chatText, 2);

	sendTextEdixBox = ui::EditBox::create(Size(250, 50), ui::Scale9Sprite::create("chatBg.png"));
	sendTextEdixBox->setPosition(Vec2(150, 250));
	sendTextEdixBox->setPlaceHolder("Please Enter Text:");//占位字符
	sendTextEdixBox->setMaxLength(20);
	sendTextEdixBox->setFontSize(32);
	sendTextEdixBox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	this->addChild(sendTextEdixBox, 1);

	auto sendItem = MenuItemFont::create("send!", CC_CALLBACK_1(ChatScene::sendTextCallBack, this));
	sendItem->setFontSize(35);
	auto sendMenu = Menu::create(sendItem, NULL);
	sendMenu->setPosition(Vec2(100,150));
	this->addChild(sendMenu, 1);

	this->schedule(CC_CALLBACK_1(ChatScene::updateNewTextFromFriend, this), 0.1,"upNewText");
	return true;
}

void ChatScene::chatCallBack(Ref* r)
{
	auto ID = IDQueryEdixBox->getText();
	Client::getInstance()->addFriendRequest(ID);
	addFriendStatusLabel->setString("Loading...");
	this->scheduleOnce(CC_CALLBACK_1(ChatScene::updateAddFriendStatus, this), 0.5, "upAdd");
}

void ChatScene::updateAddFriendStatus(float dt)
{
	if (Client::getInstance()->friendID.length() > 0) {
		addFriendStatusLabel->setString("Friend " + Client::getInstance()->friendID + "\n is found!");
	}
	else {
		addFriendStatusLabel->setString("Friend " + Client::getInstance()->friendID + "\n is not found!");
	}
}

void ChatScene::sendTextCallBack(Ref* r)
{
	std::string textToFriend = sendTextEdixBox->getText();
	Client::getInstance()->sendTextToFriend(textToFriend, Client::getInstance()->friendID);
	if (Client::getInstance()->friendID.length() > 0) {
		this->chatText->setString(this->chatText->getString() + "\n" + Client::getInstance() ->myID+":"+textToFriend);
	}
}

void ChatScene::updateNewTextFromFriend(float dt)
{
	if (Client::getInstance()->hasNewChatText) {
		this->chatText->setString(this->chatText->getString() + "\n"+ Client::getInstance()->friendID+":"
			+ Client::getInstance()->textFromFriend);
		Client::getInstance()->hasNewChatText = false;
		Client::getInstance()->textFromFriend = "";
	}
}