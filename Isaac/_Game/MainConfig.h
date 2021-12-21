#pragma once

#include <array>
#include <bitset>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>
#include <Windows.h>

#include "Singleton.h"

using namespace std;

#pragma comment(lib, "winmm.lib")

#define WIN_START_POS_X		0
#define WIN_START_POS_Y		0
#define WIN_SIZE_X			1280
#define WIN_SIZE_Y			800
#define TILEMAP_SIZE_X		1440
#define TILEMAP_SIZE_Y		900

extern HINSTANCE			g_hInstance;
extern HWND					g_hWnd;
extern POINT				g_ptMouse;

inline void SetWindowSize(int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	int x, y, width, height;
	RECT rc, rcDesk;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX; rc.bottom = sizeY;
	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	GetWindowRect(GetDesktopWindow(), &rcDesk);

	width = rc.right - rc.left;
	height = rc.bottom - rc.top;

	x = (rcDesk.right - width) / 2;
	y = (rcDesk.bottom - height) / 2;

	// 윈도우 창을 중앙으로 조정
	MoveWindow(g_hWnd, x, y, width, height, TRUE);
}

#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }

#define KEY_MAX_COUNT		256

#include "Input.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

#define GET_SINGLETON_IMAGE	ImageManager::GetSingleton()
#define GET_SINGLETON_SCENE	SceneManager::GetSingleton()
#define GET_SINGLETON_TIME	TimeManager::GetSingleton()

#define MAGENTA				RGB(255, 0, 255)

// GameObject
enum class			ObjectDir { UP, DOWN, LEFT, RIGHT, NONE };	// 이동 방향

#define ADVANCE_FRAME		1

#define DEVIDE_HALF			0.5f

#define ZERO				0

// Player
enum class PlayerStates { IDLE, WALK, ATTACK, HURT, ITEMPICKUP, JUMP, STAT };

#define ADJUST_SIZE_05			5
#define ADJUST_SIZE_09			9
#define ADJUST_SIZE_14			14
#define ADJUST_SIZE_15			15
#define ADJUST_SIZE_30			30
#define ADJUST_SIZE_40			40

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

// Weapon
#define WEAPON_MAX_COUNT		100

// TilemapTool
enum class TileTypes { CLIFF, DOOR, ROAD, WALL, NOTHINGNESS }; 
enum class SampleTileTypes { BASEMENT, CAVE, CELLAR, DEPTH, NONE };

typedef struct tagSampleTile
{
	RECT		rc = {};
	int			frameX = 0;
	int			frameY = 0;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	RECT		rc = {};
	int			frameX = 0;
	int			frameY = 0;
	TileTypes	terrain = TileTypes::WALL;
} TILE_INFO;

#define TILE_SIZE				40
#define	TILE_COLUMN				32
#define TILE_ROW				20
#define BASEMENT_TILE_ROW		80
#define CAVE_TILE_ROW			120
#define CELLAR_TILE_ROW			80
#define DEPTH_TILE_ROW			60
#define SAMPLE_TILE_SIZE		14
#define SAMPLE_TILE_COLUMN		33
#define SAMPLE_TILE_ROW			20

inline void SetTerrain(TILE_INFO* rc, int index)
{
	// WALL로 설정
	if (0 <= rc->frameX && rc->frameX < 32)
	{
		for (int r = 0; r < index; ++r)
		{
			if (0 + (r * TILE_ROW) <= rc->frameY && rc->frameY < (r + 1) * TILE_ROW)
			{
				rc->terrain = TileTypes::WALL;
			}
		}
	}
	// DOOR로 설정/상/하
	if (15 <= rc->frameX && rc->frameX < 17)
	{
		for (int r = 0; r < index; ++r)
		{
			if (1 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 3 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::DOOR;
			}
			if (17 + (r * TILE_ROW) <= rc->frameY && rc->frameY < ((r + 1) * TILE_ROW) - 1)
			{
				rc->terrain = TileTypes::DOOR;
			}
		}
	}
	// DOOR로 설정/좌/우
	if (1 <= rc->frameX && rc->frameX < 31)
	{
		for (int r = 0; r < index; ++r)
		{
			if (9 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 11 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::DOOR;
			}
		}
	}
	// ROAD로 설정
	if (3 <= rc->frameX && rc->frameX < 29)
	{
		for (int r = 0; r < index; ++r)
		{
			if (3 + (r * TILE_ROW) <= rc->frameY && rc->frameY < 17 + (r * TILE_ROW))
			{
				rc->terrain = TileTypes::ROAD;
			}
		}
	}
	if (rc->frameX == 32 && rc->frameY == 0)
	{
		rc->terrain = TileTypes::ROAD;
	}

	// 빈 공간
	if (rc->frameX == 32)
	{
		for (int r = 0; r < index; ++r)
		{
			if (0 < rc->frameY && rc->frameY < (r + 1) * TILE_ROW)
			{
				rc->terrain = TileTypes::NOTHINGNESS;
			}
		}
	}
}

// RoomEditing
enum class RoomTypes { BOSS, CURSE, ITEM, NORMAL, PRIVATE, SATAN, START, NONE };

// DoorEditing
enum class DoorStates { OPENED, CLOSED, LOCKED, NONE };

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

// ObstacleTool
typedef struct tagStoreSampleInfo
{
	ObstacleTypes				sampleType = ObstacleTypes::NONE;
	POINTFLOAT					pos = {};
} STORE_OBSTACLE_INFO;