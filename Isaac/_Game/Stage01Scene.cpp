#include "stdafx.h"
#include "Stage01Scene.h"

#include "DoorEditing.h"
#include "Image.h"
#include "Minimap.h"
#include "NormalMonster.h"
#include "Obstacle.h"
#include "Player.h"
#include "PlayerTear.h"

using namespace std;

HRESULT Stage01Scene::Init()
{
	// Initialize Map Image
	switch (stageNum)
	{
	case 0:
		// TileType
		sampleTileType = SampleTileTypes::BASEMENT;
		// Tilemap Image
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Basement.bmp");
		break;
	case 1:
		// TileType
		sampleTileType = SampleTileTypes::CAVE;
		// Tilemap Image
		drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cave.bmp");
		break;
	}
	// StartPoint Infomation Image
	infomationStartImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Info.bmp");

	// Door
	door = new DoorEditing;
	door->Init(stageNum);

	// Stage01�� Size�� �ޱ�
	stageSize = door->GetStageSize();

	// Start Point�� �ޱ�
	startPoint = door->GetStartPoint();
	currColumn = startPoint;
	currRow = startPoint;

	// Stage Size��ŭ resize�ϰ�
	stageIndex.resize(stageSize);
	for (size_t i = 0; i < stageIndex.size(); ++i)
	{
		stageIndex[i].resize(stageSize);
		for (size_t j = 0; j < stageIndex[i].size(); ++j)
		{
			// Stage ������ �޾ƿ���
			stageIndex[i][j] = door->GetStage()[i][j];
		}
	}

	// Room Size��ŭ resize�ϰ�
	roomInfo.resize(stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			roomInfo[i][j] = door->GetRoomType()[i][j];
		}
	}

	// DOOR_INFO �� ����
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

	// Obstacle
	obstacleFileInfo.resize(stageSize);
	for (size_t i = 0; i < obstacleFileInfo.size(); ++i)
	{
		obstacleFileInfo[i].resize(stageSize);
		for (size_t j = 0; j < obstacleFileInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::CURSE)
			{
				// string ����
				NamingObstacleInfo((INT)i, (INT)j, "CURSE", 0);
			}
			if (roomInfo[i][j] == RoomTypes::ITEM)
			{
				// string ����
				NamingObstacleInfo((INT)i, (INT)j, "ITEM", 1);
			}
			if (roomInfo[i][j] == RoomTypes::NORMAL)
			{
				// string ����
				NamingObstacleInfo((INT)i, (INT)j, "NORMAL", 2);
			}
		}
	}

#ifdef _DEBUG ObstacleFileInfo
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

	// ����Ǿ��ִ� ������ Load�� ������ Size �ʱ�ȭ
	storeObstacle.resize(roomTypeCount);

	// Stage�� Obstacle ����
	obstacle.resize(stageSize);
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		obstacle[i].resize(stageSize);
		for (size_t j = 0; j < obstacle[i].size(); ++j)
		{
			LoadObstacle((INT)i, (INT)j, obstacleFileInfo[i][j].index, obstacleFileInfo[i][j].count);
		}
	}

	// NormalMonster
	normalMonsterFileInfo.resize(stageSize);
	for (size_t i = 0; i < normalMonsterFileInfo.size(); ++i)
	{
		normalMonsterFileInfo[i].resize(stageSize);
		for (size_t j = 0; j < normalMonsterFileInfo[i].size(); ++j)
		{
			if (roomInfo[i][j] == RoomTypes::NORMAL)
			{
				NamingNormalMonsterInfo((INT)i, (INT)j);
			}
		}
	}

#ifdef _DEBUG NormalMonsterFileInfo
	cout << "NormalMonsterFileInfo.index\n";
	for (size_t i = 0; i < normalMonsterFileInfo.size(); ++i)
	{
		for (size_t j = 0; j < normalMonsterFileInfo[i].size(); ++j)
		{
			cout << normalMonsterFileInfo[i][j].index << "\t";

			if (normalMonsterFileInfo[i][j].index == "")
			{
				cout << "#########\t";
			}
		}
		cout << "\n";
	}
	cout << "\n";

	cout << "NormalMonsterFileInfo.count\n";
	for (size_t i = 0; i < normalMonsterFileInfo.size(); ++i)
	{
		for (size_t j = 0; j < normalMonsterFileInfo[i].size(); ++j)
		{
			cout << normalMonsterFileInfo[i][j].count << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
#endif

	// Stage�� NormalMonster ����
	normalMonster.resize(stageSize);
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		normalMonster[i].resize(stageSize);
		for (size_t j = 0; j < normalMonster[i].size(); ++j)
		{
			LoadNormalMonster((INT)i, (INT)j, normalMonsterFileInfo[i][j].index, normalMonsterFileInfo[i][j].count);
		}
	}

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

	// PlayerTear
	playerTear = new PlayerTear;
	playerTear->SetObstacleInfo(&obstacle);
	playerTear->SetTileInfo(colliderTileInfo);
	playerTear->Init();

	// Player
	player = new Player;
	player->SetDoorInfo(&doorInfo);
	player->SetNormalMonsterInfo(&normalMonster);
	player->SetObstacleInfo(&obstacle);
	player->SetPlayerTear(playerTear);
	player->SetStageSize(stageSize);
	player->SetTileInfo(colliderTileInfo);
	player->Init();

	// Minimap
	minimap = new Minimap;
	minimap->SetRoomInfo(&roomInfo);
	minimap->SetStageSize(stageSize);
	minimap->SetStartPointColumn(currColumn);
	minimap->SetStartPointRow(currRow);
	minimap->Init();

	return S_OK;
}

void Stage01Scene::Release()
{
	SAFE_RELEASE(door);
	SAFE_RELEASE(minimap);
	SAFE_RELEASE(player);
	SAFE_RELEASE(playerTear);

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

	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		for (size_t j = 0; j < normalMonster[i].size(); ++j)
		{
			for (size_t k = 0; k < normalMonster[i][j].size(); ++k)
			{
				SAFE_RELEASE(normalMonster[i][j][k]);
			}
		}
	}
}

void Stage01Scene::Update()
{
	// Door�� ������ Update
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

	// PlayerTear
	playerTear->SetOwner(player);
	playerTear->SetCurrCloumn(currColumn);
	playerTear->SetCurrRow(currRow);
	playerTear->Update();

	// Player Update
	player->SetCurrCloumn(currColumn);
	player->SetCurrRow(currRow);
	//player->SetDoorInfo(&doorInfo);					// ������Ʈ���� ��� ����� �ϴ���??
	//player->SetObstacleInfo(&obstacle);				// ������Ʈ���� ��� ����� �ϴ���??
	player->Update();

														// ���� ���鼭 ������Ʈ ���Ѿ� �ұ�??											// ���� �߻�! ! => ������ Bonfire�� ������Ʈ�� ���� �ʴ´�.
														//for (int k = 0; k < obstacleFileInfo[currRow][currColumn].count; ++k)
														//{
														//	obstacle[currRow][currColumn][k]->Update();
	// Obstacle Update									//}
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

	// NormalMonster���� Player�� ��ġ ���� ��.
	for (int i = 0; i < normalMonsterFileInfo[currRow][currColumn].count; ++i)
	{
		normalMonster[currRow][currColumn][i]->SetTargetPos(player->GetPlayerBodyPos());
	}

	// NormalMonster Update								// ���� �߻�! ! => ������ Monster�� ������Ʈ�� ���� �ʴ´�.
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		for (size_t j = 0; j < normalMonster[i].size(); ++j)
		{
			for (size_t k = 0; k < normalMonster[i][j].size(); ++k)
			{
				normalMonster[i][j][k]->Update();
			}
		}
	}

	// Map Update
	MoveToNextMap();

	// DoorEditing Update
	door->SetCurrCloumn(currColumn);
	door->SetCurrRow(currRow);
	door->SetNormalMonsterInfo(&normalMonster);
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

	// Start Map�� Image Render
	if (currRow == startPoint && currColumn == startPoint)
	{
		infomationStartImg->Render(hdc, (INT)(WIN_SIZE_X * DEVIDE_HALF), (INT)(WIN_SIZE_Y * DEVIDE_HALF));
	}

	// Obstacle Render
	for (int i = 0; i < obstacleFileInfo[currRow][currColumn].count; ++i)
	{
		obstacle[currRow][currColumn][i]->Render(hdc);
	}

	// NormalMonster Render
	for (int i = 0; i < normalMonsterFileInfo[currRow][currColumn].count; ++i)
	{
		normalMonster[currRow][currColumn][i]->Render(hdc);
	}

	// Door Render
	door->Render(hdc);

	// Tear
	playerTear->Render(hdc);

	// Player Render
	player->Render(hdc);

	// Minimap Render
	minimap->Render(hdc);
}

void Stage01Scene::MoveToNextMap()
{
	if (player->GetEnterNextDoor()[UPPER_DOOR])
	{
		// ��
		if (doorInfo[currRow][currColumn][UPPER_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][UPPER_DOOR].img != nullptr)
		{
			--currRow;
			if (currRow < OUT_OF_STAGE)
			{
				currRow = OUT_OF_STAGE;
			}
		}
		SelectMapImage();
		player->SetEnterNextUpDoor(false);
	}
	if (player->GetEnterNextDoor()[LOWER_DOOR])
	{
		// ��
		if (doorInfo[currRow][currColumn][LOWER_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][LOWER_DOOR].img != nullptr)
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
	if (player->GetEnterNextDoor()[LEFT_DOOR])
	{
		// ��
		if (doorInfo[currRow][currColumn][LEFT_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][LEFT_DOOR].img != nullptr)
		{
			--currColumn;
			if (currColumn < OUT_OF_STAGE)
			{
				currColumn = OUT_OF_STAGE;
			}
		}
		SelectMapImage();
		player->SetEnterNextLeftDoor(false);
	}
	if (player->GetEnterNextDoor()[RIGHT_DOOR])
	{
		// ��
		if (doorInfo[currRow][currColumn][RIGHT_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][RIGHT_DOOR].img != nullptr)
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
	
	#ifdef _DEBUG MoveToNextMap
	if (Input::GetButtonDown(VK_UP))
	{
		if (doorInfo[currRow][currColumn][UPPER_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][UPPER_DOOR].img != nullptr)
		{
			--currRow;
			if (currRow < OUT_OF_STAGE)
			{
				currRow = OUT_OF_STAGE;
			}
		}
		SelectMapImage();
	}
	if (Input::GetButtonDown(VK_DOWN))
	{
		if (doorInfo[currRow][currColumn][LOWER_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][LOWER_DOOR].img != nullptr)
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
		if (doorInfo[currRow][currColumn][LEFT_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][LEFT_DOOR].img != nullptr)
		{
			--currColumn;
			if (currColumn < OUT_OF_STAGE)
			{
				currColumn = OUT_OF_STAGE;
			}
		}
		SelectMapImage();
	}
	if (Input::GetButtonDown(VK_RIGHT))
	{
		if (doorInfo[currRow][currColumn][RIGHT_DOOR].roomType != RoomTypes::NONE || doorInfo[currRow][currColumn][RIGHT_DOOR].img != nullptr)
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
}

void Stage01Scene::NamingNormalMonsterInfo(int row, int column)
{
	string fileName = "Save/MONSTER";
	// .monster ���� ����
	int index = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	index = dis(gen) % normalMonsterMaxIndex;

	if (index < 10)
	{
		fileName += "0";
	}

	fileName += to_string(index) + "_";

	int count = 0;

	switch (index)
	{
	case 3:
		count = 0;
		break;
	case 2:
		count = 3;
		break;
	case 0: case 1:
		count = 6;
		break;
	}

	if (count < 10)
	{
		fileName += "0";
	}

	fileName += to_string(count) + ".monster";

	normalMonsterFileInfo[row][column].index = fileName;
	normalMonsterFileInfo[row][column].count = count;
}

void Stage01Scene::NamingObstacleInfo(int row, int column, string loadObstacleFileName, int obstacleIndex)
{
	string fileName = "Save/";

	fileName += loadObstacleFileName;
	// .obstacle ���� ����
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
		case 16: case 17:
			count = 0;
			break;
		case 12: case 13: case 14:
			count = 1;
			break;
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 9:
			count = 4;
			break;
		case 10: case 15:
			count = 5;
			break;
		case 8:
			count = 20;
			break;
		case 11:
			count = 24;
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
			MessageBox(_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement �� ������ �ε忡 ����! !", "����", MB_OK);
		}
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}

	CloseHandle(hFile);
}

void Stage01Scene::LoadNormalMonster(int row, int column, string loadNormalMonsterFileName, int normalMonsterCount)
{
	if (loadNormalMonsterFileName == "" || normalMonsterCount == 0)
	{
		return;
	}

	string loadFileName = loadNormalMonsterFileName;

	HANDLE hFile = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD mapLoadFileInfo = sizeof(storeNormalMonsterInfo) * normalMonsterCount;

	DWORD readByte = 0;

	storeNormalMonster.resize(normalMonsterCount);
	for (int i = 0; i < normalMonsterCount; ++i)
	{
		if (ReadFile(hFile, &storeNormalMonster[i], sizeof(storeNormalMonsterInfo), &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Normal Monster ������ �ε忡 ����! !", "����", MB_OK);
		}
	}

	normalMonster[row][column].resize(normalMonsterCount);
	for (size_t i = 0; i < normalMonster[row][column].size(); ++i)
	{
		normalMonster[row][column][i] = new NormalMonster;
		normalMonster[row][column][i]->SetNormalMonsterPos(storeNormalMonster[i].pos);
		normalMonster[row][column][i]->SetNormalMonsterType(storeNormalMonster[i].sampleType);
		normalMonster[row][column][i]->Init();
	}

	storeNormalMonster.clear();

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

	DWORD mapLoadFileInfo = sizeof(storeObstacleInfo) * obstacleCount;

	DWORD readByte = 0;

	if (loadFileName.substr(5, 1) == "C")
	{
		storeObstacle[0].resize(obstacleCount);
		for (int i = 0; i < obstacleCount; ++i)
		{
			if (ReadFile(hFile, &storeObstacle[0][i], sizeof(storeObstacleInfo), &readByte, NULL) == false)
			{
				MessageBox(_hWnd, "storeObstacle[0] Obstacle ������ �ε忡 ����! !", "����", MB_OK);
			}
		}
	}
	if (loadFileName.substr(5, 1) == "I")
	{
		storeObstacle[1].resize(obstacleCount);
		for (int i = 0; i < obstacleCount; ++i)
		{
			if (ReadFile(hFile, &storeObstacle[1][i], sizeof(storeObstacleInfo), &readByte, NULL) == false)
			{
				MessageBox(_hWnd, "storeObstacle[1] Obstacle ������ �ε忡 ����! !", "����", MB_OK);
			}
		}
	}
	if (loadFileName.substr(5, 1) == "N")
	{
		storeObstacle[2].resize(obstacleCount);
		for (int i = 0; i < obstacleCount; ++i)
		{
			if (ReadFile(hFile, &storeObstacle[2][i], sizeof(storeObstacleInfo), &readByte, NULL) == false)
			{
				MessageBox(_hWnd, "storeObstacle[2] Obstacle ������ �ε忡 ����! !", "����", MB_OK);
			}
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

	CloseHandle(hFile);
}

void Stage01Scene::SelectMapImage()
{
	// Stage01Index�� ��������� ���� �ȵ�.
	if (stageIndex[currRow][currColumn].empty() == false)
	{
		// SampleTileType �Ӽ��� �ٲ������
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
				drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Cellar.bmp");
			}
		}
		if (stageIndex[currRow][currColumn].substr(5, 1) == "D")
		{
			sampleTileType = SampleTileTypes::DEPTH;
			drawingAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/Tilemap/Tile/Depth.bmp");
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
