#pragma once

class Image;
class MainGame
{
private:
	HANDLE	hTimer = 0;					// Ÿ�̸�
	int		maxSizeX = 0;				// SIZE_X
	int		maxSizeY = 0;				// SIZE_X
	Image*	backBuffer = nullptr;		// �����

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};