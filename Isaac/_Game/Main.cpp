// Main.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "MainConfig.h"
#include "Game.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

HINSTANCE	_hInst;
HWND		_hWnd;
POINT		_ptMouse;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(545);
#endif
	Game game;

	if (false == game.Init(hInstance))
	{
		return 0;
	}

	INT32 res = game.Run();

	return res;
}