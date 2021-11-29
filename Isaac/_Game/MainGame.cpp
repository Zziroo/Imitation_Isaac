#include "MainConfig.h"
#include "MainGame.h"

#include "Image.h"

void MainGame::Init()
{
	//Singleton
	GETSINGLETON_KEY->Init();
	GETSINGLETON_IMAGE->Init();
	GETSINGLETON_SCENE->Init();
	GETSINGLETON_TIME->Init();

	//GETSINGLETON_SCENE->AddScene("TestScene", new TestScene());

	//GETSINGLETON_SCENE->ChangeScene("TestScene");

	srand((unsigned int)time(nullptr));
	//타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	//백버퍼
	backBuffer = new Image;
	maxSizeX = WIN_SIZE_X;
	maxSizeY = WIN_SIZE_Y;
	backBuffer->Init(maxSizeX, maxSizeY);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);			//백버퍼 삭제
	KillTimer(g_hWnd, 0);				//타이머 객체 삭제

	//Singleton 삭제
	//Timer
	GETSINGLETON_TIME->Release();
	GETSINGLETON_TIME->ReleaseSingleton();
	//Scene
	GETSINGLETON_SCENE->Release();
	GETSINGLETON_SCENE->ReleaseSingleton();
	//Key
	GETSINGLETON_KEY->Release();
	GETSINGLETON_KEY->ReleaseSingleton();
	//Image
	GETSINGLETON_IMAGE->Release();
	GETSINGLETON_IMAGE->ReleaseSingleton();
}

void MainGame::Update()
{
	GETSINGLETON_TIME->Update();
	GETSINGLETON_SCENE->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), WHITENESS);

	GETSINGLETON_SCENE->Render(hBackBufferDC);
	GETSINGLETON_TIME->Render(hBackBufferDC);

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
