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

	// selectTile
	selectedSampleTile.frameX = 0;
	selectedSampleTile.frameY = 0;

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
	if (GET_SINGLETON_KEY->IsStayKeyDown(VK_LCONTROL) && GET_SINGLETON_KEY->IsOnceKeyDown('D'))
	{
		debugMode = !debugMode;
	}
	// Tile
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

			selectedSampleTile.frameX = sampleTileInfo[selectedIdY][selectedIdX].frameX;
			selectedSampleTile.frameY = sampleTileInfo[selectedIdY][selectedIdX].frameY;
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
					tileInfo[r][c].frameX = selectedSampleTile.frameX;
					tileInfo[r][c].frameY = selectedSampleTile.frameY;
				}
			}
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
			sampleTileImg->EnlargeSampleTile(hdc, tileInfo[r][c].rc.left, tileInfo[r][c].rc.top, tileInfo[r][c].frameX, tileInfo[r][c].frameY, scale);
		}
	}

	// SampleTileImage
	sampleTileImg->Render(hdc, 900 + (sampleTileImg->GetWidth() * DEVIDE_HALF), 380 + (sampleTileImg->GetHeight() * DEVIDE_HALF));


	// Button
	button->Render(hdc);

	// Debug
	OnDebug(hdc);
}

void TilemapToolScene::OnDebug(HDC hdc)
{
	sampleTileImg->EnlargeSampleTile(hdc, 1320, 40, selectedSampleTile.frameX, selectedSampleTile.frameY, 3.0f);

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
