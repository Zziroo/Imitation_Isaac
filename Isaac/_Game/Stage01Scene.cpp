#include "MainConfig.h"
#include "Stage01Scene.h"

#include "DoorEditing.h"
#include "Image.h"
#include "Minimap.h"
#include "Obstacle.h"
#include "Player.h"

using namespace std;

HRESULT Stage01Scene::Init()
{
	// Initialize Map Image
	switch (stageNum)
	{
	case 0:
		// Tilemap Image
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		break;
	case 1:
		// Tilemap Image
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
		break;
	}
	// StartPoint Infomation Image
	infomationStartImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Info.bmp");

	// Door
	door = new DoorEditing;
	door->Init(stageNum);

	// Stage01의 Size를 받기
	stageSize = door->GetStageSize();

	// Start Point를 받기
	startPoint = door->GetStartPoint();
	currColumn = startPoint;
	currRow = startPoint;

	// Stage Size만큼 resize하고
	stageIndex.resize(stageSize);
	for (size_t i = 0; i < stageIndex.size(); ++i)
	{
		stageIndex[i].resize(stageSize);
		for (size_t j = 0; j < stageIndex[i].size(); ++j)
		{
			// Stage 정보를 받아오기
			stageIndex[i][j] = door->GetStage()[i][j];
		}
	}

	// Room Size만큼 resize하고
	roomInfo.resize(stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			roomInfo[i][j] = door->GetRoomType()[i][j];
		}
	}

	// DOOR_INFO 를 저장
	doorInfo.resize(stageSize);
	for (size_t i = 0; i < doorInfo.size(); ++i)
	{
		doorInfo[i].resize(stageSize);
		for (size_t j = 0; j < doorInfo[i].size(); ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				doorInfo[i][j][k] = door->GetDoorInfo()[i][j][k];
			}
		}
	}

	// Load Map
	LoadMap(stageIndex[startPoint][startPoint]);

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
	player->SetStageSize(stageSize);
	player->Init();

	// Minimap
	minimap = new Minimap;
	minimap->SetRoomInfo(&roomInfo);
	minimap->SetStageSize(stageSize);
	minimap->SetStartPointRow(currRow);
	minimap->SetStartPointColumn(currColumn);
	minimap->Init();

	// Obstacle
	obstacleFileInfo.resize(stageSize);
	for (size_t i = 0; i < obstacleFileInfo.size(); ++i)
	{
		obstacleFileInfo[i].resize(stageSize);
		for (size_t j = 0; j < obstacleFileInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::CURSE)
			{
				// string 저장
				NamingObstacleInfo(i, j, "CURSE", 0);
			}
			if (roomInfo[i][j] == RoomTypes::ITEM)
			{
				// string 저장
				NamingObstacleInfo(i, j, "ITEM", 1);
			}
			if (roomInfo[i][j] == RoomTypes::NORMAL)
			{
				// string 저장
				NamingObstacleInfo(i, j, "NORMAL", 2);
			}
		}
	}

	// 저장되어있는 파일을 Load할 벡터의 Size 초기화
	storeObstacle.resize(roomTypeCount);

	// Stage에 Obstacle 생성
	obstacle.resize(stageSize);
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		obstacle[i].resize(stageSize);
		for (size_t j = 0; j < obstacle[i].size(); ++j)
		{
			// 문제 발생! ! => 현재 파일 안의 정보가 이상해 pos, type값을 정확히 가져오지 못한다.
			LoadObstacle(i, j, obstacleFileInfo[i][j].index, obstacleFileInfo[i][j].count);
		}
	}

#ifdef _DEBUG ObstacleCount
	cout << "obstacleFileInfo.index\n";
	for (size_t i = 0; i < obstacleFileInfo.size(); ++i)
	{
		for (size_t j = 0; j < obstacleFileInfo[i].size(); ++j)
		{
			cout << obstacleFileInfo[i][j].index << "\t";

			if (obstacleFileInfo[i][j].index == "")
			{
				cout << "########\t";
			}
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "obstacleFileInfo.count\n";
	for (size_t i = 0; i < obstacleFileInfo.size(); ++i)
	{
		for (size_t j = 0; j < obstacleFileInfo[i].size(); ++j)
		{
			cout << obstacleFileInfo[i][j].count << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
#endif

	return S_OK;
}

void Stage01Scene::Release()
{
	SAFE_RELEASE(door);
	SAFE_RELEASE(minimap);
	SAFE_RELEASE(player);

	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		for (size_t j = 0; j < obstacle[i].size(); ++j)
		{
			for (size_t k = 0; k < obstacle[i][j].size(); ++k)
			{
				SAFE_RELEASE(obstacle[i][j][k]);
			}
		}
	}
}

void Stage01Scene::Update()
{
#ifdef _DEBUG
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
		SelectMapImage();
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		if (doorInfo[currRow][currColumn][1].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][1].img != nullptr)
		{
			++currRow;
			if (currRow >= stageSize)
			{
				currRow = stageSize - 1;
			}
		}
		SelectMapImage();
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
		SelectMapImage();
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		if (doorInfo[currRow][currColumn][3].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][3].img != nullptr)
		{
			++currColumn;
			if (currColumn >= stageSize)
			{
				currColumn = stageSize - 1;
			}
		}
		SelectMapImage();
	}
#endif

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
		SelectMapImage();
		player->SetEnterNextUpDoor(false);
	}
	if (player->GetEnterNextDoor()[1])
	{
		// 하
		if (doorInfo[currRow][currColumn][1].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][1].img != nullptr)
		{
			++currRow;
			if (currRow >= stageSize)
			{
				currRow = stageSize - 1;
			}
		}
		SelectMapImage();
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
		SelectMapImage();
		player->SetEnterNextLeftDoor(false);
	}
	if (player->GetEnterNextDoor()[3])
	{
		// 우
		if (doorInfo[currRow][currColumn][3].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][3].img != nullptr)
		{
			++currColumn;
			if (currColumn >= stageSize)
			{
				currColumn = stageSize - 1;
			}
		}
		SelectMapImage();
		player->SetEnterNextRightDoor(false);
	}

	// Obstacle Update
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		for (size_t j = 0; j < obstacle[i].size(); ++j)
		{
			for (int k = 0; k < obstacleFileInfo[i][j].count; ++k)
			{
				obstacle[i][j][k]->Update();
			}
		}
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
	// Map Render
	TileRender(hdc);

	// Start Map에 Image Render
	if (currRow == startPoint && currColumn == startPoint)
	{
		infomationStartImg->Render(hdc, (INT)(WIN_SIZE_X * DEVIDE_HALF), (INT)(WIN_SIZE_Y * DEVIDE_HALF));
	}

	// Obstacle Render
	for (int i = 0; i < obstacleFileInfo[currRow][currColumn].count; ++i)
	{
		obstacle[currRow][currColumn][i]->Render(hdc);
	}

	// Door Render
	door->Render(hdc);

	// Player Render
	player->Render(hdc);

	// Minimap Render
	minimap->Render(hdc);
}

void Stage01Scene::LoadMap(string loadTilemapFileName)
{
	HANDLE hFile = CreateFile(loadTilemapFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

void Stage01Scene::LoadObstacle(int row, int column, string loadObstacleFileName, int obstacleCount)
{
	if (loadObstacleFileName == "")
	{
		return;
	}

	string loadFileName = loadObstacleFileName;

	HANDLE hFile = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << GetLastError();
	}

	DWORD mapLoadFileInfo = sizeof(tagStoreSampleInfo) * obstacleCount;

	DWORD readByte = 0;

	if (loadFileName.substr(5, 1) == "C")
	{
		storeObstacle[0].resize(obstacleCount);
		if(ReadFile(hFile, &storeObstacle[0], mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "storeObstacle[0] 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
	}
	if (loadFileName.substr(5, 1) == "I")
	{
		storeObstacle[1].resize(obstacleCount);
		if (ReadFile(hFile, &storeObstacle[1], mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "storeObstacle[1] 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
	}
	if (loadFileName.substr(5, 1) == "N")
	{
		storeObstacle[2].resize(obstacleCount);
		if (ReadFile(hFile, &storeObstacle[2], mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(g_hWnd, "storeObstacle[2] 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
	}

	obstacle[row][column].resize(obstacleCount);

	if (loadFileName.substr(5, 1) == "C")
	{
		for (size_t i = 0; i < obstacle[row][column].size(); ++i)
		{
			obstacle[row][column][i] = new Obstacle;
			obstacle[row][column][i]->SetObstaclePos(storeObstacle[0][i].pos);
			obstacle[row][column][i]->SetObstacleType(storeObstacle[0][i].sampleType);
			obstacle[row][column][i]->Init();
		}

		storeObstacle[0].clear();
	}
	if (loadFileName.substr(5, 1) == "I")
	{
		for (size_t i = 0; i < obstacle[row][column].size(); ++i)
		{
			obstacle[row][column][i] = new Obstacle;
			obstacle[row][column][i]->SetObstaclePos(storeObstacle[1][i].pos);
			obstacle[row][column][i]->SetObstacleType(storeObstacle[1][i].sampleType);
			obstacle[row][column][i]->Init();
		}

		storeObstacle[1].clear();
	}
	if (loadFileName.substr(5, 1) == "N")
	{
		for (size_t i = 0; i < obstacle[row][column].size(); ++i)
		{
			obstacle[row][column][i] = new Obstacle;
			obstacle[row][column][i]->SetObstaclePos(storeObstacle[2][i].pos);
			obstacle[row][column][i]->SetObstacleType(storeObstacle[2][i].sampleType);
			obstacle[row][column][i]->Init();
		}

		storeObstacle[2].clear();
	}
}

void Stage01Scene::NamingObstacleInfo(int row, int column, string loadObstacleFileName, int obstacleIndex)
{

	string fileName = "Save/";

	fileName += loadObstacleFileName;
	// .obstacle 랜덤 설정
	int index = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	index = dis(gen) % obstacleMaxIndex[obstacleIndex];

	if (index < 10)
	{
		fileName += "0";
	}

	fileName += to_string(index) + "_";

	int count = 0;

	switch (obstacleIndex)
	{
	case 0:
		switch (index)
		{
		case 0:
			count = 1;
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (index)
		{
		case 0:
			count = 1;
			break;
		case 1: case 2:
			count = 3;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (index)
		{
		case 9: case 12:
			count = 2;
			break;
		case 0: case 1: case 2: case 5: case 6: case 7: case 8: case 10: case 11:
			count = 4;
			break;
		case 14:
			count = 6;
			break;
		case 13:
			count = 8;
			break;
		case 3:
			count = 19;
			break;
		case 4:
			count = 20;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (count < 10)
	{
		fileName += "0";
	}

	fileName += to_string(count) + ".obstacle";

	obstacleFileInfo[row][column].index = fileName;
	obstacleFileInfo[row][column].count = count;
}

void Stage01Scene::SelectMapImage()
{
	// Stage01Index가 비어있으면 가면 안됨.
	if (stageIndex[currRow][currColumn].empty() == false)
	{
		// SampleTileType 속성을 바꿔줘야함
		if (stageIndex[currRow][currColumn].substr(5, 1) == "B")
		{
			sampleTileType = SampleTileTypes::BASEMENT;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		}
		if (stageIndex[currRow][currColumn].substr(5, 1) == "C")
		{
			if (stageIndex[currRow][currColumn].substr(6, 1) == "A")
			{
				sampleTileType = SampleTileTypes::CAVE;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
			}
			if (stageIndex[currRow][currColumn].substr(6, 1) == "E")
			{
				sampleTileType = SampleTileTypes::CELLAR;
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");		// 문제 발생 => CELLAR00.map Load()시 readByte = 0 이 돼버림.
			}
		}
		if (stageIndex[currRow][currColumn].substr(5, 1) == "D")
		{
			sampleTileType = SampleTileTypes::DEPTH;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");			// 문제 발생 => DEPTH00.map Load()시 readByte = 0 이 돼버림.
		}
		// Load
		LoadMap(stageIndex[currRow][currColumn]);
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
