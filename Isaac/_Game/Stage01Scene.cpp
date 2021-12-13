#include "MainConfig.h"
#include "Stage01Scene.h"

#include "Image.h"
#include "MapEditing.h"

HRESULT Stage01Scene::Init()
{
	stage01 = new MapEditing;
	stage01->Init();
	// Stage01의 Size를 받기
	_stageSize = stage01->GetStageSize();
	// StartPoint를 받기
	_startPoint = stage01->GetStartPoint();
	stageColumn = _startPoint;
	stageRow = _startPoint;
	// Stage Size만큼 resize하고
	stage01Index.resize(_stageSize);
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		stage01Index[i].resize(_stageSize);
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			// Stage 정보를 받아오기
			stage01Index[i][j] = stage01->GetStage()[i][j];
		}
	}
	// Load
	Load(stage01Index[_startPoint][_startPoint]);
	// Tilemap Image
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");

	// 맵의 정보를 콘솔창에 보여줌
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			cout << stage01Index[i][j] << "\t";
			if (stage01Index[i][j].empty())
			{
				cout << "########\t";
			}
		}
		cout << "\n";
	}

	return S_OK;
}

void Stage01Scene::Release()
{
	SAFE_RELEASE(stage01);
}

void Stage01Scene::Update()
{
	// 예시) 상,하,좌,우 키를 입력해서 맵을 바꿈.(맵의 종류를 알아서 보여줘야함)
	if (Input::GetButtonDown(VK_UP))
	{
		--stageRow;
		if (stageRow < 0)
		{
			stageRow = 0;
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		++stageRow;
		if (stageRow >= _stageSize)
		{
			stageRow = _stageSize - 1;
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		--stageColumn;
		if (stageColumn < 0)
		{
			stageColumn = 0;
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		++stageColumn;
		if (stageColumn >= _stageSize)
		{
			stageColumn = _stageSize - 1;
		}
		LoadMap();
	}
}

void Stage01Scene::Render(HDC hdc)
{
	TileRender(hdc);
}

void Stage01Scene::Load(string loadFileName)
{
	HANDLE hFile = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#ifdef _DEBUG
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << GetLastError();
	}
#endif
	DWORD mapLoadFileInfo = sizeof(tagTile) * TILE_ROW * TILE_COLUMN;

	DWORD readByte = 0;
	switch (sampleTileType)
	{
	case SampleTileTypes::BASEMENT:
		if (ReadFile(hFile, mainBasementTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			cout << GetLastError();
			MessageBox(g_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
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

void Stage01Scene::LoadMap()
{
	// Stage01Index가 비어있으면 가면 안됨.
	if (stage01Index[stageRow][stageColumn].empty() == false)
	{
		// SampleTileType 속성을 바꿔줘야함
		if (stage01Index[stageRow][stageColumn].substr(5, 1) == "B")
		{
			sampleTileType = SampleTileTypes::BASEMENT;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		}
		if (stage01Index[stageRow][stageColumn].substr(5, 1) == "C")
		{
			if (stage01Index[stageRow][stageColumn].substr(6, 1) == "A")
			{
				sampleTileType = SampleTileTypes::CAVE;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
			}
			if (stage01Index[stageRow][stageColumn].substr(6, 1) == "E")
			{
				sampleTileType = SampleTileTypes::CELLAR;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");		// 문제 발생 => CELLAR00.map Load()시 readByte = 0 이 돼버림.
			}
		}
		if (stage01Index[stageRow][stageColumn].substr(5, 1) == "D")
		{
			sampleTileType = SampleTileTypes::DEPTH;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");			// 문제 발생 => DEPTH00.map Load()시 readByte = 0 이 돼버림.
		}
		// Load
		Load(stage01Index[stageRow][stageColumn]);
	}
}

void Stage01Scene::TileRender(HDC hdc)
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
