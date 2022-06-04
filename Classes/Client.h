#pragma once
#include "cocos2d.h"
#include "network/SocketIO.h"
USING_NS_CC;

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
	void getAddFriendResult(cocos2d::network::SIOClient* client, const std::string& reply) ;
	void sendTextToFriend(std::string& text, std::string friendID);
	void getTextFromFriend(cocos2d::network::SIOClient* client, const std::string& text) ;

	void readRankingRequest(const std::string& ID);
	void getRankingData(cocos2d::network::SIOClient* client, const std::string& text);

	void inviteFriend(const std::string& ID);
	void getInviteFriend(cocos2d::network::SIOClient* client, const std::string& ID);

	static bool getIsRegister();
	static bool getIsLogin();
	std::string myID;
	std::string friendID="";
	bool hasNewChatText = false;
	std::string textFromFriend = "";
private:
	Client();
	static Client* myClient;
	cocos2d::network::SIOClient* _sioClient;
	std::string serverIp;


	static bool isRegister ;
	static bool isLogin ;
};