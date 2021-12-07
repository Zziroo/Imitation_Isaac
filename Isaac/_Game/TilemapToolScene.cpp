#include "MainConfig.h"
#include "TilemapToolScene.h"

#include "Button.h"
#include "ButtonFunction.h"
#include "Image.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);
	// BackGround
	backGround = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround01.bmp");
	sampleBackGround = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround02.bmp");
	// sampleTileImage
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Nothingness.bmp");

	// MainTile
	for (int r = 0; r < TILE_ROW; ++r)
	{
		for (int c = 0; c < TILE_COLUMN; ++c)
		{
			SetRect(&(mainTileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
			mainTileInfo[r][c].frameX = c;
			mainTileInfo[r][c].frameY = r;
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
		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[0] != sampleImg.size())
		{
			//SampleImg
			sampleImg.resize(sampleTileMaxIndex[0]);

			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					sampleTileInfo[r][c].resize(sampleTileMaxIndex[0]);
				}
			}
		}
		str += "Basement";
		for (size_t i = 0; i < sampleImg.size(); ++i)
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

			sampleImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Basement";
		}

		for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
		{
			for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
			{
				for (size_t i = 0; i < sampleTileInfo[r][c].size(); ++i)
				{
					SetRect(&(sampleTileInfo[r][c][i].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r][c][i].frameX = c;
					sampleTileInfo[r][c][i].frameY = r;
				}
			}
		}

		sampleTileType = SampleTileTypes::BASEMENT;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectCaveTile() && sampleTileType != SampleTileTypes::CAVE)
	{
		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[1] != sampleImg.size())
		{
			//SampleImg
			sampleImg.resize(sampleTileMaxIndex[1]);

			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					sampleTileInfo[r][c].resize(sampleTileMaxIndex[1]);
				}
			}
		}
		str += "Cave";
		for (size_t i = 0; i < sampleImg.size(); ++i)
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

			sampleImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Cave";
		}

		for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
		{
			for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
			{
				for (size_t i = 0; i < sampleTileInfo[r][c].size(); ++i)
				{
					SetRect(&(sampleTileInfo[r][c][i].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r][c][i].frameX = c;
					sampleTileInfo[r][c][i].frameY = r;
				}
			}
		}

		sampleTileType = SampleTileTypes::CAVE;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectCellarTile() && sampleTileType != SampleTileTypes::CELLAR)
	{
		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[2] != sampleImg.size())
		{
			//SampleImg
			sampleImg.resize(sampleTileMaxIndex[2]);

			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					sampleTileInfo[r][c].resize(sampleTileMaxIndex[2]);
				}
			}
		}
		str += "Cellar";
		for (size_t i = 0; i < sampleImg.size(); ++i)
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

			sampleImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Cellar";
		}

		for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
		{
			for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
			{
				for (size_t i = 0; i < sampleTileInfo[r][c].size(); ++i)
				{
					SetRect(&(sampleTileInfo[r][c][i].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r][c][i].frameX = c;
					sampleTileInfo[r][c][i].frameY = r;
				}
			}
		}

		sampleTileType = SampleTileTypes::CELLAR;
		currShowIndex = 0;

		return;
	}
	if (button->GetSelectDepthTile() && sampleTileType != SampleTileTypes::DEPTH)
	{
		// SampleImg의 size보다 크거나 작을 때 크기를 조정
		if (sampleTileMaxIndex[3] != sampleImg.size())
		{
			//SampleImg
			sampleImg.resize(sampleTileMaxIndex[3]);

			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					sampleTileInfo[r][c].resize(sampleTileMaxIndex[3]);
				}
			}
		}
		str += "Depth";
		for (size_t i = 0; i < sampleImg.size(); ++i)
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

			sampleImg[i] = GET_SINGLETON_IMAGE->FindImage(cha);

			str = "Image/Tilemap/Tile/Depth";
		}

		for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
		{
			for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
			{
				for (size_t i = 0; i < sampleTileInfo[r][c].size(); ++i)
				{
					SetRect(&(sampleTileInfo[r][c][i].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
					sampleTileInfo[r][c][i].frameX = c;
					sampleTileInfo[r][c][i].frameY = r;
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
			if (sampleTileCurrIndex[0] > ((INT)sampleImg.size() - 1))
			{
				sampleTileCurrIndex[0] = ((INT)sampleImg.size() - 1);
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
			if (sampleTileCurrIndex[1] > ((INT)sampleImg.size() - 1))
			{
				sampleTileCurrIndex[1] = ((INT)sampleImg.size() - 1);
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
			if (sampleTileCurrIndex[2] > ((INT)sampleImg.size() - 1))
			{
				sampleTileCurrIndex[2] = ((INT)sampleImg.size() - 1);
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
			if (sampleTileCurrIndex[3] > ((INT)sampleImg.size() - 1))
			{
				sampleTileCurrIndex[3] = ((INT)sampleImg.size() - 1);
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
}

void TilemapToolScene::Render(HDC hdc)
{
	// BackGround
	backGround->Render(hdc);

	// Tile
	float scale = (FLOAT)TILE_SIZE / SAMPLE_TILE_SIZE;
	for (int r = 0; r < TILE_ROW; ++r)
	{
		for (int c = 0; c < TILE_COLUMN; ++c)
		{
			SetTerrain(&mainTileInfo[r][c]);
			drawingAreaImg->EnlargeSampleTile(hdc, mainTileInfo[r][c].rc.left, mainTileInfo[r][c].rc.top, mainTileInfo[r][c].frameX, mainTileInfo[r][c].frameY, scale);
		}
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

		if (sampleImg.size() != 0)
		{
			sampleImg[currShowIndex]->Render(hdc, (INT)(900 + (sampleImg[currShowIndex]->GetWidth() * DEVIDE_HALF)), (INT)(380 + (sampleImg[currShowIndex]->GetHeight() * DEVIDE_HALF)));
		}
	}

	// Button
	button->Render(hdc);

	// Debug
	OnDebug(hdc);
}

void TilemapToolScene::OnDebug(HDC hdc)
{
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
			if (PtInRect(&(mainTileInfo[r][c].rc), g_ptMouse))
			{
				if (Input::GetButtonDown('T'))
				{
					cout << "frameX : " << mainTileInfo[r][c].frameX << "\t" << "frameY : " << mainTileInfo[r][c].frameY << "\n";
					if (mainTileInfo[r][c].terrain == TileTypes::WALL)
					{
						cout << "TileType : WALL\n";
					}
					if (mainTileInfo[r][c].terrain == TileTypes::DOOR)
					{
						cout << "TileType : DOOR\n";
					}
					if (mainTileInfo[r][c].terrain == TileTypes::ROAD)
					{
						cout << "TileType : ROAD\n";
					}
					if (mainTileInfo[r][c].terrain == TileTypes::NOTHINGNESS)
					{
						cout << "TileType : NOTHINGNESS\n";
					}
				}
			}
		}
	}

	if (debugMode)
	{
		// Tile
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				Rectangle(hdc, mainTileInfo[r][c].rc.left, mainTileInfo[r][c].rc.top, mainTileInfo[r][c].rc.right, mainTileInfo[r][c].rc.bottom);
			}
		}

		if (button->GetSelectSampleTile())
		{
			// SampleTile
			for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
			{
				for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
				{
					if (sampleTileInfo[r][c].size() != 0)
					{
						Rectangle(hdc, sampleTileInfo[r][c][currShowIndex].rc.left, sampleTileInfo[r][c][currShowIndex].rc.top, sampleTileInfo[r][c][currShowIndex].rc.right, sampleTileInfo[r][c][currShowIndex].rc.bottom);
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
				multiSelectedSampleTile[1][index].frameX = sampleTileInfo[r][c][0].frameX;
				multiSelectedSampleTile[1][index].frameY = sampleTileInfo[r][c][0].frameY;
				++index;
			}
		}
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				if (PtInRect(&(mainTileInfo[r][c].rc), g_ptMouse))
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
							mainTileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
							mainTileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
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
				if (PtInRect(&(mainTileInfo[r][c].rc), g_ptMouse))
				{
					if (Input::GetButtonDown(VK_RBUTTON))
					{
						mainTileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
						mainTileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
					}
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

void TilemapToolScene::MarkMultiPoint()
{
	if (multiSelectPoint[0] && multiSelectPoint[1])
	{
		isMultiSelect = true;
	}
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

			multiSelectedSampleTile[0][0].frameX = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameX;
			multiSelectedSampleTile[0][0].frameY = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameY;
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

			multiSelectedSampleTile[0][1].frameX = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameX;
			multiSelectedSampleTile[0][1].frameY = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameY;
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

				singleSelectedSampleTile.frameX = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameX;
				singleSelectedSampleTile.frameY = sampleTileInfo[selectedIdY][selectedIdX][currShowIndex].frameY;
			}
		}
	}
}
