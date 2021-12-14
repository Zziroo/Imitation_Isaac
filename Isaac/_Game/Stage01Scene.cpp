#include "MainConfig.h"
#include "Stage01Scene.h"

#include "DoorEditing.h"
#include "Image.h"
#include "Player.h"

HRESULT Stage01Scene::Init()
{
	// Tilemap Image
	drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");

	// Door
	door = new DoorEditing;
	door->Init();
	// Stage01의 Size를 받기
	_stageSize = door->GetStageSize();
	// Start Point를 받기
	_startPoint = door->GetStartPoint();
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
	cout << "Stage01Scene => DoorEditing => RoomInfo\n";
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			switch (roomInfo[i][j])
			{
			case RoomTypes::BOSS:
				cout << "BOSS\t";
				break;
			case RoomTypes::CURSE:
				cout << "COURSE\t";
				break;
			case RoomTypes::ITEM:
				cout << "ITEM\t";
				break;
			case RoomTypes::NORMAL:
				cout << "NORMAL\t";
				break;
			case RoomTypes::PRIVATE:
				cout << "PRIVATE\t";
				break;
			case RoomTypes::SATAN:
				cout << "SATAN\t";
				break;
			case RoomTypes::START:
				cout << "START\t";
				break;
			case RoomTypes::NONE:
				cout << "NONE\t";
				break;
			default:
				cout << "####\t";
			}
		}
		cout << "\n";
	}
	cout << "\n";
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

	return S_OK;
}

void Stage01Scene::Release()
{
	SAFE_RELEASE(door);
	SAFE_RELEASE(player);
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
	//// 문이 닫혀 있거나 잠겨 있을 때, 플레이어는 통과하지 못함
	//for (size_t i = 0; i < doorInfo.size(); ++i)
	//{
	//	for (size_t j = 0; j < doorInfo[i].size(); ++j)
	//	{
	//		for (int k = 0; k < 4; ++k)
	//		{
	//			POINTFLOAT	buffPlayerBodyPos = player->GetPlayerBodyPos();
	//			RECT		buffPlayerBodyShape = player->GetPlayerBodyShape();
	//			POINTFLOAT	buffPlayerHeadPos = player->GetPlayerHeadPos();
	//			RECT		buffPlayerHeadShape = player->GetPlayerHeadShape();
	//			if (IntersectRect(&colliderRect, &buffPlayerHeadShape, &doorInfo[i][j][k].shape) || IntersectRect(&colliderRect, &buffPlayerBodyShape, &doorInfo[i][j][k].shape))
	//			{
	//				if (doorInfo[i][j][k].doorState != DoorStates::OPENED || doorInfo[i][j][k].img == nullptr)
	//				{
	//					player->SetPlayerBodyPos(buffPlayerBodyPos);
	//					player->SetPlayerBodyShape(buffPlayerBodyShape);
	//					player->SetPlayerHeadPos(buffPlayerHeadPos);
	//					player->SetPlayerHeadShape(buffPlayerHeadShape);
	//				}
	//			}
	//		}
	//	}
	//}
	//// OPENED 상태일 때 player가 접촉하면 다음 맵으로 이동
	//// 상
	//if (doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][0].doorState == DoorStates::OPENED && doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][0].img != nullptr)
	//{
	//	int row = door->GetLocatedRow();
	//	--stageRow;
	//	if (stageRow < 0)
	//	{
	//		stageRow = 0;
	//	}
	//	LoadMap();
	//	door->SetLocatedRow(--row);
	//}
	//// 하
	//if (doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][1].doorState == DoorStates::OPENED && doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][1].img != nullptr)
	//{
	//	int row = door->GetLocatedRow();
	//	++stageRow;
	//	if (stageRow >= _stageSize)
	//	{
	//		stageRow = _stageSize - 1;
	//	}
	//	LoadMap();
	//	door->SetLocatedRow(++row);
	//}
	//// 좌
	//if (doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][2].doorState == DoorStates::OPENED && doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][2].img != nullptr)
	//{
	//	int column = door->GetLocatedColumn();
	//	--stageColumn;
	//	if (stageColumn < 0)
	//	{
	//		stageColumn = 0;
	//	}
	//	LoadMap();
	//	door->SetLocatedRow(--column);
	//}
	//// 우
	//if (doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][3].doorState == DoorStates::OPENED && doorInfo[door->GetLocatedRow()][door->GetLocatedColumn()][3].img != nullptr)
	//{
	//	int column = door->GetLocatedColumn();
	//	++stageColumn;
	//	if (stageColumn >= _stageSize)
	//	{
	//		stageColumn = _stageSize - 1;
	//	}
	//	LoadMap();
	//	door->SetLocatedRow(++column);
	//}

	player->Update();
	door->Update();
}

void Stage01Scene::Render(HDC hdc)
{
	TileRender(hdc);
	door->Render(hdc);
	player->Render(hdc);
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
