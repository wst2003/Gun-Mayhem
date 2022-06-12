#pragma once
#include "cocos2d.h"
#include "network/SocketIO.h"
#include "Actor.h"
USING_NS_CC;

//客户端类，采用单例化设计模式
class Client :public cocos2d::network::SocketIO::SIODelegate
{
public:
	static Client* getInstance();

	virtual void onConnect(cocos2d::network::SIOClient* client);
	virtual void onMessage(cocos2d::network::SIOClient* client, const std::string& data);
	virtual void onClose(cocos2d::network::SIOClient* client);
	virtual void onError(cocos2d::network::SIOClient* client, const std::string& data);

	void registerIDRequest(std::string ID);
	void getRegisterResult(cocos2d::network::SIOClient* client, const std::string& reply);

	void loginRequest(std::string ID);
	void getLoginResult(cocos2d::network::SIOClient* client, const std::string& reply);
	void loginLegally(std::string ID);

	void addFriendRequest(std::string ID);
	void getAddFriendResult(cocos2d::network::SIOClient* client, const std::string& reply);
	void sendTextToFriend(std::string& text, std::string friendID);
	void getTextFromFriend(cocos2d::network::SIOClient* client, const std::string& text);

	void readRankingRequest(const std::string& ID);
	void getRankingData(cocos2d::network::SIOClient* client, const std::string& text);

	void inviteFriend(const std::string& ID);
	void getInviteFriend(cocos2d::network::SIOClient* client, const std::string& ID);

	void startGame(const std::string& ID);
	void getStartGame(cocos2d::network::SIOClient* client, const std::string& ID);

	void sendInfo(const std::string& info);
	void getInfo(cocos2d::network::SIOClient* client, const std::string& info);


	static bool getIsRegister();
	static bool getIsLogin();
	static bool getIsServerConnected();

	std::string myID;
	std::string friendID = "";
	bool hasNewChatText = false;
	std::string textFromFriend = "";
private:
	Client();
	static Client* myClient;
	cocos2d::network::SIOClient* _sioClient;
	std::string serverIp;


	static bool isRegister;
	static bool isLogin;
	static bool isServerConnected;
};