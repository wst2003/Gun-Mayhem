#include "StartGameScene.h"
#include "Client.h"
#include "cocos2d.h"
#include "network/SocketIO.h"

USING_NS_CC;
using namespace  cocos2d::network;

Client* Client::myClient = nullptr;
bool Client::isRegister = false;
bool Client::isLogin = false;

Client::Client()
{
	serverIp = "http://192.168.3.7:3000/";
	//serverIp = "http://180.160.2.227:3000/";
	_sioClient = SocketIO::connect(serverIp, *this);
	_sioClient->on("getRegisterResult", CC_CALLBACK_2(Client::getRegisterResult, this));
	_sioClient->on("getLoginResult", CC_CALLBACK_2(Client::getLoginResult, this));
	_sioClient->on("getAddFriendResult", CC_CALLBACK_2(Client::getAddFriendResult, this));
	_sioClient->on("getTextFromFriend", CC_CALLBACK_2(Client::getTextFromFriend, this));
	_sioClient->on("getRankingData", CC_CALLBACK_2(Client::getRankingData, this));
}

Client* Client::getInstance()
{
	if (myClient == nullptr) {
		myClient = new Client();
		return myClient;
	}
	return myClient;
}

bool Client::getIsRegister() 
{
	return isRegister;
}

bool Client::getIsLogin()
{
	return isLogin;
}

void Client::onConnect(cocos2d::network::SIOClient* client)
{
	log("HelloWorld::onConnect called");
 }
void Client::onMessage(cocos2d::network::SIOClient* client, const std::string& data)
{
	log("HelloWorld::onMessage received: %s", data.c_str());
 };

void Client::onClose(cocos2d::network::SIOClient* client)
{
	log("HelloWorld::onClose called");
 };

void Client::onError(cocos2d::network::SIOClient* client, const std::string& data)
{
	log("HelloWorld::onError received: %s", data.c_str());
 };

void Client::registerIDRequest(std::string ID)
{
	_sioClient->emit("getRegisterIDRequest", ID);
}

void Client::getRegisterResult(cocos2d::network::SIOClient* client, const std::string& reply)
{
	if (reply.compare("\"1\"")==0) {
		Client::isRegister =true;
		if (Client::getIsRegister()) {
			log("REGISTER");
		}
		log("register succeed!");
	}
	else {
		isRegister = false;
		log("register failed!");
	}
	
}

void Client::loginRequest(std::string ID)
{
	_sioClient->emit("getLoginRequest", ID);
	myID = ID;
}

void Client::getLoginResult(cocos2d::network::SIOClient* client, const std::string& reply)
{
	log(reply.c_str());
	if (reply.compare("\"1\"") == 0) {
		Client::isLogin = true;
		loginLegally(myID);
		log("login succeed!");
	}
	else {
		isLogin = false;
		myID = "";
		log("login failed!");
	}
}

void Client::loginLegally(std::string ID)
{
	_sioClient->emit("login", ID);
}

void Client::addFriendRequest(std::string ID)
{
	_sioClient->emit("getAddFriendRequest", {myID,ID});
}

void Client::getAddFriendResult(cocos2d::network::SIOClient* client, const std::string& reply)
{
	auto tmp = reply;
	tmp.erase(tmp.begin());
	tmp.erase(tmp.end() - 1);
	auto isAdd = *(tmp.end() - 1);
	tmp.erase(tmp.end() - 1);
	auto friendID = tmp;
	if (isAdd == '1') {
		this->friendID = friendID;
	}
	else {
		this->friendID = "";
	}
}

void Client::sendTextToFriend(std::string& text, std::string friendID)
{
	if (friendID.length() == 0) {
		log("You have not found a friend!");
		return;
	}
	_sioClient->emit("sendTextByFriendID", { friendID,myID,text });
}

void Client::getTextFromFriend(cocos2d::network::SIOClient* client, const std::string& text)
{
	auto data = text;
	data.erase(data.begin());
	data.erase(data.end() - 1);
	auto friendID = data.substr(0, data.find_first_of('|'));
	auto textFromFriend = data.substr(data.find_first_of('|') + 1, data.length() - friendID.length() - 1);
	this->friendID = friendID;
	this->textFromFriend = textFromFriend;
	this->hasNewChatText = true;

}

void Client::readRankingRequest(const std::string& ID)
{
	_sioClient->emit("getReadRankingRequest", ID);
}

void Client::getRankingData(cocos2d::network::SIOClient* client, const std::string& text)
{
	auto data = text;
	data.erase(data.begin());
	data.erase(data.end() - 1);
	auto aID = data.substr(0, data.find_first_of('|'));
	auto score = data.substr(data.find_first_of('|') + 1, data.length() - aID.length() - 1);
	log(aID.c_str());
	log(score.c_str());
}
