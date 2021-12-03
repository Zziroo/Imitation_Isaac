#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	exitBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Exit.bmp");
	saveBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");
	loadBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");
	sampleTileBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index_01.bmp");
	objectBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index_01.bmp");
	enemyBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index_01.bmp");
	revertBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Revert.bmp");
	multiSelectBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/On_Off.bmp");

	DeclareButtonInfo(&exitBtn, 150,  40);
	DeclareButtonInfo(&saveBtn, 413,  40);
	DeclareButtonInfo(&loadBtn, 313,  40);
	DeclareButtonInfo(&sampleTileBtn, 1287, 40);
	DeclareButtonInfo(&objectBtn, 1061, 40);
	DeclareButtonInfo(&enemyBtn, 835, 40);
	DeclareButtonInfo(&revertBtn, 600, 40);
	DeclareButtonInfo(&multiSelectBtn, 500, 40);

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
	exitBtn.button->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y));								// Exit.img 
	sampleTileBtn.button->Render(hdc, (INT)(sampleTileBtn.pos.x), (INT)(sampleTileBtn.pos.y));				// Exit.img 
	objectBtn.button->Render(hdc, (INT)(objectBtn.pos.x), (INT)(objectBtn.pos.y));							// Exit.img 
	enemyBtn.button->Render(hdc, (INT)(enemyBtn.pos.x), (INT)(enemyBtn.pos.y));								// Exit.img 
	revertBtn.button->Render(hdc, (INT)(revertBtn.pos.x), (INT)(revertBtn.pos.y));							// Revert.img 
	switch (buttonState)
	{
	case Button_State::NONE:	case Button_State::UP:
		saveBtn.button->Render(hdc, (INT)(saveBtn.pos.x), (INT)(saveBtn.pos.y), 0, 0);						// Save.img
		loadBtn.button->Render(hdc, (INT)(loadBtn.pos.x), (INT)(loadBtn.pos.y), 0, 0);						// Load.img
		multiSelectBtn.button->Render(hdc, (INT)(multiSelectBtn.pos.x), (INT)(multiSelectBtn.pos.y), 0, 1);	// ultiSelect.img
		break;
	case Button_State::DOWN:
		saveBtn.button->Render(hdc, (INT)(saveBtn.pos.x), (INT)(saveBtn.pos.y), 1, 0);						// Save.img
		loadBtn.button->Render(hdc, (INT)(loadBtn.pos.x), (INT)(loadBtn.pos.y), 1, 0);						// Load.img
		multiSelectBtn.button->Render(hdc, (INT)(multiSelectBtn.pos.x), (INT)(multiSelectBtn.pos.y), 0, 0);	// ultiSelect.img
		break;
	default:
		break;
	}

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
	btnInfo->pos.x = (FLOAT)(TILEMAP_SIZE_X - width);
	btnInfo->pos.y = (FLOAT)(TILEMAP_SIZE_Y - height);
	btnInfo->shape.left = (LONG)(btnInfo->pos.x - (btnInfo->button->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.top = (LONG)(btnInfo->pos.y - (btnInfo->button->GetFrameHeight() * DEVIDE_HALF));
	btnInfo->shape.right = (LONG)(btnInfo->pos.x + (btnInfo->button->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.bottom = (LONG)(btnInfo->pos.y + (btnInfo->button->GetFrameHeight() * DEVIDE_HALF));
}

