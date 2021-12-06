#pragma once

class Input
{
private:
	static bool		currKeyStates[KEY_MAX_COUNT];
	static bool		prevKeyStates[KEY_MAX_COUNT];
	static POINT	mousePosition;
	static HWND		_hWnd;

public:
	Input() = delete;
	~Input() = delete;

	static void		Init(HWND hWnd) noexcept;
	static void		Update() noexcept;

	static bool		GetButton(BYTE vkey) noexcept;
	static bool		GetButtonDown(BYTE vkey) noexcept;
	static bool		GetButtonUp(BYTE vkey) noexcept;

	static POINT	GetMousePosition() noexcept;
};

