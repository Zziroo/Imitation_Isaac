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
	return (currKeyStates[vkey] && prevKeyStates[vkey]);			// ��� ���� ������ ��
}

bool Input::GetButtonDown(BYTE vkey) noexcept
{
	return (currKeyStates[vkey] && prevKeyStates[vkey] == false);	// �ѹ� ������ ��
}

bool Input::GetButtonUp(BYTE vkey) noexcept
{
	return (currKeyStates[vkey] == false && prevKeyStates[vkey]);	// ���� ��
}

POINT Input::GetMousePosition() noexcept
{
	return mousePosition;
}
