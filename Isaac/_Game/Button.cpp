#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	enemyBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	exitBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	loadBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");
	objectBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	sampleTileBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	saveBtn.button = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");

	letter_Enemy = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Enemy.bmp");
	letter_Exit = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Exit.bmp");
	letter_Object = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Object.bmp");
	letter_Tile = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Tile.bmp");

	DeclareButtonInfo(&enemyBtn, 835, 40);
	DeclareButtonInfo(&exitBtn, 153, 40);
	DeclareButtonInfo(&loadBtn, 306, 40);
	DeclareButtonInfo(&objectBtn, 1061, 40);
	DeclareButtonInfo(&sampleTileBtn, 1287, 40);
	DeclareButtonInfo(&saveBtn, 386, 40);
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
	switch (buttonState)
	{
	case Button_State::NONE:	case Button_State::UP:
		enemyBtn.button->Render(hdc, (INT)(enemyBtn.pos.x), (INT)(enemyBtn.pos.y), 0, 0);					// Enemy.img
		exitBtn.button->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y), 0, 0);						// Exit.img
		loadBtn.button->Render(hdc, (INT)(loadBtn.pos.x), (INT)(loadBtn.pos.y), 0, 0);						// Load.img
		objectBtn.button->Render(hdc, (INT)(objectBtn.pos.x), (INT)(objectBtn.pos.y), 0, 0);				// Object.img
		sampleTileBtn.button->Render(hdc, (INT)(sampleTileBtn.pos.x), (INT)(sampleTileBtn.pos.y), 0, 0);	// SampleTile.img
		saveBtn.button->Render(hdc, (INT)(saveBtn.pos.x), (INT)(saveBtn.pos.y), 0, 0);						// Save.img
		break;
	case Button_State::DOWN:
		enemyBtn.button->Render(hdc, (INT)(enemyBtn.pos.x), (INT)(enemyBtn.pos.y), 0, 1);					// Enemy.img
		exitBtn.button->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y), 0, 1);						// Exit.img
		loadBtn.button->Render(hdc, (INT)(loadBtn.pos.x), (INT)(loadBtn.pos.y), 1, 0);						// Load.img
		objectBtn.button->Render(hdc, (INT)(objectBtn.pos.x), (INT)(objectBtn.pos.y), 0, 1);				// Object.img
		sampleTileBtn.button->Render(hdc, (INT)(sampleTileBtn.pos.x), (INT)(sampleTileBtn.pos.y), 0, 1);	// SampleTile.img
		saveBtn.button->Render(hdc, (INT)(saveBtn.pos.x), (INT)(saveBtn.pos.y), 1, 0);						// Save.img
		break;
	default:
		break;
	}

	letter_Enemy->Render(hdc, (INT)(enemyBtn.pos.x), (INT)(enemyBtn.pos.y));
	letter_Exit->Render(hdc, (INT)(exitBtn.pos.x), (INT)(exitBtn.pos.y));
	letter_Object->Render(hdc, (INT)(objectBtn.pos.x), (INT)(objectBtn.pos.y));
	letter_Tile->Render(hdc, (INT)(sampleTileBtn.pos.x), (INT)(sampleTileBtn.pos.y));

	GameObject::Render(hdc);
}

void Button::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		Rectangle(hdc, enemyBtn.shape.left, enemyBtn.shape.top, enemyBtn.shape.right, enemyBtn.shape.bottom);
		Rectangle(hdc, exitBtn.shape.left, exitBtn.shape.top, exitBtn.shape.right, exitBtn.shape.bottom);
		Rectangle(hdc, loadBtn.shape.left, loadBtn.shape.top, loadBtn.shape.right, loadBtn.shape.bottom);
		Rectangle(hdc, objectBtn.shape.left, objectBtn.shape.top, objectBtn.shape.right, objectBtn.shape.bottom);
		Rectangle(hdc, sampleTileBtn.shape.left, sampleTileBtn.shape.top, sampleTileBtn.shape.right, sampleTileBtn.shape.bottom);
		Rectangle(hdc, saveBtn.shape.left, saveBtn.shape.top, saveBtn.shape.right, saveBtn.shape.bottom);
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

