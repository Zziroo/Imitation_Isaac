#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	enemyBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	exitBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	loadBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");
	objectBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	sampleTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	saveBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");

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
	if (PtInRect(&enemyBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			enemyBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && enemyBtn.buttonState == Button_State::DOWN)
		{
			enemyBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { enemyBtn.buttonState = Button_State::NONE; }
	if (PtInRect(&exitBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			exitBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && exitBtn.buttonState == Button_State::DOWN)
		{
			exitBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { exitBtn.buttonState = Button_State::NONE; }
	if (PtInRect(&loadBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			loadBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && loadBtn.buttonState == Button_State::DOWN)
		{
			loadBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { loadBtn.buttonState = Button_State::NONE; }
	if (PtInRect(&objectBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			objectBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && objectBtn.buttonState == Button_State::DOWN)
		{
			objectBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { objectBtn.buttonState = Button_State::NONE; }
	if (PtInRect(&sampleTileBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			sampleTileBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && sampleTileBtn.buttonState == Button_State::DOWN)
		{
			sampleTileBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { sampleTileBtn.buttonState = Button_State::NONE; }
	if (PtInRect(&saveBtn.shape, g_ptMouse))
	{
		if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_LBUTTON)) 
		{ 
			saveBtn.buttonState = Button_State::DOWN;

		}
		else if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON) && saveBtn.buttonState == Button_State::DOWN)
		{
			saveBtn.buttonState = Button_State::UP;
			if (btnFunc && pFunc) 
			{ 
				(btnFunc->*pFunc)(argFunc);
			}

			return;
		}
	}
	else { saveBtn.buttonState = Button_State::NONE; }

}

void Button::Render(HDC hdc)
{
	ClikedButton(enemyBtn, hdc);
	ClikedButton(exitBtn, hdc);
	ClikedButton(loadBtn, hdc);
	ClikedButton(objectBtn, hdc);
	ClikedButton(sampleTileBtn, hdc);
	ClikedButton(saveBtn, hdc);

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
	btnInfo->shape.left = (LONG)(btnInfo->pos.x - (btnInfo->image->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.top = (LONG)(btnInfo->pos.y - (btnInfo->image->GetFrameHeight() * DEVIDE_HALF));
	btnInfo->shape.right = (LONG)(btnInfo->pos.x + (btnInfo->image->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.bottom = (LONG)(btnInfo->pos.y + (btnInfo->image->GetFrameHeight() * DEVIDE_HALF));
}

void Button::ClikedButton(ButtonInfo btnInfo, HDC hdc)
{
	switch (btnInfo.buttonState)
	{
	case Button_State::NONE:	case Button_State::UP:
		RenderUpButtonImage(btnInfo, hdc);
		break;
	case Button_State::DOWN:
		RenderDownButtonImage(btnInfo, hdc);
		break;
	default:
		break;
	}
}

void Button::RenderUpButtonImage(ButtonInfo btnInfo, HDC hdc)
{
	btnInfo.image->Render(hdc, (INT)(btnInfo.pos.x), (INT)(btnInfo.pos.y), 0, 0);
}

void Button::RenderDownButtonImage(ButtonInfo btnInfo, HDC hdc)
{
	btnInfo.image->Render(hdc, (INT)(btnInfo.pos.x), (INT)(btnInfo.pos.y), 0, 1);
}
