#pragma once

class Image;
class Game
{
private:
	enum { MAX_LOADSTARING = 100 };

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Image*		backBuffer = nullptr;

	HBITMAP		_backBitmap = {};
	HDC			_hDC = {};
	HDC			_backDC = {};
	LPSTR		_lpszClass = (LPSTR)TEXT("Isaac: Rebirth");

	INT32		maxSizeX = 0;				// SIZE_X
	INT32		maxSizeY = 0;				// SIZE_X

public:
	bool		Init(HINSTANCE hInst);
	INT32		Run();

	~Game() noexcept;

private:
	ATOM		registerClass();

	void		update();
	void		render();
};

