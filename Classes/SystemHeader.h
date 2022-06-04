#pragma once
#include "AudioEngine.h"
#define MUSICID "musicid"
#define MUSIC_KEY "music_key"
#define SOUND_KEY "sound_key"
#define BACKGROUNDA "1.mp3"
#define CLICKSOUND "sound/click.m4a"

#define NUM_MAP 5
#define MAPID "mapid"
#define UPKEY "upkey"
#define DOWNKEY "downkey"
#define LEFTKEY "leftkey"
#define RIGHTKEY "rightkey"

#define GROUND 400
#define MAP 140
#define FOOTSTEP 200
#define PLAYER 101
#define ACTOR 101
#define ENEMY 104
#define GUN 105
#define EDGE 1002
#define BULLET 100
#define BOX 106

//category 与 collision 做  & 不为0
#define PLAYER_COLLISION_BITMASK 1
#define PLAYER_CATEGORY_BITMASK 1

#define ENEMY_COLLISION_BITMASK 2
#define	ENEMY_CATEGORY_BITMASK 2

#define ACTOR_CHANGED_COLLISION_BITMASK 64
#define ACTOR_CHANGED_CATEGORY_BITMASK 16

#define	FOOTSTEP_COLLISION_BITMASK 47
#define FOOTSTEP_CATEGORY_BITMASK 47

#define EDGE_COLLISION_BITMASK 0xFFFFFFFF
#define EDGE_CATEGORY_BITMASK 0xFFFFFFFF

#define	BULLET_COLLISION_BITMASK 15
#define BULLET_CATEGORY_BITMASK 15

#define GUN_COLLISION_BITMASK 32
#define GUN_CATEGORY_BITMASK 32

#define GUN_CHANGED_COLLISION_BITMASK 16
#define GUN_CHANGED_CATEGORY_BITMASK 16

#define BOX_COLLISION_BITMASK 32
#define BOX_CATEGORY_BITMASK 32

#define BOX_CHANGED_COLLISION_BITMASK 0
#define BOX_CHANGED_CATEGORY_BITMASK 0

#define LEFT_KEY EventKeyboard::KeyCode::KEY_LEFT_ARROW
#define RIGHT_KEY EventKeyboard::KeyCode::KEY_RIGHT_ARROW
#define UP_KEY EventKeyboard::KeyCode::KEY_UP_ARROW
#define A_KEY EventKeyboard::KeyCode::KEY_A
#define W_KEY EventKeyboard::KeyCode::KEY_W
#define D_KEY EventKeyboard::KeyCode::KEY_D
#define DOWN_KEY EventKeyboard::KeyCode::KEY_DOWN_ARROW
#define S_KEY EventKeyboard::KeyCode::KEY_S
#define P_KEY EventKeyboard::KeyCode::KEY_P

#define MOUSE_DOWN EventMouse::MouseEventType::MOUSE_DOWN
#define MOUSE_UP EventMouse::MouseEventType::MOUSE_UP
#define MOUSE_MOVE EventMouse::MouseEventType::MOUSE_MOVE

//must be edited
#define HANDGUN_ARR {20,0.5,10,8,2000}
#define SNIPERGUN_ARR {7,1,30,20,2800}
#define ARGUN_ARR {50,0.1,4,6,2800}

#define HANDGUN_TYPE 1;
#define SNIPERGUN_TYPE 2;
#define ARGUN_TYPE 3;

#define HANDGUN_FILENAME "369.png"
#define SNIPERGUN_FILENAME "489.png"
#define ARGUN_FILENAME "469.png"

#define BRAND_NAME 455
#define BRAND_BULLETLEFT 456
#define BRAND_LIFELEFT 457
#define BRAND_BLOODPERCENT 458