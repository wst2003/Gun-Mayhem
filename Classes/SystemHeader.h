#pragma once
#include "AudioEngine.h"

//音乐
#define MUSICID "musicid"
#define MUSIC_KEY "music_key"
#define SOUND_KEY "sound_key"
#define BACKGROUNDA "1.mp3"
#define BACKGROUNDB "2.mp3"
#define BACKGROUNDC "3.mp3"
#define BACKGROUNDD "4.mp3"
#define CLICKSOUND "fire.mp3"
#define MUSICVOLUME "musicVolume"
#define ISPLAYGAME "isPlayGame"


#define NUM_MAP 5
#define MAPID "mapid"
#define UPKEY "upkey"
#define DOWNKEY "downkey"
#define LEFTKEY "leftkey"
#define RIGHTKEY "rightkey"

//tag 标签设置
#define SPAY 45456

#define GROUND 400
#define MAP 140

#define MAP1 111
#define MAP2 112
#define MAP3 113
#define MAP4 114

#define FOOTSTEP 200
#define PLAYER 101
#define ACTOR 101
#define ENEMY 104
#define GUN 105
#define EDGE 1002
#define BULLET 100
#define BOX 106

//掩码体系
//category 与 collision 做  & 不为0
#define PLAYER_COLLISION_BITMASK (1<<30)+1
#define PLAYER_CATEGORY_BITMASK (1<<30)+1

#define ENEMY_COLLISION_BITMASK (1<<29)+8
#define	ENEMY_CATEGORY_BITMASK (1<<29)+8

#define ACTOR_CHANGED_COLLISION_BITMASK 64
#define ACTOR_CHANGED_CATEGORY_BITMASK 16

#define	FOOTSTEP_COLLISION_BITMASK 47
#define FOOTSTEP_CATEGORY_BITMASK 47

#define EDGE_COLLISION_BITMASK 0xFFFFFFFF
#define EDGE_CATEGORY_BITMASK 0xFFFFFFFF

#define	BULLET_COLLISION_BITMASK (1<<30)+8
#define BULLET_CATEGORY_BITMASK (1<<29)+1

#define GUN_COLLISION_BITMASK 32
#define GUN_CATEGORY_BITMASK 32

#define GUN_CHANGED_COLLISION_BITMASK 16
#define GUN_CHANGED_CATEGORY_BITMASK 16

#define BOX_COLLISION_BITMASK 32
#define BOX_CATEGORY_BITMASK 32

#define BOX_CHANGED_COLLISION_BITMASK 0
#define BOX_CHANGED_CATEGORY_BITMASK 0

//鼠标与键盘按键
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

//枪支属性
#define HANDGUN_ARR {20,0.5,10,400,2000}
#define SNIPERGUN_ARR {7,1,30,600,2800}
#define ARGUN_ARR {50,0.20,4,200,2800}
#define BOMB {3,1.5,50,200,1500}

//枪支类型
#define HANDGUN_TYPE 1;
#define SNIPERGUN_TYPE 2;
#define ARGUN_TYPE 3;

//枪支名
#define HANDGUN_FILENAME "369.png"
#define SNIPERGUN_FILENAME "489.png"
#define ARGUN_FILENAME "469.png"

#define BRAND_NAME 455
#define BRAND_BULLETLEFT 456
#define BRAND_LIFELEFT 457
#define BRAND_BLOODPERCENT 458

//速度设置
#define SPEED_LEFT -350
#define SPEED_RIGHT 350
#define SPEED_UP 780

#define BOMB_FILENAME "bomb.png"