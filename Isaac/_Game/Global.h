#pragma once

// GameObject
enum class ObjectDir { UP, DOWN, LEFT, RIGHT, NONE };	// 이동 방향

#define ADJUST_SIZE_05			5
#define ADJUST_SIZE_09			9
#define ADJUST_SIZE_10			10
#define ADJUST_SIZE_14			14
#define ADJUST_SIZE_15			15
#define ADJUST_SIZE_30			30
#define ADJUST_SIZE_40			40

#define ADVANCE_FRAME			1

#define BLINK_IMAGE_FRAME		1

#define DEVIDE_HALF				0.5f

#define ZERO					0

// Player
enum class PlayerStates { IDLE, WALK, ATTACK, DEAD, HURT, ITEMPICKUP, JUMP, STAT };

#define PLAYER_BODY_POS_X		PLAYER_HEAD_POS_X
#define PLAYER_BODY_POS_Y		PLAYER_HEAD_POS_Y + 42.5f
#define PLAYER_BODYSIZE			25.0f
#define START_BODY_FRAME_X		0
#define MAX_BODY_FRAME_X		9
#define BODY_DEFAULT_DIR		0
#define BODY_RIGHT_DIR			1
#define BODY_LEFT_DIR			2

#define PLAYER_HEAD_POS_X		WIN_SIZE_X * 0.5f
#define PLAYER_HEAD_POS_Y		WIN_SIZE_Y * 0.5f
#define PLAYER_HEADSIZE			70.0f
#define PLAYER_MOVESPEED		500.0f
#define HEAD_LOOK_DOWN			0
#define ATTACKING_DOWNSIDE		1
#define HEAD_LOOK_RIGHT			2
#define ATTACKING_RIGHTSIDE		3
#define HEAD_LOOK_UP			4
#define ATTACKING_UPSIDE		5
#define HEAD_LOOK_LEFT			6
#define ATTACKING_LEFTSIDE		7

#define HURT_IMAGE				1

// PlayerTear
#define MAX_COUNT				50

// RoomEditing
enum class RoomTypes { BOSS, CURSE, ITEM, NORMAL, PRIVATE, SATAN, START, NONE };

// DoorEditing
enum class DoorStates { OPENED, CLOSED, LOCKED, NONE };

#define OPENED_STATE_DOOR 0
#define CLOSED_STATE_DOOR 1
#define LOCKED_STATE_DOOR 2

typedef struct tagDoorInfo
{
	Image* img = nullptr;

	DoorStates					doorState = DoorStates::NONE;
	ObjectDir					doorDir = ObjectDir::NONE;
	RoomTypes					roomType = RoomTypes::NONE;

	POINTFLOAT					pos = {};
	RECT						shape = {};
} DOOR_INFO;

#define UPPER_DOOR				0
#define LOWER_DOOR				1
#define	LEFT_DOOR				2
#define	RIGHT_DOOR				3

#define OUT_OF_STAGE			0

// Obstacle
enum class ObstacleTypes { BONFIRE, BRICK, DDONG, ITEMSTAND, JAR, SLIDER, SPIDERWEB, STONE, THORN, NONE };

// NormalMonster
enum class NormalMonsterTypes { FLY, ATTACKFLY, POOTER, NONE };

// Boss Monster
enum class BossMonsterTypes { DUKE, NONE };

// AStar
struct Pos
{
	int					X = 0;
	int					Y = 0;

	bool operator<(const Pos& other) const { return (X < other.X) && (Y < other.Y); }
	bool operator==(const Pos& other) const { return X == other.X && Y == other.Y; }
	bool operator!=(const Pos& other) const { return !(*this == other); }
};

#define INF						1e9
#define IMPASSABLE_ROAD			1e3
