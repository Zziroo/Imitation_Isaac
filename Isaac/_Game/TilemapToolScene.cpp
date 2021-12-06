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
	sampleTileImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement00.bmp");

	// Tile
	for (int r = 0; r < TILE_ROW; ++r)
	{
		for (int c = 0; c < TILE_COLUMN; ++c)
		{
			SetRect(&(tileInfo[r][c].rc), c * TILE_SIZE, r * TILE_SIZE, (c + 1) * TILE_SIZE, (r + 1) * TILE_SIZE);
			tileInfo[r][c].frameX = 32;
			tileInfo[r][c].frameY = 0;
			tileInfo[r][c].terrain = TileType::ROAD;
		}
	}

	// SampleMapTile
	for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
	{
		for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
		{
			SetRect(&(sampleTileInfo[r][c].rc), 900 + (c * SAMPLE_TILE_SIZE), 380 + (r * SAMPLE_TILE_SIZE), 900 + (c + 1) * SAMPLE_TILE_SIZE, 380 + (r + 1) * SAMPLE_TILE_SIZE);
			sampleTileInfo[r][c].frameX = c;
			sampleTileInfo[r][c].frameY = r;
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
	if (GET_SINGLETON_KEY->IsStayKeyDown(VK_LCONTROL) && GET_SINGLETON_KEY->IsOnceKeyDown('R'))
	{
		debugMode = !debugMode;
	}

	if (button->GetSelectSampleTile())
	{
		// Tile
		// SingleSelectTile
		// 샘플역역에서 샘플을 선택
		RECT sampleArea = { 900, 380, 900 + sampleTileImg->GetWidth(), 380 + sampleTileImg->GetHeight() };

		if (PtInRect(&(sampleArea), g_ptMouse))
		{
			if (GET_SINGLETON_KEY->IsOnceKeyDown('Q'))
			{
				int posX = g_ptMouse.x - sampleArea.left;
				int selectedIdX = posX / SAMPLE_TILE_SIZE;

				int posY = g_ptMouse.y - sampleArea.top;
				int selectedIdY = posY / SAMPLE_TILE_SIZE;

				singleSelectedSampleTile.frameX = sampleTileInfo[selectedIdY][selectedIdX].frameX;
				singleSelectedSampleTile.frameY = sampleTileInfo[selectedIdY][selectedIdX].frameY;
				cout << "singleSelectedSampleTile.frameX : " << singleSelectedSampleTile.frameX << "\t" << "singleSelectedSampleTile.frameY : " << singleSelectedSampleTile.frameY << "\n";
			}
		}
		// 메인역역에서 선택된 샘플 정보로 수정
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				if (PtInRect(&(tileInfo[r][c].rc), g_ptMouse))
				{
					if (GET_SINGLETON_KEY->IsOnceKeyDown('W'))
					{
						tileInfo[r][c].frameX = singleSelectedSampleTile.frameX;
						tileInfo[r][c].frameY = singleSelectedSampleTile.frameY;
					}
				}
			}
		}
		// MutiSelectTile
		// 샘플 영역의 시작
		if (PtInRect(&(sampleArea), g_ptMouse))
		{
			if (GET_SINGLETON_KEY->IsOnceKeyDown('A'))
			{
				int posX = g_ptMouse.x - sampleArea.left;
				int selectedIdX = posX / SAMPLE_TILE_SIZE;

				int posY = g_ptMouse.y - sampleArea.top;
				int selectedIdY = posY / SAMPLE_TILE_SIZE;

				multiSelectedSampleTile[0][0].frameX = sampleTileInfo[selectedIdY][selectedIdX].frameX;
				multiSelectedSampleTile[0][0].frameY = sampleTileInfo[selectedIdY][selectedIdX].frameY;
				cout << "multiSelectedSampleTile[0][0].frameX : " << multiSelectedSampleTile[0][0].frameX << "\t" << "multiSelectedSampleTile[0][0].frameY : " << multiSelectedSampleTile[0][0].frameY << "\n";
			}
		}
		// 샘플 영역의 끝
		if (PtInRect(&(sampleArea), g_ptMouse))
		{
			if (GET_SINGLETON_KEY->IsOnceKeyDown('S'))
			{
				int posX = g_ptMouse.x - sampleArea.left;
				int selectedIdX = posX / SAMPLE_TILE_SIZE;

				int posY = g_ptMouse.y - sampleArea.top;
				int selectedIdY = posY / SAMPLE_TILE_SIZE;

				multiSelectedSampleTile[0][1].frameX = sampleTileInfo[selectedIdY][selectedIdX].frameX;
				multiSelectedSampleTile[0][1].frameY = sampleTileInfo[selectedIdY][selectedIdX].frameY;

				isMultiSelect = true;

				cout << "multiSelectedSampleTile[0][1].frameX : " << multiSelectedSampleTile[0][1].frameX << "\t" << "multiSelectedSampleTile[0][1].frameY : " << multiSelectedSampleTile[0][1].frameY << "\n";
			}
		}

		if (isMultiSelect)
		{
			// 문제!! => 타일을 하나 받으면 min, max 적용 안됨	
			int startX = min(multiSelectedSampleTile[0][0].frameX, multiSelectedSampleTile[0][1].frameX);
			int endX = max(multiSelectedSampleTile[0][0].frameX, multiSelectedSampleTile[0][1].frameX);
			int startY = min(multiSelectedSampleTile[0][0].frameY, multiSelectedSampleTile[0][1].frameY);
			int endY = max(multiSelectedSampleTile[0][0].frameY, multiSelectedSampleTile[0][1].frameY);
			int multiSelectedSampleCloumnCount = endX - startX + 1;
			int multiSelectedSampleRowCount = endY - startY + 1;
			int multiSelectedSampleTotalCount = multiSelectedSampleCloumnCount * multiSelectedSampleRowCount;

			multiSelectedSampleTile[1].resize(multiSelectedSampleTotalCount);

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
			// 메인 영역에서 선택된 샘플 정보로 수정
			for (int r = 0; r < TILE_ROW; ++r)
			{
				for (int c = 0; c < TILE_COLUMN; ++c)
				{
					if (PtInRect(&(tileInfo[r][c].rc), g_ptMouse))
					{
						int plusColumn = 0;
						int plusRow = 0;
						if (GET_SINGLETON_KEY->IsOnceKeyDown('D'))
						{
							for (int i = 0; i < multiSelectedSampleTile[1].size(); ++i)
							{
								tileInfo[r + plusRow][c + plusColumn].frameX = multiSelectedSampleTile[1][i].frameX;
								tileInfo[r + plusRow][c + plusColumn].frameY = multiSelectedSampleTile[1][i].frameY;
								++plusColumn;
								if (plusColumn > endX - startX)
								{
									++plusRow;
									plusColumn = 0;
								}
							}
							finishDrawing = true;
						}
					}
				}
			}
		}
		// 전부 그렸으면 MultiSelectedSampleTileInfo[1] 초기화
		if (finishDrawing)
		{
			multiSelectedSampleTile[1].resize(0);

			isMultiSelect = false;
			finishDrawing = false;
		}
	}

	// Button
	button->Update();

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
			SetTerrain(&tileInfo[r][c]);
			sampleTileImg->EnlargeSampleTile(hdc, tileInfo[r][c].rc.left, tileInfo[r][c].rc.top, tileInfo[r][c].frameX, tileInfo[r][c].frameY, scale);
		}
	}

	// SampleTileImage
	if (button->GetSelectSampleTile())
	{
		sampleBackGround->Render(hdc, 963, 560);
		sampleTileImg->Render(hdc, (INT)(900 + (sampleTileImg->GetWidth() * DEVIDE_HALF)), (INT)(380 + (sampleTileImg->GetHeight() * DEVIDE_HALF)));
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
	TextOut(hdc, (TILEMAP_SIZE_X - 200), 20, text, (INT)(strlen(text)));
	wsprintf(text, "Mouse.PosY : %d", g_ptMouse.y);
	TextOut(hdc, (TILEMAP_SIZE_X - 200), 40, text, (INT)(strlen(text)));

	// TileType 출력
	for (int r = 0; r < SAMPLE_TILE_ROW; ++r)
	{
		for (int c = 0; c < SAMPLE_TILE_COLUMN; ++c)
		{
			if (PtInRect(&(tileInfo[r][c].rc), g_ptMouse))
			{
				if (GET_SINGLETON_KEY->IsOnceKeyDown('E'))
				{
					cout << "frameX : " << tileInfo[r][c].frameX << "\t" << "frameY : " << tileInfo[r][c].frameY << "\n";
					if (tileInfo[r][c].terrain == TileType::WALL)
					{
						cout << "TileType : WALL\n";
					}
					if (tileInfo[r][c].terrain == TileType::DOOR)
					{
						cout << "TileType : DOOR\n";
					}
					if (tileInfo[r][c].terrain == TileType::ROAD)
					{
						cout << "TileType : ROAD\n";
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
				Rectangle(hdc, tileInfo[r][c].rc.left, tileInfo[r][c].rc.top, tileInfo[r][c].rc.right, tileInfo[r][c].rc.bottom);
			}
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
}
