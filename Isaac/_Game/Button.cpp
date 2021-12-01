#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	Button::FindIamge();

	exitBtn.pos.x = (FLOAT)(TILEMAP_SIZE_X - 210);
	exitBtn.pos.y = (FLOAT)(TILEMAP_SIZE_Y - 70);
	exitBtn.shape.left = (LONG)(exitBtn.pos.x - (exitBtn.button->GetFrameWidth() * DEVIDE_HALF));
	exitBtn.shape.top = (LONG)(exitBtn.pos.y - (exitBtn.button->GetFrameHeight() * DEVIDE_HALF));
	exitBtn.shape.right = (LONG)(exitBtn.pos.x + (exitBtn.button->GetFrameWidth() * DEVIDE_HALF));
	exitBtn.shape.bottom = (LONG)(exitBtn.pos.y + (exitBtn.button->GetFrameHeight() * DEVIDE_HALF));

}

HRESULT Button::FindIamge()
{
	exitBtn.button = GETSINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Exit.bmp");
	if (exitBtn.button == nullptr)
	{
		cout << "Not Found : Image/Tilemap/UI/Exit.bmp\n";
		return E_FAIL;
	}

	return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{
	// 마우스로 클릭했을 때 기능 실행.
	if (PtInRect(&exitBtn.shape, g_ptMouse))
	{
		cout << "Exit.bmp 실행 준비 완료.\n";
		if (GETSINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) { buttonState = Button_State::DOWN; }
		else if (GETSINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && buttonState == Button_State::DOWN)
		{
			buttonState = Button_State::UP;
			if (btnFunc && pFunc) { (btnFunc->*pFunc)(argFunc); }
			return;
		}
	}
	else { buttonState = Button_State::NONE; }
}

void Button::Render(HDC hdc)
{
	exitBtn.button->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y));	// Exit.img

	if (debugMode) { Rectangle(hdc, exitBtn.shape.left, exitBtn.shape.top, exitBtn.shape.right, exitBtn.shape.bottom); }
}
