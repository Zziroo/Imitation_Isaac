#pragma once

#include <bitset>
#include <iostream>
#include <map>
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

#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

#define GET_SINGLETON_IMAGE	ImageManager::GetSingleton()
#define GET_SINGLETON_KEY	KeyManager::GetSingleton()
#define GET_SINGLETON_SCENE	SceneManager::GetSingleton()
#define GET_SINGLETON_TIME	TimeManager::GetSingleton()

#define MAGENTA				RGB(255, 0, 255)

// GameObject
enum class ObjectStates { IDLE, WALK, ATTACK, HURT, ITEMPICKUP, JUMP, STAT };

#define ADVANCE_FRAME		1

#define DEVIDE_HALF			0.5f

#define ZERO				0

// Button
typedef struct ArgumentFuncPtr
{

} ARGUMENT_PTR, *LPARGUMENT_PTR;

// Player
#define ADJUST_SIZE_05			5
#define ADJUST_SIZE_09			9
#define ADJUST_SIZE_14			14
#define ADJUST_SIZE_30			30

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
#define PLAYER_MOVESPEED		100.0f
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
