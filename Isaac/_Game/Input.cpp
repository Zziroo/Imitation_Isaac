#include "MainConfig.h"
#include "Input.h"

bool Input::currKeyStates[KEY_MAX_COUNT] = { false };
bool Input::prevKeyStates[KEY_MAX_COUNT] = { false };
POINT Input::mousePosition = {};
HWND Input::_hWnd = {};

void Input::Init(HWND hWnd) noexcept
{
	_hWnd = hWnd;
}

void Input::Update() noexcept
{
	memcpy(prevKeyStates, currKeyStates, sizeof(currKeyStates));

	for (size_t vkey = 0; vkey < KEY_MAX_COUNT; ++vkey)
	{
		if (GetAsyncKeyState(vkey) & 0x8000)
		{
			currKeyStates[vkey] = true;
		}
		else
		{
			currKeyStates[vkey] = false;
		}
	}

	GetCursorPos(&mousePosition);
	ScreenToClient(_hWnd, &mousePosition);
}

bool Input::GetButton(BYTE vkey) noexcept
{
	return (currKeyStates[vkey] && prevKeyStates[vkey]);			// 계속 누른 상태일 때
}

bool Input::GetButtonDown(BYTE vkey) noexcept
{
	return (currKeyStates[vkey] && prevKeyStates[vkey] == false);	// 한번 눌렀을 때
}

bool Input::GetButtonUp(BYTE vkey) noexcept
{
	return (currKeyStates[vkey] == false && prevKeyStates[vkey]);	// 땠을 때
}

POINT Input::GetMousePosition() noexcept
{
	return mousePosition;
}
