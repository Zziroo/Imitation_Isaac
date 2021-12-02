#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	exitBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Exit.bmp");
	saveBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");
	loadBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");

	DeclareButtonInfo(&exitBtn, TILEMAP_SIZE_X - 210, TILEMAP_SIZE_Y - 70);
	DeclareButtonInfo(&saveBtn, TILEMAP_SIZE_X - 500, TILEMAP_SIZE_Y - 80);
	DeclareButtonInfo(&loadBtn, TILEMAP_SIZE_X - 400, TILEMAP_SIZE_Y - 80);

}

void Button::Release()
{
}

void Button::Update()
{
	GameObject::Update();

	// 마우스로 클릭했을 때 기능 실행.
	if (PtInRect(&exitBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			buttonState = Button_State::DOWN;
		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && buttonState == Button_State::DOWN)
		{
			buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { buttonState = Button_State::NONE; }

}

void Button::Render(HDC hdc)
{
	exitBtn.button->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y));		// Exit.img
	saveBtn.button->Render(hdc, (INT)(saveBtn.pos.x), (INT)(saveBtn.pos.y), 0, 0);	// Save.img
	loadBtn.button->Render(hdc, (INT)(loadBtn.pos.x), (INT)(loadBtn.pos.y), 0, 0);	// Load.img

	GameObject::Render(hdc);
}

void Button::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		Rectangle(hdc, exitBtn.shape.left, exitBtn.shape.top, exitBtn.shape.right, exitBtn.shape.bottom);
		Rectangle(hdc, saveBtn.shape.left, saveBtn.shape.top, saveBtn.shape.right, saveBtn.shape.bottom);
		Rectangle(hdc, loadBtn.shape.left, loadBtn.shape.top, loadBtn.shape.right, loadBtn.shape.bottom);
	}
}

void Button::DeclareButtonInfo(ButtonInfo* btnInfo, int width, int height)
{
	btnInfo->pos.x = (FLOAT)(width);
	btnInfo->pos.y = (FLOAT)(height);
	btnInfo->shape.left = (LONG)(btnInfo->pos.x - (btnInfo->button->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.top = (LONG)(btnInfo->pos.y - (btnInfo->button->GetFrameHeight() * DEVIDE_HALF));
	btnInfo->shape.right = (LONG)(btnInfo->pos.x + (btnInfo->button->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.bottom = (LONG)(btnInfo->pos.y + (btnInfo->button->GetFrameHeight() * DEVIDE_HALF));
}

