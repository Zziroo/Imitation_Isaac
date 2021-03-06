#include "stdafx.h"
#include "Button.h"

#include "Image.h"

void Button::Init()
{
	basementTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	caveTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	cellarTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	closeBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Close.bmp");
	curseRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	depthTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	enemyBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	exitBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	itemRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	loadBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Load.bmp");
	nextBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Next.bmp");
	normalRoomObstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	obstacleBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	prevBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Prev.bmp");
	sampleTileBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Index.bmp");
	saveBtn.image = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/UI/Save.bmp");

	basementLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Basement.bmp");
	caveLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Cave.bmp");
	cellarLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Cellar.bmp");
	curseLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Curse.bmp");
	depthLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Depth.bmp");
	enemyLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Enemy.bmp");
	exitLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Exit.bmp");
	itemLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Item.bmp");
	normalLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Normal.bmp");
	obstacleLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Obstacle.bmp");
	shopLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Shop.bmp");
	tileLetter = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Letter/Tile.bmp");

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

	// Close ???? ??????
	if (sampleTileBtn.clicked)
	{
		DeclareButtonInfo(&closeBtn, 98, 550);
	}
	if (obstacleBtn.clicked || enemyBtn.clicked)
	{
		DeclareButtonInfo(&closeBtn, 98, 630);
	}

	// ?????? ?????? ?? ???? ?????? ???????? ??????.
	// Close
	if (PtInRect(&closeBtn.shape, _ptMouse))
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
			if (enemyBtn.clicked)
			{
				enemyBtn.clicked = false;
			}
		}
	}
	else
	{
		closeBtn.buttonState = ButtonStates::NONE;
	}
	// Exit
	if (PtInRect(&exitBtn.shape, _ptMouse))
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
	if (PtInRect(&loadBtn.shape, _ptMouse))
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
	if (PtInRect(&saveBtn.shape, _ptMouse))
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

	// ?????? ???? ???? ?? ?? ????
	// EnemyBtn
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&enemyBtn.shape, _ptMouse))
		{
			enemyBtn.clicked = !enemyBtn.clicked;
			obstacleBtn.buttonState = ButtonStates::NONE;
			sampleTileBtn.buttonState = ButtonStates::NONE;
		}
	}
	else 
	{
		enemyBtn.buttonState = ButtonStates::NONE;
	}
	// ObstacleBtn
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&obstacleBtn.shape, _ptMouse))
		{
			obstacleBtn.clicked = !obstacleBtn.clicked;
			enemyBtn.buttonState = ButtonStates::NONE;
			sampleTileBtn.buttonState = ButtonStates::NONE;
		}
	}
	else 
	{
		obstacleBtn.buttonState = ButtonStates::NONE; 
	}
	// SampleTile
	if (Input::GetButtonDown(VK_LBUTTON))
	{	
		if (PtInRect(&sampleTileBtn.shape, _ptMouse))
		{
			sampleTileBtn.clicked = !sampleTileBtn.clicked;
			enemyBtn.buttonState = ButtonStates::NONE;
			obstacleBtn.buttonState = ButtonStates::NONE;
		}
	}
	else
	{
		sampleTileBtn.buttonState = ButtonStates::NONE;
	}

	// curseRoomObstacle
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&curseRoomObstacleBtn.shape, _ptMouse))
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
		if (PtInRect(&itemRoomObstacleBtn.shape, _ptMouse))
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
		if (PtInRect(&normalRoomObstacleBtn.shape, _ptMouse))
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

	// ?????? ???? ?? ?????? ?????? ???? ????????.
	if (sampleTileBtn.clicked)
	{
		// BasementTile
		if (PtInRect(&basementTileBtn.shape, _ptMouse) && basementTileBtn.buttonState != ButtonStates::DOWN)
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
		if (PtInRect(&caveTileBtn.shape, _ptMouse) && caveTileBtn.buttonState != ButtonStates::DOWN)
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
		if (PtInRect(&cellarTileBtn.shape, _ptMouse) && cellarTileBtn.buttonState != ButtonStates::DOWN)
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
		if (PtInRect(&depthTileBtn.shape, _ptMouse) && depthTileBtn.buttonState != ButtonStates::DOWN)
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


	// ???? ?????? ???????? ???????? UP?????? ????.
	if (enemyBtn.clicked)
	{
		if (obstacleBtn.clicked && obstacleBtn.buttonState != ButtonStates::NONE)
		{
			enemyBtn.clicked = false;
			enemyBtn.buttonState = ButtonStates::UP;
		}
		if (sampleTileBtn.clicked && sampleTileBtn.buttonState != ButtonStates::NONE)
		{
			enemyBtn.clicked = false;
			enemyBtn.buttonState = ButtonStates::UP;
		}
	}
	if (obstacleBtn.clicked)
	{
		if (enemyBtn.clicked && enemyBtn.buttonState != ButtonStates::NONE)
		{
			obstacleBtn.clicked = false;
			obstacleBtn.buttonState = ButtonStates::UP;
		}
		if (sampleTileBtn.clicked && sampleTileBtn.buttonState != ButtonStates::NONE)
		{
			obstacleBtn.clicked = false;
			obstacleBtn.buttonState = ButtonStates::UP;
		}
	}
	if (sampleTileBtn.clicked)
	{
		if (enemyBtn.clicked && enemyBtn.buttonState != ButtonStates::NONE)
		{
			sampleTileBtn.clicked = false;
			sampleTileBtn.buttonState = ButtonStates::UP;
		}
		if (obstacleBtn.clicked && obstacleBtn.buttonState != ButtonStates::NONE)
		{
			sampleTileBtn.clicked = false;
			sampleTileBtn.buttonState = ButtonStates::UP;
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

	// SampleTile ???? ???? ???????? true, ?????? ?????????? false
	if (sampleTileBtn.clicked)
	{
		sampleTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		sampleTileBtn.buttonState = ButtonStates::UP;
	}
	// BasementTile ???? ???? ???????? true, ?????? ?????????? false
	if (basementTileBtn.clicked)
	{
		basementTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		basementTileBtn.buttonState = ButtonStates::UP;
	}
	// CaveTile ???? ???? ???????? true, ?????? ?????????? false
	if (caveTileBtn.clicked)
	{
		caveTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		caveTileBtn.buttonState = ButtonStates::UP;
	}
	// CellarTile ???? ???? ???????? true, ?????? ?????????? false
	if (cellarTileBtn.clicked)
	{
		cellarTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		cellarTileBtn.buttonState = ButtonStates::UP;
	}
	// DepthTile ???? ???? ???????? true, ?????? ?????????? false
	if (depthTileBtn.clicked)
	{
		depthTileBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		depthTileBtn.buttonState = ButtonStates::UP;
	}

	// ObstacleTile ???? ???? ???????? true, ?????? ?????????? false
	if (obstacleBtn.clicked)
	{
		obstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		obstacleBtn.buttonState = ButtonStates::UP;
	}
	// curseRoomObstacle ???? ???? ???????? true, ?????? ?????????? false
	if (curseRoomObstacleBtn.clicked)
	{
		curseRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		curseRoomObstacleBtn.buttonState = ButtonStates::UP;
	}
	// itemRoomObstacle ???? ???? ???????? true, ?????? ?????????? false
	if (itemRoomObstacleBtn.clicked)
	{
		itemRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		itemRoomObstacleBtn.buttonState = ButtonStates::UP;
	}
	// normalRoomObstacle ???? ???? ???????? true, ?????? ?????????? false
	if (normalRoomObstacleBtn.clicked)
	{
		normalRoomObstacleBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		normalRoomObstacleBtn.buttonState = ButtonStates::UP;
	}

	// Enemy ???? ???? ???????? true, ?????? ?????????? false
	if (enemyBtn.clicked)
	{
		enemyBtn.buttonState = ButtonStates::DOWN;
	}
	else
	{
		enemyBtn.buttonState = ButtonStates::UP;
	}

	// NextButton,PrevButton
	if (sampleTileBtn.clicked)
	{
		// Next Button
		if (PtInRect(&nextBtn.shape, _ptMouse))
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
		if (PtInRect(&prevBtn.shape, _ptMouse))
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

		ShowLetter(hdc, basementLetter, &basementTileBtn);
		ShowLetter(hdc, caveLetter, &caveTileBtn);
		ShowLetter(hdc, cellarLetter, &cellarTileBtn);
		ShowLetter(hdc, depthLetter, &depthTileBtn);
	}

	if (obstacleBtn.clicked)
	{
		RenderNormalButton(hdc, &closeBtn);

		switch (curseRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			curseRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(curseRoomObstacleBtn.pos.x - 70), (INT)(curseRoomObstacleBtn.pos.y - 20), 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			curseRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(curseRoomObstacleBtn.pos.x - 70), (INT)(curseRoomObstacleBtn.pos.y - 20), 0, 1, 0.68f);
			break;
		default:
			break;
		}

		switch (itemRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			itemRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(itemRoomObstacleBtn.pos.x - 70), (INT)(itemRoomObstacleBtn.pos.y - 20), 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			itemRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(itemRoomObstacleBtn.pos.x - 70), (INT)(itemRoomObstacleBtn.pos.y - 20), 0, 1, 0.68f);
			break;
		default:
			break;
		}
		switch (normalRoomObstacleBtn.buttonState)
		{
		case ButtonStates::NONE:	case ButtonStates::UP:
			normalRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(normalRoomObstacleBtn.pos.x - 70), (INT)(normalRoomObstacleBtn.pos.y - 20), 0, 0, 0.68f);
			break;
		case ButtonStates::DOWN:
			normalRoomObstacleBtn.image->EnlargeSampleTile(hdc, (INT)(normalRoomObstacleBtn.pos.x - 70), (INT)(normalRoomObstacleBtn.pos.y - 20), 0, 1, 0.68f);
			break;
		default:
			break;
		}
		ShowLetter(hdc, curseLetter, &curseRoomObstacleBtn);
		ShowLetter(hdc, itemLetter, &itemRoomObstacleBtn);
		ShowLetter(hdc, normalLetter, &normalRoomObstacleBtn);
	}

	if (enemyBtn.clicked)
	{
		RenderNormalButton(hdc, &closeBtn);
	}

	ShowLetter(hdc, enemyLetter, &enemyBtn);
	ShowLetter(hdc, exitLetter, &exitBtn);
	ShowLetter(hdc, obstacleLetter, &obstacleBtn);
	ShowLetter(hdc, tileLetter, &sampleTileBtn);

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

void Button::DeclareButtonInfo(ButtonInfo* btnInfo, int width, int height)
{
	btnInfo->pos.x = (FLOAT)(TILEMAP_SIZE_X - width);
	btnInfo->pos.y = (FLOAT)(TILEMAP_SIZE_Y - height);
	btnInfo->shape.left = (LONG)(btnInfo->pos.x - (btnInfo->image->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.top = (LONG)(btnInfo->pos.y - (btnInfo->image->GetFrameHeight() * DEVIDE_HALF));
	btnInfo->shape.right = (LONG)(btnInfo->pos.x + (btnInfo->image->GetFrameWidth() * DEVIDE_HALF));
	btnInfo->shape.bottom = (LONG)(btnInfo->pos.y + (btnInfo->image->GetFrameHeight() * DEVIDE_HALF));
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
