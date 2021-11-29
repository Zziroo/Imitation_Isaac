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

#define WIN_START_POS_X 0
#define WIN_START_POS_Y 0
#define WIN_SIZE_X		1280
#define WIN_SIZE_Y		800

extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;

inline void SetWindowSize(int sizeX, int sizeY)
{
	// ���ϴ� ������ �۾����� ����
	int x, y, width, height;
	RECT rc, rcDesk;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX; rc.bottom = sizeY;
	// ��Ÿ���� ���Ե� ���� ������ ũ�� ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	GetWindowRect(GetDesktopWindow(), &rcDesk);

	width = rc.right - rc.left;
	height = rc.bottom - rc.top;

	x = (rcDesk.right - width) / 2;
	y = (rcDesk.bottom - height) / 2;

	// ������ â�� �߾����� ����
	MoveWindow(g_hWnd, x, y, width, height, TRUE);
}

#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }

#define KEY_MAX_COUNT		256

#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

#define GETSINGLETON_IMAGE	ImageManager::GetSingleton()
#define GETSINGLETON_KEY	KeyManager::GetSingleton()
#define GETSINGLETON_SCENE	SceneManager::GetSingleton()
#define GETSINGLETON_TIME	TimeManager::GetSingleton()

#define MAGENTA				RGB(255, 0, 255)

enum class ObjectStates { IDLE, WALK, HURT, ITEMPICKUP, JUMP, STAT };

#define PLAYER_IMAGE_SCALE	3