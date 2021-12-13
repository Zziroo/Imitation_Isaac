#include "MainConfig.h"
#include "Stage01Scene.h"

#include "Image.h"
#include "MapEditing.h"

HRESULT Stage01Scene::Init()
{
	stage01 = new MapEditing;
	stage01->Init();
	// Stage01�� Size�� �ޱ�
	_stageSize = stage01->GetStageSize();
	// StartPoint�� �ޱ�
	_startPoint = stage01->GetStartPoint();
	stageColumn = _startPoint;
	stageRow = _startPoint;
	// Stage Size��ŭ resize�ϰ�
	stage01Index.resize(_stageSize);
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		stage01Index[i].resize(_stageSize);
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			// Stage ������ �޾ƿ���
			stage01Index[i][j] = stage01->GetStage()[i][j];
		}
	}
	// Load
	Load(stage01Index[_startPoint][_startPoint]);
	// Tilemap Image
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");

	// ���� ������ �ܼ�â�� ������
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
	// ����) ��,��,��,�� Ű�� �Է��ؼ� ���� �ٲ�.(���� ������ �˾Ƽ� ���������)
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
			MessageBox(g_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			cout << GetLastError();
			MessageBox(g_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
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
	// Stage01Index�� ��������� ���� �ȵ�.
	if (stage01Index[stageRow][stageColumn].empty() == false)
	{
		// SampleTileType �Ӽ��� �ٲ������
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
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");		// ���� �߻� => CELLAR00.map Load()�� readByte = 0 �� �Ź���.
			}
		}
		if (stage01Index[stageRow][stageColumn].substr(5, 1) == "D")
		{
			sampleTileType = SampleTileTypes::DEPTH;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");			// ���� �߻� => DEPTH00.map Load()�� readByte = 0 �� �Ź���.
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
