#include "MainConfig.h"
#include "Stage01Scene.h"

#include "DoorEditing.h"
#include "Image.h"
#include "Minimap.h"
#include "Player.h"

HRESULT Stage01Scene::Init()
{
	// Tilemap Image
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
	// StartPoint Infomation Image
	infomationStartImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Info.bmp");

	// Door
	door = new DoorEditing;
	door->Init();
	// Stage01의 Size를 받기
	_stageSize = door->GetStageSize();
	// Start Point를 받기
	_startPoint = door->GetStartPoint();
	currColumn = _startPoint;
	currRow = _startPoint;
	// Stage Size만큼 resize하고
	stage01Index.resize(_stageSize);
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		stage01Index[i].resize(_stageSize);
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			// Stage 정보를 받아오기
			stage01Index[i][j] = door->GetStage()[i][j];
		}
	}
	// Room Size만큼 resize하고
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			roomInfo[i][j] = door->GetRoomType()[i][j];
		}
	}
	// DOOR_INFO 를 저장
	doorInfo.resize(_stageSize);
	for (size_t i = 0; i < doorInfo.size(); ++i)
	{
		doorInfo[i].resize(_stageSize);
		for (size_t j = 0; j < doorInfo[i].size(); ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				doorInfo[i][j][k] = door->GetDoorInfo()[i][j][k];
			}
		}
	}

	// Load
	Load(stage01Index[_startPoint][_startPoint]);

#ifdef _DEBUG RoomInfo
	std::cout << "Stage01Scene => DoorEditing => RoomInfo\n";
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			switch (roomInfo[i][j])
			{
			case RoomTypes::BOSS:
				std::cout << "BOSS\t";
				break;
			case RoomTypes::CURSE:
				std::cout << "COURSE\t";
				break;
			case RoomTypes::ITEM:
				std::cout << "ITEM\t";
				break;
			case RoomTypes::NORMAL:
				std::cout << "NORMAL\t";
				break;
			case RoomTypes::PRIVATE:
				std::cout << "PRIVATE\t";
				break;
			case RoomTypes::SATAN:
				std::cout << "SATAN\t";
				break;
			case RoomTypes::START:
				std::cout << "START\t";
				break;
			case RoomTypes::NONE:
				std::cout << "NONE\t";
				break;
			default:
				std::cout << "####\t";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
#endif

	// Player
	player = new Player;
	player->Init();
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
	player->SetTileInfo(colliderTileInfo);
	player->SetDoorInfo(&doorInfo);
	player->SetStageSize(_stageSize);

	// Minimap
	minimap = new Minimap;
	minimap->SetRoomInfo(&roomInfo);
	minimap->SetStageSize(_stageSize);
	minimap->SetStartPointRow(currRow);
	minimap->SetStartPointColumn(currColumn);
	minimap->Init();

	return S_OK;
}

void Stage01Scene::Release()
{
	SAFE_RELEASE(door);
	SAFE_RELEASE(minimap);
	SAFE_RELEASE(player);
}

void Stage01Scene::Update()
{
	// 예시) 상,하,좌,우 키를 입력해서 맵을 바꿈.(맵의 종류를 알아서 보여줘야함)
	if (Input::GetButtonDown(VK_UP))
	{
		if (doorInfo[currRow][currColumn][0].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][0].img != nullptr)
		{
			--currRow;
			if (currRow < 0)
			{
				currRow = 0;
			}
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		if (doorInfo[currRow][currColumn][1].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][1].img != nullptr)
		{
			++currRow;
			if (currRow >= _stageSize)
			{
				currRow = _stageSize - 1;
			}
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_LEFT))
	{
		if (doorInfo[currRow][currColumn][2].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][2].img != nullptr)
		{
			--currColumn;
			if (currColumn < 0)
			{
				currColumn = 0;
			}
		}
		LoadMap();
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		if (doorInfo[currRow][currColumn][3].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][3].img != nullptr)
		{
			++currColumn;
			if (currColumn >= _stageSize)
			{
				currColumn = _stageSize - 1;
			}
		}
		LoadMap();
	}

	// Door의 정보를 Update
	for (size_t i = 0; i < doorInfo.size(); ++i)
	{
		for (size_t j = 0; j < doorInfo[i].size(); ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				doorInfo[i][j][k] = door->GetDoorInfo()[i][j][k];
			}
		}
	}
	// Player Update
	player->SetCurrCloumn(currColumn);
	player->SetCurrRow(currRow);
	player->SetDoorInfo(&doorInfo);
	player->Update();
	// Map Update
	if (player->GetEnterNextDoor()[0])
	{
		// 상
		if (doorInfo[currRow][currColumn][0].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][0].img != nullptr)
		{
			--currRow;
			if (currRow < 0)
			{
				currRow = 0;
			}
		}
		LoadMap();
		player->SetEnterNextUpDoor(false);
	}
	if (player->GetEnterNextDoor()[1])
	{
		// 하
		if (doorInfo[currRow][currColumn][1].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][1].img != nullptr)
		{
			++currRow;
			if (currRow >= _stageSize)
			{
				currRow = _stageSize - 1;
			}
		}
		LoadMap();
		player->SetEnterNextDownDoor(false);
	}
	if (player->GetEnterNextDoor()[2])
	{
		// 좌
		if (doorInfo[currRow][currColumn][2].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][2].img != nullptr)
		{
			--currColumn;
			if (currColumn < 0)
			{
				currColumn = 0;
			}
		}
		LoadMap();
		player->SetEnterNextLeftDoor(false);
	}
	if (player->GetEnterNextDoor()[3])
	{
		// 우
		if (doorInfo[currRow][currColumn][3].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][3].img != nullptr)
		{
			++currColumn;
			if (currColumn >= _stageSize)
			{
				currColumn = _stageSize - 1;
			}
		}
		LoadMap();
		player->SetEnterNextRightDoor(false);
	}
	// DoorEditing Update
	door->SetLocatedColumn(currColumn);
	door->SetLocatedRow(currRow);
	door->Update();
	// Minimap Update
	minimap->SetCurrCloumn(currColumn);
	minimap->SetCurrRow(currRow);
	minimap->Update();
}

void Stage01Scene::Render(HDC hdc)
{
	TileRender(hdc);
	if (currRow == _startPoint && currColumn == _startPoint)
	{
		infomationStartImg->Render(hdc, (INT)(WIN_SIZE_X * DEVIDE_HALF), (INT)(WIN_SIZE_Y * DEVIDE_HALF));
	}
	door->Render(hdc);
	player->Render(hdc);
	minimap->Render(hdc);
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
	if (stage01Index[currRow][currColumn].empty() == false)
	{
		// SampleTileType 속성을 바꿔줘야함
		if (stage01Index[currRow][currColumn].substr(5, 1) == "B")
		{
			sampleTileType = SampleTileTypes::BASEMENT;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		}
		if (stage01Index[currRow][currColumn].substr(5, 1) == "C")
		{
			if (stage01Index[currRow][currColumn].substr(6, 1) == "A")
			{
				sampleTileType = SampleTileTypes::CAVE;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
			}
			if (stage01Index[currRow][currColumn].substr(6, 1) == "E")
			{
				sampleTileType = SampleTileTypes::CELLAR;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");		// 문제 발생 => CELLAR00.map Load()시 readByte = 0 이 돼버림.
			}
		}
		if (stage01Index[currRow][currColumn].substr(5, 1) == "D")
		{
			sampleTileType = SampleTileTypes::DEPTH;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");			// 문제 발생 => DEPTH00.map Load()시 readByte = 0 이 돼버림.
		}
		// Load
		Load(stage01Index[currRow][currColumn]);
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
