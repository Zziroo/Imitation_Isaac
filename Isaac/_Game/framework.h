#pragma once

#define WIN32_LEAN_AND_MEAN			// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#include <crtdbg.h>
#endif

// Windows 헤더 파일
#include <Windows.h>

#include <array>
#include <bitset>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

#include "Singleton.h"

using namespace std;
using namespace std::chrono;

#define WIN_START_POS_X			0
#define WIN_START_POS_Y			0
#define WIN_SIZE_X				1280
#define WIN_SIZE_Y				800
#define TILEMAP_SIZE_X			1440
#define TILEMAP_SIZE_Y			900

extern HINSTANCE				_hInst;
extern HWND						_hWnd;
extern POINT					_ptMouse;

inline void SetWindowSize(int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	int x, y, width, height;
	RECT rc, rcDesk;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX; rc.bottom = sizeY;
	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	GetWindowRect(GetDesktopWindow(), &rcDesk);

	width = rc.right - rc.left;
	height = rc.bottom - rc.top;

	x = (rcDesk.right - width) / 2;
	y = (rcDesk.bottom - height) / 2;

	// 윈도우 창을 중앙으로 조정
	MoveWindow(_hWnd, x, y, width, height, TRUE);
}

#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }

#define KEY_MAX_COUNT			256

#include "Input.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "Timer.h"

#define GET_SINGLETON_IMAGE	ImageManager::GetSingleton()
#define GET_SINGLETON_SCENE	SceneManager::GetSingleton()

#define MAGENTA					RGB(255, 0, 255)

#include "Global.h"
#include "Maptool.h"