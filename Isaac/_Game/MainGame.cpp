#include "MainConfig.h"
#include "MainGame.h"

#include "Image.h"

#ifdef _DEBUG
//#define MAPTOOL
#endif

void MainGame::Init()
{
	// Manager
	Input::Init(g_hWnd);
	GET_SINGLETON_IMAGE->Init();
	GET_SINGLETON_SCENE->Init();
	GET_SINGLETON_TIME->Init();

	srand((unsigned int)time(nullptr));
	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	// 백버퍼
	backBuffer = new Image;

#ifdef MAPTOOL
	GET_SINGLETON_SCENE->ChangeScene("EnemyTool");			// TilemapTool / EnemyTool / ObstacleTool
	maxSizeX = TILEMAP_SIZE_X;
	maxSizeY = TILEMAP_SIZE_Y;
#else
	GET_SINGLETON_SCENE->ChangeScene("Stage01");			// Title / Doodle / Stage01
	maxSizeX = WIN_SIZE_X;
	maxSizeY = WIN_SIZE_Y;
#endif

	backBuffer->Init(maxSizeX, maxSizeY);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);			// 백버퍼 삭제
	KillTimer(g_hWnd, 0);				// 타이머 객체 삭제

	// Singleton 삭제
	// Timer
	GET_SINGLETON_TIME->Release();
	GET_SINGLETON_TIME->ReleaseSingleton();
	// Scene
	GET_SINGLETON_SCENE->Release();
	GET_SINGLETON_SCENE->ReleaseSingleton();
	// Image
	GET_SINGLETON_IMAGE->Release();
	GET_SINGLETON_IMAGE->ReleaseSingleton();
}

void MainGame::Update()
{
	Input::Update();

	GET_SINGLETON_TIME->Update();
	GET_SINGLETON_SCENE->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), WHITENESS);

	GET_SINGLETON_SCENE->Render(hBackBufferDC);
	GET_SINGLETON_TIME->Render(hBackBufferDC);

	backBuffer->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
