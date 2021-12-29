#include "stdafx.h"
#include "Game.h"

#include "Image.h"
#include "Timer.h"

#ifdef _DEBUG
//#define MAPTOOL
#endif

LRESULT Game::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

bool Game::Init(HINSTANCE hInst)
{
	_hInst = hInst;

	if (0 == registerClass())
	{
		return false;
	}

	_hWnd = CreateWindow(_lpszClass, _lpszClass, WS_OVERLAPPEDWINDOW, WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y, NULL, NULL, _hInst, NULL);

	if (_hWnd == NULL)
	{
		return false;
	}

	SetWindowSize(WIN_SIZE_X, WIN_SIZE_Y);

	ShowWindow(_hWnd, SW_SHOW);
	UpdateWindow(_hWnd);

	_hDC = GetDC(_hWnd);
	_backDC = CreateCompatibleDC(_hDC);
	_backBitmap = CreateCompatibleBitmap(_hDC, WIN_SIZE_X, WIN_SIZE_Y);
	SelectObject(_backDC, _backBitmap);

	// Manager
	Input::Init(_hWnd);
	GET_SINGLETON_IMAGE->Init();
	GET_SINGLETON_SCENE->Init();

	// 백버퍼
	backBuffer = new Image;

#ifdef MAPTOOL
	GET_SINGLETON_SCENE->ChangeScene("TilemapTool");		// TilemapTool / EnemyTool / ObstacleTool
	maxSizeX = TILEMAP_SIZE_X;
	maxSizeY = TILEMAP_SIZE_Y;
#else
	GET_SINGLETON_SCENE->ChangeScene("Title");				// Title / Doodle / Stage01
	maxSizeX = WIN_SIZE_X;
	maxSizeY = WIN_SIZE_Y;
#endif

	backBuffer->Init(maxSizeX, maxSizeY);

	return true;
}

INT32 Game::Run()
{
	Timer::Init();

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (Timer::CanUpdate())
			{
				update();
				render();
			}
		}
	}

	return static_cast<INT32>(msg.wParam);
}

Game::~Game() noexcept
{
	SAFE_RELEASE(backBuffer);			// 백버퍼 삭제

	// Scene
	GET_SINGLETON_SCENE->Release();
	GET_SINGLETON_SCENE->ReleaseSingleton();
	// Image
	GET_SINGLETON_IMAGE->Release();
	GET_SINGLETON_IMAGE->ReleaseSingleton();

	DeleteObject(_backBitmap);
	DeleteDC(_backDC);
	ReleaseDC(_hWnd, _hDC);
}

ATOM Game::registerClass()
{
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInst;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = _lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	return RegisterClass(&wndClass);
}

void Game::update()
{
	Input::Update();

	GET_SINGLETON_SCENE->Update();

	InvalidateRect(_hWnd, NULL, false);
}

void Game::render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), WHITENESS);

	GET_SINGLETON_SCENE->Render(hBackBufferDC);

	backBuffer->Render(_hDC);
}
