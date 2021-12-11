#include "MainConfig.h"
#include "TilemapToolScene.h"

#include "Button.h"
#include "ButtonFunction.h"
#include "Image.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);
	// Main BackGround
	backGround = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround01.bmp");
	// Sample BackGround
	sampleBackGround = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround02.bmp");
	// Drawing Area
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Nothingness.bmp");

	// MainTile
	for (int r = 0; r < TILE_ROW; ++r)
	{
		for (int c = 0; c < TILE_COLUMN; ++c)
		{
			SetRect(&(tempTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
			tempTileInfo[r][c].frameX = c;
			tempTileInfo[r][c].frameY = r;
		}
	}

	// SingleSelectTile
	singleSelectedSampleTile.frameX = 32;
	singleSelectedSampleTile.frameY = 0;

	// MultiSelectTile
	multiSelectedSampleTile[0].resize(2);
	for (int i = 0; i < multiSelectedSampleTile[0].size(); ++i)
	{
		multiSelectedSampleTile[0][i].frameX = 32;
		multiSelectedSampleTile[0][i].frameY = 0;
	}

	// Button
	buttonFunc = new ButtonFunction;
	button = new Button;
	button->Init();
	button->SetFunction(&ButtonFunction::QuitProgram, buttonFunc);

	return S_OK;
}

void TilemapToolScene::Release()
{
	SAFE_RELEASE(button);
	SAFE_DELETE(buttonFunc);
}

void TilemapToolScene::Update()
{
	// Debug
	if (Input::GetButtonDown('M'))
	{
		debugMode = !debugMode;
	}

	// Button
	button->Update();

	// SampleImg와 SampleTile 초기화
	char cha[128];
	string str = "Image/Tilemap/Tile/";
	if (button->GetSelectBasementTile() && sampleTileType != SampleTileTypes::BASEMENT)
	{
		// 이미지
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");

		// Main 영역
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetRect(&(mainBasementTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
				mainBasementTileInfo[r][c].frameX = c;
				mainBasementTileInfo[r][c].frameY = r;
			}
		}

		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[0] != sampleTileImg.size())
		{
			//SampleImg
			sampleTileImg.resize(sampleTileMaxIndex[0]);
		}

		str += "Basement";

		for (size_t i = 0; i < sampleTileImg.size(); ++i)
		{
			// Numbering
			if (i < 10)
			{
				str += "0";
				str += to_string(i);
			}
			else
			{
				str += to_string(i);
			}
			str += ".bmp";
			strcpy_s(cha, str.c_str());

			sampleTileImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Basement";

			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					SetRect(&(sampleTileInfo[r + (i * TILE_ROW)][c].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r + (i * TILE_ROW)][c].frameX = c;
					sampleTileInfo[r + (i * TILE_ROW)][c].frameY = r + (INT)(i * TILE_ROW);
				}
			}
		}

		sampleTileType = SampleTileTypes::BASEMENT;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectCaveTile() && sampleTileType != SampleTileTypes::CAVE)
	{
		// 이미지
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");

		// Main 영역
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetRect(&(mainCaveTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
				mainCaveTileInfo[r][c].frameX = c;
				mainCaveTileInfo[r][c].frameY = r;
			}
		}

		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[1] != sampleTileImg.size())
		{
			//SampleImg
			sampleTileImg.resize(sampleTileMaxIndex[1]);
		}

		str += "Cave";

		for (size_t i = 0; i < sampleTileImg.size(); ++i)
		{
			// Numbering
			if (i < 10)
			{
				str += "0";
				str += to_string(i);
			}
			else
			{
				str += to_string(i);
			}
			str += ".bmp";
			strcpy_s(cha, str.c_str());

			sampleTileImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Cave";

			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					SetRect(&(sampleTileInfo[r + (i * TILE_ROW)][c].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r + (i * TILE_ROW)][c].frameX = c;
					sampleTileInfo[r + (i * TILE_ROW)][c].frameY = r + (INT)(i * TILE_ROW);
				}
			}
		}

		sampleTileType = SampleTileTypes::CAVE;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectCellarTile() && sampleTileType != SampleTileTypes::CELLAR)
	{
		// 이미지
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");

		// Main 영역
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetRect(&(mainCellarTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
				mainCellarTileInfo[r][c].frameX = c;
				mainCellarTileInfo[r][c].frameY = r;
			}
		}

		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[2] != sampleTileImg.size())
		{
			//SampleImg
			sampleTileImg.resize(sampleTileMaxIndex[2]);
		}

		str += "Cellar";

		for (size_t i = 0; i < sampleTileImg.size(); ++i)
		{
			// Numbering
			if (i < 10)
			{
				str += "0";
				str += to_string(i);
			}
			else
			{
				str += to_string(i);
			}
			str += ".bmp";
			strcpy_s(cha, str.c_str());

			sampleTileImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Cellar";

			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					SetRect(&(sampleTileInfo[r + (i * TILE_ROW)][c].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r + (i * TILE_ROW)][c].frameX = c;
					sampleTileInfo[r + (i * TILE_ROW)][c].frameY = r + (INT)(i * TILE_ROW);
				}
			}
		}

		sampleTileType = SampleTileTypes::CELLAR;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectDepthTile() && sampleTileType != SampleTileTypes::DEPTH)
	{
		// 이미지
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");

		// Main 영역
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetRect(&(mainDepthTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
				mainDepthTileInfo[r][c].frameX = c;
				mainDepthTileInfo[r][c].frameY = r;
			}
		}

		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[3] != sampleTileImg.size())
		{
			//SampleImg
			sampleTileImg.resize(sampleTileMaxIndex[3]);
		}

		str += "Depth";

		for (size_t i = 0; i < sampleTileImg.size(); ++i)
		{
			// Numbering
			if (i < 10)
			{
				str += "0";
				str += to_string(i);
			}
			else
			{
				str += to_string(i);
			}
			str += ".bmp";
			strcpy_s(cha, str.c_str());

			sampleTileImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Depth";

			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					SetRect(&(sampleTileInfo[r + (i * TILE_ROW)][c].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r + (i * TILE_ROW)][c].frameX = c;
					sampleTileInfo[r + (i * TILE_ROW)][c].frameY = r + (INT)(i * TILE_ROW);
				}
			}
		}

		sampleTileType = SampleTileTypes::DEPTH;
		currShowIndex = 0;

		return;
	}

	// Next, Prev 버튼을 누를 때마다 샘플 이미지 변화
	if (button->GetSelectBasementTile())
	{
		//NextBtn 눌렀을 때
		if (button->GetPressNextButton())
		{
			sampleTileCurrIndex[0] = button->GetTileIndex();
			// SampleIndex 초과시 => MaxSize로
			if (sampleTileCurrIndex[0] > ((INT)sampleTileImg.size() - 1))
			{
				sampleTileCurrIndex[0] = ((INT)sampleTileImg.size() - 1);
				button->SetTileIndex(sampleTileCurrIndex[0]);
			}
			currShowIndex = sampleTileCurrIndex[0];
		}
		if(button->GetPressPrevButton())
		{
			sampleTileCurrIndex[0] = button->GetTileIndex();
			// SampleIndex는 0까지
			if (sampleTileCurrIndex[0] < 0)
			{
				sampleTileCurrIndex[0] = 0;
				button->SetTileIndex(sampleTileCurrIndex[0]);
			}
			currShowIndex = sampleTileCurrIndex[0];
		}
	}
	if (button->GetSelectCaveTile())
	{
		//NextBtn 눌렀을 때
		if (button->GetPressNextButton())
		{
			sampleTileCurrIndex[1] = button->GetTileIndex();
			// SampleIndex 초과시 => MaxSize로
			if (sampleTileCurrIndex[1] > ((INT)sampleTileImg.size() - 1))
			{
				sampleTileCurrIndex[1] = ((INT)sampleTileImg.size() - 1);
				button->SetTileIndex(sampleTileCurrIndex[1]);
			}
			currShowIndex = sampleTileCurrIndex[1];
		}
		if (button->GetPressPrevButton())
		{
			sampleTileCurrIndex[1] = button->GetTileIndex();
			// SampleIndex는 0까지
			if (sampleTileCurrIndex[1] < 0)
			{
				sampleTileCurrIndex[1] = 0;
				button->SetTileIndex(sampleTileCurrIndex[1]);
			}
			currShowIndex = sampleTileCurrIndex[1];
		}
	}
	if (button->GetSelectCellarTile())
	{
		//NextBtn 눌렀을 때
		if (button->GetPressNextButton())
		{
			sampleTileCurrIndex[2] = button->GetTileIndex();
			// SampleIndex 초과시 => MaxSize로
			if (sampleTileCurrIndex[2] > ((INT)sampleTileImg.size() - 1))
			{
				sampleTileCurrIndex[2] = ((INT)sampleTileImg.size() - 1);
				button->SetTileIndex(sampleTileCurrIndex[2]);
			}
			currShowIndex = sampleTileCurrIndex[2];
		}
		if (button->GetPressPrevButton())
		{
			sampleTileCurrIndex[2] = button->GetTileIndex();
			// SampleIndex는 0까지
			if (sampleTileCurrIndex[2] < 0)
			{
				sampleTileCurrIndex[2] = 0;
				button->SetTileIndex(sampleTileCurrIndex[2]);
			}
			currShowIndex = sampleTileCurrIndex[2];
		}
	}
	if (button->GetSelectDepthTile())
	{
		//NextBtn 눌렀을 때
		if (button->GetPressNextButton())
		{
			sampleTileCurrIndex[3] = button->GetTileIndex();
			// SampleIndex 초과시 => MaxSize로
			if (sampleTileCurrIndex[3] > ((INT)sampleTileImg.size() - 1))
			{
				sampleTileCurrIndex[3] = ((INT)sampleTileImg.size() - 1);
				button->SetTileIndex(sampleTileCurrIndex[3]);
			}
			currShowIndex = sampleTileCurrIndex[3];
		}
		if (button->GetPressPrevButton())
		{
			sampleTileCurrIndex[3] = button->GetTileIndex();
			// SampleIndex는 0까지
			if (sampleTileCurrIndex[3] < 0)
			{
				sampleTileCurrIndex[3] = 0;
				button->SetTileIndex(sampleTileCurrIndex[3]);
			}
			currShowIndex = sampleTileCurrIndex[3];
		}
	}

	// 샘플역역에서 샘플을 선택
	RECT sampleTileArea = { 900, 380, 900 + 462, 380 + 280 };
	// SingleSelectTile
	DrawSingleTile(sampleTileArea);
	// MutiSelectTile
	DrawMultiTile(sampleTileArea);

	if (Input::GetButtonDown('S'))
	{
		Save(saveIndex);
		++saveIndex;
	}
	if (Input::GetButtonDown('L'))
	{
		Load();
	}
}

void TilemapToolScene::Render(HDC hdc)
{
	// BackGround
	backGround->Render(hdc);

	// Tile
	float scale = (FLOAT)TILE_SIZE / SAMPLE_TILE_SIZE;
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		for (int r = 0; r < BASEMENT_TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetTerrain(&mainBasementTileInfo[r][c], sampleTileMaxIndex[0]);
				drawingAreaImg->EnlargeSampleTile(hdc, mainBasementTileInfo[r][c].rc.left, mainBasementTileInfo[r][c].rc.top, mainBasementTileInfo[r][c].frameX, mainBasementTileInfo[r][c].frameY, scale);
			}
		}
		break;
	case SampleTileTypes::CAVE:
		for (int r = 0; r < CAVE_TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetTerrain(&mainCaveTileInfo[r][c], sampleTileMaxIndex[1]);
				drawingAreaImg->EnlargeSampleTile(hdc, mainCaveTileInfo[r][c].rc.left, mainCaveTileInfo[r][c].rc.top, mainCaveTileInfo[r][c].frameX, mainCaveTileInfo[r][c].frameY, scale);
			}
		}
		break;
	case SampleTileTypes::CELLAR:
		for (int r = 0; r < CELLAR_TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetTerrain(&mainCellarTileInfo[r][c], sampleTileMaxIndex[2]);
				drawingAreaImg->EnlargeSampleTile(hdc, mainCellarTileInfo[r][c].rc.left, mainCellarTileInfo[r][c].rc.top, mainCellarTileInfo[r][c].frameX, mainCellarTileInfo[r][c].frameY, scale);
			}
		}
		break;
	case SampleTileTypes::DEPTH:
		for (int r = 0; r < DEPTH_TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				SetTerrain(&mainDepthTileInfo[r][c], sampleTileMaxIndex[3]);
				drawingAreaImg->EnlargeSampleTile(hdc, mainDepthTileInfo[r][c].rc.left, mainDepthTileInfo[r][c].rc.top, mainDepthTileInfo[r][c].frameX, mainDepthTileInfo[r][c].frameY, scale);
			}
		}
		break;
	case SampleTileTypes::NONE:
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				drawingAreaImg->EnlargeSampleTile(hdc, tempTileInfo[r][c].rc.left, tempTileInfo[r][c].rc.top, tempTileInfo[r][c].frameX, tempTileInfo[r][c].frameY, scale);
			}
		}
		break;
	default:
		break;
	}

	// SampleTileImage
	if (button->GetSelectSampleTile())
	{
		sampleBackGround->Render(hdc, 963, 560);

		if (initialTileBtnState)
		{
			button->SetSelecteBasementTile(true);
			initialTileBtnState = false;
		}

		if (sampleTileImg.size() != 0)
		{
			sampleTileImg[currShowIndex]->Render(hdc, (INT)(900 + (sampleTileImg[currShowIndex]->GetWidth() * DEVIDE_HALF)), (INT)(380 + (sampleTileImg[currShowIndex]->GetHeight() * DEVIDE_HALF)));
		}
	}

	// Button
	button->Render(hdc);

	// Debug
	OnDebug(hdc);
}

void TilemapToolScene::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		// SampleTileType 출력
		switch (sampleTileType)
		{
		case SampleTileTypes::NONE:
			cout << "SampleTileType : NONE\n";
			break;
		case SampleTileTypes::BASEMENT:
			cout << "SampleTileType : BASEMENT\n";
			break;
		case SampleTileTypes::CAVE:
			cout << "SampleTileType : CAVE\n";
			break;
		case SampleTileTypes::CELLAR:
			cout << "SampleTileType : CELLAR\n";
			break;
		case SampleTileTypes::DEPTH:
			cout << "SampleTileType : DEPTH\n";
			break;
		default:
			break;
		}

		// Tile
		switch (sampleTileType)
		{
		case SampleTileTypes::BASEMENT:
			for (int r = 0; r < TILE_ROW; ++r)
			{
				for (int c = 0; c < TILE_COLUMN; ++c)
				{
					Rectangle(hdc, mainBasementTileInfo[r][c].rc.left, mainBasementTileInfo[r][c].rc.top, mainBasementTileInfo[r][c].rc.right, mainBasementTileInfo[r][c].rc.bottom);
				}
			}
			break;
		case SampleTileTypes::CAVE:
			for (int r = 0; r < TILE_ROW; ++r)
			{
				for (int c = 0; c < TILE_COLUMN; ++c)
				{
					Rectangle(hdc, mainCaveTileInfo[r][c].rc.left, mainCaveTileInfo[r][c].rc.top, mainCaveTileInfo[r][c].rc.right, mainCaveTileInfo[r][c].rc.bottom);
				}
			}
			break;
		case SampleTileTypes::CELLAR:
			for (int r = 0; r < TILE_ROW; ++r)
			{
				for (int c = 0; c < TILE_COLUMN; ++c)
				{
					Rectangle(hdc, mainCellarTileInfo[r][c].rc.left, mainCellarTileInfo[r][c].rc.top, mainCellarTileInfo[r][c].rc.right, mainCellarTileInfo[r][c].rc.bottom);
				}
			}
			break;
		case SampleTileTypes::DEPTH:
			for (int r = 0; r < TILE_ROW; ++r)
			{
				for (int c = 0; c < TILE_COLUMN; ++c)
				{
					Rectangle(hdc, mainDepthTileInfo[r][c].rc.left, mainDepthTileInfo[r][c].rc.top, mainDepthTileInfo[r][c].rc.right, mainDepthTileInfo[r][c].rc.bottom);
				}
			}
			break;
		case SampleTileTypes::NONE:
			break;
		default:
			break;
		}

		if (button->GetSelectSampleTile())
		{
			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					Rectangle(hdc, sampleTileInfo[r][c].rc.left, sampleTileInfo[r][c].rc.top, sampleTileInfo[r][c].rc.right, sampleTileInfo[r][c].rc.bottom);
				}
			}
		}
	}

	// MousePointer
	wsprintf(text, "Mouse.PosX : %d", g_ptMouse.x);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 20, text, (INT)(strlen(text)));
	wsprintf(text, "Mouse.PosY : %d", g_ptMouse.y);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 40, text, (INT)(strlen(text)));

	// 선택한 샘플 타일들의 프레임값
	wsprintf(text, "Single Sample.X : %d", singleSelectedSampleTile.frameX);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 80, text, (INT)(strlen(text)));
	wsprintf(text, "Single Sample.Y : %d", singleSelectedSampleTile.frameY);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 100, text, (INT)(strlen(text)));
	wsprintf(text, "Multi Sample[0].X : %d", multiSelectedSampleTile[0][0].frameX);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 140, text, (INT)(strlen(text)));
	wsprintf(text, "Multi Sample[0].Y : %d", multiSelectedSampleTile[0][0].frameY);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 160, text, (INT)(strlen(text)));
	wsprintf(text, "Multi Sample[1].X : %d", multiSelectedSampleTile[0][1].frameX);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 180, text, (INT)(strlen(text)));
	wsprintf(text, "Multi Sample[1].Y : %d", multiSelectedSampleTile[0][1].frameY);
	TextOut(hdc, (TILEMAP_SIZE_X - 300), 200, text, (INT)(strlen(text)));

	if (multiSelectedSampleTile[1].size() <= 0)
	{
		wsprintf(text, "! !복사할 샘플 영역이 존재하지 않음! !");
		TextOut(hdc, (TILEMAP_SIZE_X - 300), 240, text, (INT)(strlen(text)));
	}

	// TileType 출력
	for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
	{
		for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
		{
			if (PtInRect(&(mainBasementTileInfo[r][c].rc), g_ptMouse))
			{
				if (Input::GetButtonDown('T'))
				{
					switch (sampleTileType)
					{
					case SampleTileTypes::BASEMENT:
						cout << "Basement frameX : " << mainBasementTileInfo[r][c].frameX << "\t" << "Basement frameY : " << mainBasementTileInfo[r][c].frameY << "\n";
						if (mainBasementTileInfo[r][c].terrain == TileTypes::WALL)
						{
							cout << "TileType : WALL\n";
						}
						if (mainBasementTileInfo[r][c].terrain == TileTypes::DOOR)
						{
							cout << "TileType : DOOR\n";
						}
						if (mainBasementTileInfo[r][c].terrain == TileTypes::ROAD)
						{
							cout << "TileType : ROAD\n";
						}
						if (mainBasementTileInfo[r][c].terrain == TileTypes::NOTHINGNESS)
						{
							cout << "TileType : NOTHINGNESS\n";
						}
						break;
					case SampleTileTypes::CAVE:
						cout << "Cave frameX : " << mainCaveTileInfo[r][c].frameX << "\t" << "Cave frameY : " << mainCaveTileInfo[r][c].frameY << "\n";
						if (mainCaveTileInfo[r][c].terrain == TileTypes::WALL)
						{
							cout << "TileType : WALL\n";
						}
						if (mainCaveTileInfo[r][c].terrain == TileTypes::DOOR)
						{
							cout << "TileType : DOOR\n";
						}
						if (mainCaveTileInfo[r][c].terrain == TileTypes::ROAD)
						{
							cout << "TileType : ROAD\n";
						}
						if (mainCaveTileInfo[r][c].terrain == TileTypes::NOTHINGNESS)
						{
							cout << "TileType : NOTHINGNESS\n";
						}
						break;
					case SampleTileTypes::CELLAR:
						cout << "Cellar frameX : " << mainCellarTileInfo[r][c].frameX << "\t" << "Cellar frameY : " << mainCellarTileInfo[r][c].frameY << "\n";
						if (mainCellarTileInfo[r][c].terrain == TileTypes::WALL)
						{
							cout << "TileType : WALL\n";
						}
						if (mainCellarTileInfo[r][c].terrain == TileTypes::DOOR)
						{
							cout << "TileType : DOOR\n";
						}
						if (mainCellarTileInfo[r][c].terrain == TileTypes::ROAD)
						{
							cout << "TileType : ROAD\n";
						}
						if (mainCellarTileInfo[r][c].terrain == TileTypes::NOTHINGNESS)
						{
							cout << "TileType : NOTHINGNESS\n";
						}
						break;
					case SampleTileTypes::DEPTH:
						cout << "Depth frameX : " << mainDepthTileInfo[r][c].frameX << "\t" << "Depth frameY : " << mainDepthTileInfo[r][c].frameY << "\n";
						if (mainDepthTileInfo[r][c].terrain == TileTypes::WALL)
						{
							cout << "TileType : WALL\n";
						}
						if (mainDepthTileInfo[r][c].terrain == TileTypes::DOOR)
						{
							cout << "TileType : DOOR\n";
						}
						if (mainDepthTileInfo[r][c].terrain == TileTypes::ROAD)
						{
							cout << "TileType : ROAD\n";
						}
						if (mainDepthTileInfo[r][c].terrain == TileTypes::NOTHINGNESS)
						{
							cout << "TileType : NOTHINGNESS\n";
						}
						break;
					case SampleTileTypes::NONE:
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

bool TilemapToolScene::ClickedButton()
{
	if (button->GetSelectSampleTile())
	{
		return true;
	}
	return false;
}

void TilemapToolScene::DrawMultiTile(RECT rc)
{
	// 샘플 영역 지정
	if (button->GetSelectSampleTile())
	{
		SelectMultiTile(rc);
	}
	// 샘플 영역 선택 했는가?
	MarkMultiPoint();
	// 메인 영역에 그리기(SampleTile 종료 && 샘플 영역을 선택 했을 때 실행)
	if ((ClickedButton() == false) && isMultiSelect)
	{
		int startX = min(multiSelectedSampleTile[0][0].frameX, multiSelectedSampleTile[0][1].frameX);
		int endX = max(multiSelectedSampleTile[0][0].frameX, multiSelectedSampleTile[0][1].frameX);
		int startY = min(multiSelectedSampleTile[0][0].frameY, multiSelectedSampleTile[0][1].frameY);
		int endY = max(multiSelectedSampleTile[0][0].frameY, multiSelectedSampleTile[0][1].frameY);
		int cloumnCount = endX - startX + 1;
		int rowCount = endY - startY + 1;
		int drawTotalCount = cloumnCount * rowCount;

		multiSelectedSampleTile[1].resize(drawTotalCount);

		int index = 0;
		for (int r = startY; r <= endY; ++r)
		{
			for (int c = startX; c <= endX; ++c)
			{
				multiSelectedSampleTile[1][index].frameX = sampleTileInfo[r][c].frameX;
				multiSelectedSampleTile[1][index].frameY = sampleTileInfo[r][c].frameY;
				++index;
			}
		}
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				switch (sampleTileType)
				{
				case SampleTileTypes::BASEMENT:
					if (PtInRect(&(mainBasementTileInfo[r][c].rc), g_ptMouse))
					{
						int originC = c;
						int originR = r;
						int plusColumn = 0;
						int plusRow = 0;
						int copyHorizontalLength = 0;
						if (Input::GetButtonDown(VK_LBUTTON))
						{
							for (int i = 0; i < multiSelectedSampleTile[1].size(); ++i)
							{
								mainBasementTileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
								mainBasementTileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
								++plusColumn;								// 복사할 가로 길이 증가
								++copyHorizontalLength;						// 복사할 가로 길이 증가
								if ((c + plusColumn) > 31)					// 세로의 범위를 넘어설 때
								{
									++r;									// 다음 세로 프레임으로 넘김.
									c = 0;									// 가로 프레임은 0
									plusColumn = 0;							// 가로 프레임은 0
								}
								if (copyHorizontalLength > endX - startX)	// 선택한 가로 길이를 다 복사하면 다음 줄 복사
								{
									r = originR;							// 원래 세로 프레임으로 돌림.(위의 상황에서 세로의 범위를 넘어서면 총 두줄이 띄어진다.)
									++plusRow;								// 세로 프레임 증가
									c = originC;							// 가로 프레임 초기화(시작 지점)
									plusColumn = 0;							// 가로 프레임 초기화
									copyHorizontalLength = 0;				// 복사할 가로 길이 초기화
								}
								if ((r + plusRow) > 19)						// 가로의 범위를 넘어설 때
								{
									r = 0;									// 가로 크기를 벗어나면 맨 첫줄로 복사
									plusRow = 0;							// 가로 크기를 벗어나면 맨 첫줄로 복사
								}
							}
							finishDrawing = true;
						}
					}
					break;
				case SampleTileTypes::CAVE:
					if (PtInRect(&(mainCaveTileInfo[r][c].rc), g_ptMouse))
					{
						int originC = c;
						int originR = r;
						int plusColumn = 0;
						int plusRow = 0;
						int copyHorizontalLength = 0;
						if (Input::GetButtonDown(VK_LBUTTON))
						{
							for (int i = 0; i < multiSelectedSampleTile[1].size(); ++i)
							{
								mainCaveTileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
								mainCaveTileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
								++plusColumn;
								++copyHorizontalLength;
								if ((c + plusColumn) > 31)
								{
									++r;
									c = 0;
									plusColumn = 0;
								}
								if (copyHorizontalLength > endX - startX)
								{
									r = originR;
									++plusRow;
									c = originC;
									plusColumn = 0;	
									copyHorizontalLength = 0;
								}
								if ((r + plusRow) > 19)
								{
									r = 0;
									plusRow = 0;
								}
							}
							finishDrawing = true;
						}
					}
					break;
				case SampleTileTypes::CELLAR:
					if (PtInRect(&(mainCellarTileInfo[r][c].rc), g_ptMouse))
					{
						int originC = c;
						int originR = r;
						int plusColumn = 0;
						int plusRow = 0;
						int copyHorizontalLength = 0;
						if (Input::GetButtonDown(VK_LBUTTON))
						{
							for (int i = 0; i < multiSelectedSampleTile[1].size(); ++i)
							{
								mainCellarTileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
								mainCellarTileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
								++plusColumn;
								++copyHorizontalLength;
								if ((c + plusColumn) > 31)
								{
									++r;
									c = 0;
									plusColumn = 0;
								}
								if (copyHorizontalLength > endX - startX)
								{
									r = originR;
									++plusRow;
									c = originC;
									plusColumn = 0;
									copyHorizontalLength = 0;
								}
								if ((r + plusRow) > 19)
								{
									r = 0;
									plusRow = 0;
								}
							}
							finishDrawing = true;
						}
					}
					break;
				case SampleTileTypes::DEPTH:
					if (PtInRect(&(mainDepthTileInfo[r][c].rc), g_ptMouse))
					{
						int originC = c;
						int originR = r;
						int plusColumn = 0;
						int plusRow = 0;
						int copyHorizontalLength = 0;
						if (Input::GetButtonDown(VK_LBUTTON))
						{
							for (int i = 0; i < multiSelectedSampleTile[1].size(); ++i)
							{
								mainDepthTileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
								mainDepthTileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
								++plusColumn;
								++copyHorizontalLength;
								if ((c + plusColumn) > 31)
								{
									++r;
									c = 0;
									plusColumn = 0;
								}
								if (copyHorizontalLength > endX - startX)
								{
									r = originR;
									++plusRow;
									c = originC;
									plusColumn = 0;
									copyHorizontalLength = 0;
								}
								if ((r + plusRow) > 19)
								{
									r = 0;
									plusRow = 0;
								}
							}
							finishDrawing = true;
						}
					}
					break;
				case SampleTileTypes::NONE:
					break;
				default:
					break;
				}
			}
		}
	}
	// 전부 그렸으면 MultiSelectedSampleTileInfo[1] 초기화
	InitializeMultiPoint();
}

void TilemapToolScene::DrawSingleTile(RECT rc)
{
	// 샘플 영역 지정
	if (button->GetSelectSampleTile())
	{
		SelectSingleTile(rc);
	}
	// 메인 역역에서 그리기
	else
	{
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				switch (sampleTileType)
				{
				case SampleTileTypes::BASEMENT:
					if (PtInRect(&(mainBasementTileInfo[r][c].rc), g_ptMouse))
					{
						if (Input::GetButtonDown(VK_RBUTTON))
						{
							mainBasementTileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
							mainBasementTileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
						}
					}
					break;
				case SampleTileTypes::CAVE:
					if (PtInRect(&(mainCaveTileInfo[r][c].rc), g_ptMouse))
					{
						if (Input::GetButtonDown(VK_RBUTTON))
						{
							mainCaveTileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
							mainCaveTileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
						}
					}
					break;
				case SampleTileTypes::CELLAR:
					if (PtInRect(&(mainCellarTileInfo[r][c].rc), g_ptMouse))
					{
						if (Input::GetButtonDown(VK_RBUTTON))
						{
							mainCellarTileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
							mainCellarTileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
						}
					}
					break;
				case SampleTileTypes::DEPTH:
					if (PtInRect(&(mainDepthTileInfo[r][c].rc), g_ptMouse))
					{
						if (Input::GetButtonDown(VK_RBUTTON))
						{
							mainDepthTileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
							mainDepthTileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
						}
					}
					break;
				case SampleTileTypes::NONE:
					break;
				default:
					break;
				}
			}
		}
	}
}

void TilemapToolScene::InitializeMultiPoint()
{
	if (finishDrawing)
	{
		multiSelectedSampleTile[1].resize(0);

		multiSelectPoint[0] = false;
		multiSelectPoint[1] = false;
		isMultiSelect = false;
		finishDrawing = false;
	}
}

void TilemapToolScene::Load(int loadIndex)
{
	string loadFileName = "Save/";
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		loadFileName += "BASEMENT";
		break;
	case SampleTileTypes::CAVE:
		loadFileName += "CAVE";
		break;
	case SampleTileTypes::CELLAR:
		loadFileName += "CELLAR";
		break;
	case SampleTileTypes::DEPTH:
		loadFileName += "DEPTH";
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}
	// 한자리 숫자일 때
	if (loadIndex < 10)
	{
		loadFileName += "0";
	}
	loadFileName += to_string(loadIndex) + ".map";

	HANDLE hFile = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD mapSaveFileInfo = sizeof(tagTile) * TILE_ROW * TILE_COLUMN;

	DWORD readByte;
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		if (ReadFile(hFile, mainBasementTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}

	CloseHandle(hFile);
}

void TilemapToolScene::MarkMultiPoint()
{
	if (multiSelectPoint[0] && multiSelectPoint[1])
	{
		isMultiSelect = true;
	}
}

void TilemapToolScene::Save(int saveIndex)
{
	string saveFileName = "Save/";
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		saveFileName += "BASEMENT";
		break;
	case SampleTileTypes::CAVE:
		saveFileName += "CAVE";
		break;
	case SampleTileTypes::CELLAR:
		saveFileName += "CELLAR";
		break;
	case SampleTileTypes::DEPTH:
		saveFileName += "DEPTH";
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}
	// 한자리 숫자일 때
	if (saveIndex < 10)
	{
		saveFileName += "0";
	}
	saveFileName += to_string(saveIndex) + ".map";

	HANDLE hFile = CreateFile(saveFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD byteSize = sizeof(tagTile) * TILE_ROW * TILE_COLUMN;

	DWORD writtenByte;
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		if (WriteFile(hFile, mainBasementTileInfo, byteSize, &writtenByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 저장에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (WriteFile(hFile, mainCaveTileInfo, byteSize, &writtenByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Cave 맵 데이터 저장에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (WriteFile(hFile, mainCellarTileInfo, byteSize, &writtenByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Cellar 맵 데이터 저장에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (WriteFile(hFile, mainDepthTileInfo, byteSize, &writtenByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Depth 맵 데이터 저장에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}

	CloseHandle(hFile);
}

void TilemapToolScene::SelectMultiTile(RECT rc)
{
	// 샘플 영역의 Point01
	if (PtInRect(&(rc), g_ptMouse))
	{
		if (Input::GetButtonDown(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rc.left;
			int selectedIdX = posX / SAMPLE_TILE_SIZE;

			int posY = g_ptMouse.y - rc.top;
			int selectedIdY = posY / SAMPLE_TILE_SIZE;

			multiSelectPoint[0] = true;

			multiSelectedSampleTile[0][0].frameX = sampleTileInfo[selectedIdY + ( currShowIndex * TILE_ROW)][selectedIdX].frameX;
			multiSelectedSampleTile[0][0].frameY = sampleTileInfo[selectedIdY + ( currShowIndex * TILE_ROW)][selectedIdX].frameY;
		}
	}
	// 샘플 영역의 Point02
	if (PtInRect(&(rc), g_ptMouse))
	{
		if (Input::GetButtonUp(VK_LBUTTON))
		{
			int posX = g_ptMouse.x - rc.left;
			int selectedIdX = posX / SAMPLE_TILE_SIZE;

			int posY = g_ptMouse.y - rc.top;
			int selectedIdY = posY / SAMPLE_TILE_SIZE;

			multiSelectPoint[1] = true;

			multiSelectedSampleTile[0][1].frameX = sampleTileInfo[selectedIdY + (currShowIndex * TILE_ROW)][selectedIdX].frameX;
			multiSelectedSampleTile[0][1].frameY = sampleTileInfo[selectedIdY + (currShowIndex * TILE_ROW)][selectedIdX].frameY;
		}
	}
}

void TilemapToolScene::SelectSingleTile(RECT rc)
{
	if (ClickedButton())
	{
		if (PtInRect(&(rc), g_ptMouse))
		{
			if (Input::GetButtonDown(VK_RBUTTON))
			{
				int posX = g_ptMouse.x - rc.left;
				int selectedIdX = posX / SAMPLE_TILE_SIZE;

				int posY = g_ptMouse.y - rc.top;
				int selectedIdY = posY / SAMPLE_TILE_SIZE;

				singleSelectedSampleTile.frameX = sampleTileInfo[selectedIdY + (currShowIndex * TILE_ROW)][selectedIdX].frameX;
				singleSelectedSampleTile.frameY = sampleTileInfo[selectedIdY + (currShowIndex * TILE_ROW)][selectedIdX].frameY;
			}
		}
	}
}
