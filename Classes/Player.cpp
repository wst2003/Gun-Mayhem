#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

//得到人物信息
ActorInformation Player::sendPlayerInformation()
{
	return Actor::actorInformation;
}

//
void Player::actByKeyBoard(std::map<EventKeyboard::KeyCode, bool>& keyMap)
{
	auto velocity = _physicsBody->getVelocity();
	if (keyMap[LEFT_KEY] || keyMap[A_KEY])
		moveOnGround({ -400,velocity.y });
	else if (keyMap[RIGHT_KEY] || keyMap[D_KEY])
		moveOnGround({ 400,velocity.y });
	else if (keyMap[UP_KEY] || keyMap[W_KEY])
		this->jumpUp();
	else if (keyMap[DOWN_KEY] || keyMap[S_KEY])
		this->jumpDown();

	return;
}

//
void Player::actByMouse(std::map<EventMouse::MouseEventType, bool>& mouseMap)
{
	auto position = this->getPosition();
	if (mouseMap[MOUSE_DOWN])
		fire();
	else if (mouseMap[MOUSE_UP])
		stopFire();
	return;
}

void Player::fire()
{
	gun->fire();

	this->_physicsBody->setVelocity({ (this->_flippedX ? 1 : -1) * 400.0f,_physicsBody->getVelocity().y });
}