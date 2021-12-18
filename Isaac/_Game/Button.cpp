#include "MainConfig.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	closeBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Close.bmp");
	enemyBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	loadBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");
	nextBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Next.bmp");
	obstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	prevBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Prev.bmp");
	sampleTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	saveBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");

	basementTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	caveTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	cellarTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	depthTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	exitBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");

	curseRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	itemRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	normalRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");

	letter_Basement = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Basement.bmp");
	letter_Cave = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Cave.bmp");
	letter_Cellar = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Cellar.bmp");
	letter_Depth = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Depth.bmp");
	letter_Enemy = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Enemy.bmp");
	letter_Exit = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Exit.bmp");
	letter_Obstacle = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Obstacle.bmp");
	letter_Shop = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Shop.bmp");
	letter_Tile = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Tile.bmp");

	letter_Curse = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Curse.bmp");
	letter_Item = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Item.bmp");
	letter_Normal = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Normal.bmp");

	DeclareButtonInfo(&exitBtn, 153, 40);
	DeclareButtonInfo(&loadBtn, 306, 40);
	DeclareButtonInfo(&saveBtn, 386, 40);

	DeclareButtonInfo(&enemyBtn, 835, 40);
	DeclareButtonInfo(&obstacleBtn, 1061, 40);
	DeclareButtonInfo(&sampleTileBtn, 1287, 40);

	DeclareButtonInfo(&basementTileBtn, 722, 500);
	DeclareButtonInfo(&caveTileBtn, 722, 393);
	DeclareButtonInfo(&cellarTileBtn, 722, 287);
	DeclareButtonInfo(&depthTileBtn, 722, 180);

	DeclareButtonInfo(&nextBtn, 98, 180);
	DeclareButtonInfo(&prevBtn, 520, 180);

	curseRoomObstacleBtn.pos = { 920.0f, 770.0f };
	curseRoomObstacleBtn.shape = {
		(LONG)(curseRoomObstacleBtn.pos.x - (140 * DEVIDE_HALF)),
		(LONG)(curseRoomObstacleBtn.pos.y - (40 * DEVIDE_HALF)),
		(LONG)(curseRoomObstacleBtn.pos.x + (140 * DEVIDE_HALF)),
		(LONG)(curseRoomObstacleBtn.pos.y + (40 * DEVIDE_HALF)),
	};

	itemRoomObstacleBtn.pos = { 1100.0f, 770.0f };
	itemRoomObstacleBtn.shape = {
		(LONG)(itemRoomObstacleBtn.pos.x - (140 * DEVIDE_HALF)),
		(LONG)(itemRoomObstacleBtn.pos.y - (40 * DEVIDE_HALF)),
		(LONG)(itemRoomObstacleBtn.pos.x + (140 * DEVIDE_HALF)),
		(LONG)(itemRoomObstacleBtn.pos.y + (40 * DEVIDE_HALF)),
	};

	normalRoomObstacleBtn.pos = { 1280.0f, 770.0f };
	normalRoomObstacleBtn.shape = {
		(LONG)(normalRoomObstacleBtn.pos.x - (140 * DEVIDE_HALF)),
		(LONG)(normalRoomObstacleBtn.pos.y - (40 * DEVIDE_HALF)),
		(LONG)(normalRoomObstacleBtn.pos.x + (140 * DEVIDE_HALF)),
		(LONG)(normalRoomObstacleBtn.pos.y + (40 * DEVIDE_HALF)),
	};
}

void Button::Release()
{
}

void Button::Update()
{
	GameObject::Update();

	// Close 버튼 재사용
	if (sampleTileBtn.clicked)
	{
		DeclareButtonInfo(&closeBtn, 98, 550);
	}
	if (obstacleBtn.clicked)
	{
		DeclareButtonInfo(&closeBtn, 98, 630);
	}

	// 버튼을 눌렀을 때 명령 실행후 원상태로 돌아감.
	// Close
	if (PtInRect(&closeBtn.shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			closeBtn.buttonState = ButtonStates::DOWN;
		}
		else if (Input::GetButtonUp(VK_LBUTTON) && closeBtn.buttonState == ButtonStates::DOWN)
		{
			closeBtn.buttonState = ButtonStates::UP;
			if (sampleTileBtn.clicked)
			{
				sampleTileBtn.clicked = false;
			}
			if (obstacleBtn.clicked)
			{
				obstacleBtn.clicked = false;
			}
		}
	}
	else
	{
		closeBtn.buttonState = ButtonStates::NONE;
	}
	// Exit
	if (PtInRect(&exitBtn.shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			exitBtn.buttonState = ButtonStates::DOWN;
		}
		else if (Input::GetButtonUp(VK_LBUTTON) && exitBtn.buttonState == ButtonStates::DOWN)
		{
			exitBtn.buttonState = ButtonStates::UP;
			PostQuitMessage(0);

			return;
		}
	}
	else
	{
		exitBtn.buttonState = ButtonStates::NONE;
	}
	// Load
	if (PtInRect(&loadBtn.shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{ 
			loadBtn.buttonState = ButtonStates::DOWN;
			loadBtn.clicked = true;
		}
		else if (Input::GetButtonUp(VK_LBUTTON) && loadBtn.buttonState == ButtonStates::DOWN)
		{
			loadBtn.buttonState = ButtonStates::UP;
			loadBtn.clicked = false;
		}
	}
	else
	{
		loadBtn.buttonState = ButtonStates::NONE;
		loadBtn.clicked = false;
	}
	// Save
	if (PtInRect(&saveBtn.shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{ 
			saveBtn.buttonState = ButtonStates::DOWN;
			saveBtn.clicked = true;
		}
		else if (Input::GetButtonUp(VK_LBUTTON) && saveBtn.buttonState == ButtonStates::DOWN)
		{
			saveBtn.buttonState = ButtonStates::UP;
			saveBtn.clicked = false;
		}
	}
	else
	{
		saveBtn.buttonState = ButtonStates::NONE;
		saveBtn.clicked = false;
	}

	// 버튼을 끄고 키고 할 수 있음
	if (PtInRect(&enemyBtn.shape, g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			enemyBtn.buttonState = ButtonStates::DOWN;

		}
		else if (Input::GetButtonUp(VK_LBUTTON) && enemyBtn.buttonState == ButtonStates::DOWN)
		{
			enemyBtn.buttonState = ButtonStates::UP;

			return;
		}
	}
	else 
	{
		enemyBtn.buttonState = ButtonStates::NONE;
	}
	// SampleTile
	if (Input::GetButtonDown(VK_LBUTTON))
	{	
		if (PtInRect(&sampleTileBtn.shape, g_ptMouse))
		{
			sampleTileBtn.clicked = !sampleTileBtn.clicked;
			obstacleBtn.buttonState = ButtonStates::NONE;
		}
	}
	else
	{
		sampleTileBtn.buttonState = ButtonStates::NONE;
	}
	// ObstacleBtn
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&obstacleBtn.shape, g_ptMouse))
		{
			obstacleBtn.clicked = !obstacleBtn.clicked;
			sampleTileBtn.buttonState = ButtonStates::NONE;
		}
	}
	else 
	{
		obstacleBtn.buttonState = ButtonStates::NONE; 
	}
	// curseRoomObstacle
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&curseRoomObstacleBtn.shape, g_ptMouse))
		{
			curseRoomObstacleBtn.clicked = !curseRoomObstacleBtn.clicked;
			itemRoomObstacleBtn.buttonState = ButtonStates::NONE;
			normalRoomObstacleBtn.buttonState = ButtonStates::NONE;
		}
	}
	else
	{
		curseRoomObstacleBtn.buttonState = ButtonStates::NONE;
	}
	// itemRoomObstacle
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&itemRoomObstacleBtn.shape, g_ptMouse))
		{
			itemRoomObstacleBtn.clicked = !itemRoomObstacleBtn.clicked;
			curseRoomObstacleBtn.buttonState = ButtonStates::NONE;
			normalRoomObstacleBtn.buttonState = ButtonStates::NONE;
		}
	}
	else
	{
		itemRoomObstacleBtn.buttonState = ButtonStates::NONE;
	}
	// normalRoomObstacle
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&normalRoomObstacleBtn.shape, g_ptMouse))
		{
			normalRoomObstacleBtn.clicked = !normalRoomObstacleBtn.clicked;
			curseRoomObstacleBtn.buttonState = ButtonStates::NONE;
			itemRoomObstacleBtn.buttonState = ButtonStates::NONE;
		}
	}
	else
	{
		normalRoomObstacleBtn.buttonState = ButtonStates::NONE;
	}

	// 기존의 버튼 중 하나는 무조건 눌려 있어야함.
	if (sampleTileBtn.clicked)
	{
		// BasementTile
		if (PtInRect(&basementTileBtn.shape, g_ptMouse) && basementTileBtn.buttonState != ButtonStates::DOWN)
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				basementTileBtn.clicked = true;
				tileIndex = 0;
			}
		}
		else
		{
			basementTileBtn.buttonState = ButtonStates::NONE;
		}
		// CaveTile
		if (PtInRect(&caveTileBtn.shape, g_ptMouse) && caveTileBtn.buttonState != ButtonStates::DOWN)
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				caveTileBtn.clicked = true;
				tileIndex = 0;
			}
		}
		else
		{
			caveTileBtn.buttonState = ButtonStates::NONE;
		}
		// CellarTile
		if (PtInRect(&cellarTileBtn.shape, g_ptMouse) && cellarTileBtn.buttonState != ButtonStates::DOWN)
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				cellarTileBtn.clicked = true;
				tileIndex = 0;
			}
		}
		else
		{
			cellarTileBtn.buttonState = ButtonStates::NONE;
		}
		// DepthTile
		if (PtInRect(&depthTileBtn.shape, g_ptMouse) && depthTileBtn.buttonState != ButtonStates::DOWN)
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				depthTileBtn.clicked = true;
				tileIndex = 0;
			}
		}
		else
		{
			depthTileBtn.buttonState = ButtonStates::NONE;
		}
	}


	// 버튼 하나를 클릭하면 나머지는 UP상태로 만듦.
	if (sampleTileBtn.clicked)
	{
		if (obstacleBtn.clicked && obstacleBtn.buttonState != ButtonStates::NONE)
		{
			sampleTileBtn.clicked = false;
			sampleTileBtn.buttonState = ButtonStates::UP;
		}
	}
	if (obstacleBtn.clicked)
	{
		if (sampleTileBtn.clicked && sampleTileBtn.buttonState != ButtonStates::NONE)
		{
			obstacleBtn.clicked = false;
			obstacleBtn.buttonState = ButtonStates::UP;
		}
	}

	if (basementTileBtn.clicked)
	{
		if (caveTileBtn.clicked && caveTileBtn.buttonState != ButtonStates::NONE)
		{
			basementTileBtn.clicked = false;
			basementTileBtn.buttonState = ButtonStates::UP;
		}
		if (cellarTileBtn.clicked && cellarTileBtn.buttonState != ButtonStates::NONE)
		{
			basementTileBtn.clicked = false;
			basementTileBtn.buttonState = ButtonStates::UP;
		}
		if (depthTileBtn.clicked && depthTileBtn.buttonState != ButtonStates::NONE)
		{
			basementTileBtn.clicked = false;
			basementTileBtn.buttonState = ButtonStates::UP;
		}
	}
	if (caveTileBtn.clicked)
	{
		if (basementTileBtn.clicked&& basementTileBtn.buttonState != ButtonStates::NONE)
		{
			caveTileBtn.clicked = false;
			caveTileBtn.buttonState = ButtonStates::UP;
		}
		if (cellarTileBtn.clicked && cellarTileBtn.buttonState != ButtonStates::NONE)
		{
			caveTileBtn.clicked = false;
			caveTileBtn.buttonState = ButtonStates::UP;
		}
		if (depthTileBtn.clicked && depthTileBtn.buttonState != ButtonStates::NONE)
		{
			caveTileBtn.clicked = false;
			caveTileBtn.buttonState = ButtonStates::UP;
		}
	}
	if (cellarTileBtn.clicked)
	{
		if (basementTileBtn.clicked&& basementTileBtn.buttonState != ButtonStates::NONE)
		{
			cellarTileBtn.clicked = false;
			cellarTileBtn.buttonState = ButtonStates::UP;
		}
		if (caveTileBtn.clicked && caveTileBtn.buttonState != ButtonStates::NONE)
		{
			cellarTileBtn.clicked = false;
			cellarTileBtn.buttonState = ButtonStates::UP;
		}
		if (depthTileBtn.clicked && depthTileBtn.buttonState != ButtonStates::NONE)
		{
			cellarTileBtn.clicked = false;
			cellarTileBtn.buttonState = ButtonStates::UP;
		}
	}
	if (depthTileBtn.clicked)
	{
		if (basementTileBtn.clicked && basementTileBtn.buttonState != ButtonStates::NONE)
		{
			depthTileBtn.clicked = false;
			depthTileBtn.buttonState = ButtonStates::UP;
		}
		if (caveTileBtn.clicked && caveTileBtn.buttonState != ButtonStates::NONE)
		{
			depthTileBtn.clicked = false;
			depthTileBtn.buttonState = ButtonStates::UP;
		}
		if (cellarTileBtn.clicked && cellarTileBtn.buttonState != ButtonStates::NONE)
		{
			depthTileBtn.clicked = false;
			depthTileBtn.buttonState = ButtonStates::UP;
		}
	}

	if (curseRoomObstacleBtn.clicked)
	{
		if (itemRoomObstacleBtn.clicked && itemRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			curseRoomObstacleBtn.clicked = false;
			curseRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
		if (normalRoomObstacleBtn.clicked && normalRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			curseRoomObstacleBtn.clicked = false;
			curseRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
	}
	if (itemRoomObstacleBtn.clicked)
	{
		if (curseRoomObstacleBtn.clicked && curseRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			itemRoomObstacleBtn.clicked = false;
			itemRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
		if (normalRoomObstacleBtn.clicked && normalRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			itemRoomObstacleBtn.clicked = false;
			itemRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
	}
	if (normalRoomObstacleBtn.clicked)
	{
		if (curseRoomObstacleBtn.clicked && curseRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			normalRoomObstacleBtn.clicked = false;
			normalRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
		if (itemRoomObstacleBtn.clicked && itemRoomObstacleBtn.buttonState != ButtonStates::NONE)
		{
			normalRoomObstacleBtn.clicked = false;
			normalRoomObstacleBtn.buttonState = ButtonStates::UP;
		}
	}

	// SampleTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (sampleTileBtn.clicked)
	{
		sampleTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		sampleTileBtn.buttonState = ButtonStates::UP;
	}
	// BasementTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (basementTileBtn.clicked)
	{
		basementTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		basementTileBtn.buttonState = ButtonStates::UP;
	}
	// CaveTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (caveTileBtn.clicked)
	{
		caveTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		caveTileBtn.buttonState = ButtonStates::UP;
	}
	// CellarTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (cellarTileBtn.clicked)
	{
		cellarTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		cellarTileBtn.buttonState = ButtonStates::UP;
	}
	// DepthTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (depthTileBtn.clicked)
	{
		depthTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		depthTileBtn.buttonState = ButtonStates::UP;
	}

	// ObstacleTile 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (obstacleBtn.clicked)
	{
		obstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		obstacleBtn.buttonState = ButtonStates::UP;
	}
	// curseRoomObstacle 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (curseRoomObstacleBtn.clicked)
	{
		curseRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		curseRoomObstacleBtn.buttonState = ButtonStates::UP;
	}
	// itemRoomObstacle 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (itemRoomObstacleBtn.clicked)
	{
		itemRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		itemRoomObstacleBtn.buttonState = ButtonStates::UP;
	}
	// normalRoomObstacle 버튼 클릭 돼있으면 true, 클릭이 안돼있으면 false
	if (normalRoomObstacleBtn.clicked)
	{
		normalRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		normalRoomObstacleBtn.buttonState = ButtonStates::UP;
	}

	// NextButton,PrevButton
	if (sampleTileBtn.clicked)
	{
		// Next Button
		if (PtInRect(&nextBtn.shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				nextBtn.buttonState = ButtonStates::DOWN;
				nextBtn.clicked = true;
				++tileIndex;
			}
			else if (Input::GetButtonUp(VK_LBUTTON) && nextBtn.buttonState == ButtonStates::DOWN)
			{
				nextBtn.buttonState = ButtonStates::UP;
				nextBtn.clicked = false;
			}
		}
		else
		{
			nextBtn.buttonState = ButtonStates::NONE;
		}
		// Prev Button
		if (PtInRect(&prevBtn.shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				prevBtn.buttonState = ButtonStates::DOWN;
				prevBtn.clicked = true;
				--tileIndex;
			}
			else if (Input::GetButtonUp(VK_LBUTTON) && prevBtn.buttonState == ButtonStates::DOWN)
			{
				prevBtn.buttonState = ButtonStates::UP;
				prevBtn.clicked = false;
			}
		}
		else
		{
			prevBtn.buttonState = ButtonStates::NONE;
		}
	}
}

void Button::Render(HDC hdc)
{
	ClikedButton(hdc, &exitBtn);
	ClikedButton(hdc, &loadBtn);
	ClikedButton(hdc, &saveBtn);

	ClikedButton(hdc, &enemyBtn);
	ClikedButton(hdc, &obstacleBtn);
	ClikedButton(hdc, &sampleTileBtn);

	if (sampleTileBtn.clicked)
	{
		ClikedButton(hdc, &basementTileBtn);
		ClikedButton(hdc, &caveTileBtn);
		ClikedButton(hdc, &cellarTileBtn);
		ClikedButton(hdc, &depthTileBtn);

		RenderNormalButton(hdc, &closeBtn);
		RenderNormalButton(hdc, &prevBtn);
		RenderNormalButton(hdc, &nextBtn);

		ShowLetter(hdc, letter_Basement, &basementTileBtn);
		ShowLetter(hdc, letter_Cave, &caveTileBtn);
		ShowLetter(hdc, letter_Cellar, &cellarTileBtn);
		ShowLetter(hdc, letter_Depth, &depthTileBtn);
	}

	if (obstacleBtn.clicked)
	{
		RenderNormalButton(hdc, &closeBtn);

		switch (curseRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			curseRoomObstacleBtn.image->EnlargeSampleTile(hdc, curseRoomObstacleBtn.pos.x - 70, curseRoomObstacleBtn.pos.y - 20, 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			curseRoomObstacleBtn.image->EnlargeSampleTile(hdc, curseRoomObstacleBtn.pos.x - 70, curseRoomObstacleBtn.pos.y - 20, 0, 1, 0.68f);
			break;
		default:
			break;
		}

		switch (itemRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			itemRoomObstacleBtn.image->EnlargeSampleTile(hdc, itemRoomObstacleBtn.pos.x - 70, itemRoomObstacleBtn.pos.y - 20, 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			itemRoomObstacleBtn.image->EnlargeSampleTile(hdc, itemRoomObstacleBtn.pos.x - 70, itemRoomObstacleBtn.pos.y - 20, 0, 1, 0.68f);
			break;
		default:
			break;
		}
		switch (normalRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			normalRoomObstacleBtn.image->EnlargeSampleTile(hdc, normalRoomObstacleBtn.pos.x - 70, normalRoomObstacleBtn.pos.y - 20, 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			normalRoomObstacleBtn.image->EnlargeSampleTile(hdc, normalRoomObstacleBtn.pos.x - 70, normalRoomObstacleBtn.pos.y - 20, 0, 1, 0.68f);
			break;
		default:
			break;
		}
		ShowLetter(hdc, letter_Curse, &curseRoomObstacleBtn);
		ShowLetter(hdc, letter_Item, &itemRoomObstacleBtn);
		ShowLetter(hdc, letter_Normal, &normalRoomObstacleBtn);
	}

	ShowLetter(hdc, letter_Enemy, &enemyBtn);
	ShowLetter(hdc, letter_Exit, &exitBtn);
	ShowLetter(hdc, letter_Obstacle, &obstacleBtn);
	ShowLetter(hdc, letter_Tile, &sampleTileBtn);

	GameObject::Render(hdc);
}

void Button::OnDebug(HDC hdc)
{
	wsprintf(text, "ExitBtn.clicked : %d", exitBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 300), text, (INT)(strlen(text)));
	wsprintf(text, "LoadBtn.clicked : %d", loadBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 280), text, (INT)(strlen(text)));
	wsprintf(text, "SaveBtnBtn.clicked : %d", saveBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 260), text, (INT)(strlen(text)));

	wsprintf(text, "SampleTileBtn.clicked : %d", sampleTileBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 220), text, (INT)(strlen(text)));
	if (sampleTileBtn.clicked)
	{
		wsprintf(text, "BasementTileBtn.clicked : %d", basementTileBtn.clicked);
		TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 180), text, (INT)(strlen(text)));
		wsprintf(text, "CaveTileBtn.clicked : %d", caveTileBtn.clicked);
		TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 160), text, (INT)(strlen(text)));
		wsprintf(text, "CellarTileBtn.clicked : %d", cellarTileBtn.clicked);
		TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 140), text, (INT)(strlen(text)));
		wsprintf(text, "DepthTileBtn.clicked : %d", depthTileBtn.clicked);
		TextOut(hdc, (TILEMAP_SIZE_X - 1390), (TILEMAP_SIZE_Y - 120), text, (INT)(strlen(text)));
	}
	wsprintf(text, "ObstacleBtn.clicked : %d", obstacleBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 1164), (TILEMAP_SIZE_Y - 220), text, (INT)(strlen(text)));
	wsprintf(text, "EnemyBtn.clicked : %d", enemyBtn.clicked);
	TextOut(hdc, (TILEMAP_SIZE_X - 938), (TILEMAP_SIZE_Y - 220), text, (INT)(strlen(text)));

	if (debugMode)
	{
		Rectangle(hdc, exitBtn.shape.left, exitBtn.shape.top, exitBtn.shape.right, exitBtn.shape.bottom);
		Rectangle(hdc, loadBtn.shape.left, loadBtn.shape.top, loadBtn.shape.right, loadBtn.shape.bottom);
		Rectangle(hdc, saveBtn.shape.left, saveBtn.shape.top, saveBtn.shape.right, saveBtn.shape.bottom);

		Rectangle(hdc, enemyBtn.shape.left, enemyBtn.shape.top, enemyBtn.shape.right, enemyBtn.shape.bottom);
		Rectangle(hdc, obstacleBtn.shape.left, obstacleBtn.shape.top, obstacleBtn.shape.right, obstacleBtn.shape.bottom);
		Rectangle(hdc, sampleTileBtn.shape.left, sampleTileBtn.shape.top, sampleTileBtn.shape.right, sampleTileBtn.shape.bottom);

		if (sampleTileBtn.clicked)
		{
			Rectangle(hdc, basementTileBtn.shape.left, basementTileBtn.shape.top, basementTileBtn.shape.right, basementTileBtn.shape.bottom);
			Rectangle(hdc, caveTileBtn.shape.left, caveTileBtn.shape.top, caveTileBtn.shape.right, caveTileBtn.shape.bottom);
			Rectangle(hdc, cellarTileBtn.shape.left, cellarTileBtn.shape.top, cellarTileBtn.shape.right, cellarTileBtn.shape.bottom);
			Rectangle(hdc, depthTileBtn.shape.left, depthTileBtn.shape.top, depthTileBtn.shape.right, depthTileBtn.shape.bottom);

			Rectangle(hdc, closeBtn.shape.left, closeBtn.shape.top, closeBtn.shape.right, closeBtn.shape.bottom);
			Rectangle(hdc, prevBtn.shape.left, prevBtn.shape.top, prevBtn.shape.right, prevBtn.shape.bottom);
			Rectangle(hdc, nextBtn.shape.left, nextBtn.shape.top, nextBtn.shape.right, nextBtn.shape.bottom);
		}

		if (obstacleBtn.clicked)
		{
			Rectangle(hdc, curseRoomObstacleBtn.shape.left, curseRoomObstacleBtn.shape.top, curseRoomObstacleBtn.shape.right, curseRoomObstacleBtn.shape.bottom);
			Rectangle(hdc, itemRoomObstacleBtn.shape.left, itemRoomObstacleBtn.shape.top, itemRoomObstacleBtn.shape.right, itemRoomObstacleBtn.shape.bottom);
			Rectangle(hdc, normalRoomObstacleBtn.shape.left, normalRoomObstacleBtn.shape.top, normalRoomObstacleBtn.shape.right, normalRoomObstacleBtn.shape.bottom);
		}
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

void Button::ClikedButton(HDC hdc, ButtonInfo* btnInfo)
{
	switch (btnInfo->buttonState)
	{
	case ButtonStates::NONE:	case ButtonStates::UP:
		RenderUpButton(hdc, btnInfo);
		break;
	case ButtonStates::DOWN:
		RenderDownButton(hdc, btnInfo);
		break;
	default:
		break;
	}
}

void Button::RenderDownButton(HDC hdc, ButtonInfo* btnInfo)
{
	btnInfo->image->Render(hdc, (INT)(btnInfo->pos.x), (INT)(btnInfo->pos.y), 0, 1);
}

void Button::RenderNormalButton(HDC hdc, ButtonInfo* btnInfo)
{
	btnInfo->image->Render(hdc, (INT)(btnInfo->pos.x), (INT)(btnInfo->pos.y));
}

void Button::RenderUpButton(HDC hdc, ButtonInfo* btnInfo)
{
	btnInfo->image->Render(hdc, (INT)(btnInfo->pos.x), (INT)(btnInfo->pos.y), 0, 0);
}

void Button::ShowLetter(HDC hdc, Image* img, ButtonInfo* btnInfo)
{
	img->Render(hdc, (INT)(btnInfo->pos.x), (INT)(btnInfo->pos.y));
}
