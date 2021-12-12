#include "MainConfig.h"
#include "InGameScene.h"

#include "Image.h"
#include "Player.h"

#include "MapEditing.h"

HRESULT InGameScene::Init()
{
	// Tile
	Load(1);

	// Tilemap Image
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		break;
	case SampleTileTypes::CAVE:
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
		break;
	case SampleTileTypes::CELLAR:
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");
		break;
	case SampleTileTypes::DEPTH:
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}

	// Player
	playerIsaac = new Player;
	playerIsaac->Init();
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				colliderTileInfo[r * TILE_COLUMN + c] = mainBasementTileInfo[r][c];
			}
		};
		break;
	case SampleTileTypes::CAVE:
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				colliderTileInfo[r * TILE_COLUMN + c] = mainCaveTileInfo[r][c];
			}
		};
		break;
	case SampleTileTypes::CELLAR:
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				colliderTileInfo[r * TILE_COLUMN + c] = mainCellarTileInfo[r][c];
			}
		};
		break;
	case SampleTileTypes::DEPTH:
		for (int r = 0; r < TILE_ROW; ++r)
		{
			for (int c = 0; c < TILE_COLUMN; ++c)
			{
				colliderTileInfo[r * TILE_COLUMN + c] = mainDepthTileInfo[r][c];
			}
		};
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}
	playerIsaac->SetTileInfo(colliderTileInfo);

	temp = new MapEditing;
	temp->Init();

	return S_OK;
}

void InGameScene::Release()
{
	SAFE_RELEASE(playerIsaac);
	SAFE_RELEASE(temp);
}

void InGameScene::Update()
{
	playerIsaac->Update();
}

void InGameScene::Render(HDC hdc)
{
	TileRender(hdc);
	playerIsaac->Render(hdc);
}

void InGameScene::Load(int loadIndex)
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

void InGameScene::TileRender(HDC hdc)
{
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
		break;
	default:
		break;
	}
}
