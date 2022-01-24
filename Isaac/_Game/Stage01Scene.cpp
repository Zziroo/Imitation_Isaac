#include "stdafx.h"
#include "Stage01Scene.h"

#include "AStar.h"
#include "BossMonster.h"
#include "BossMonsterHP.h"
#include "DoorEditing.h"
#include "Image.h"
#include "Minimap.h"
#include "NextStageDoor.h"
#include "NormalMonster.h"
#include "Obstacle.h"
#include "Player.h"
#include "PlayerHP.h"
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

	// NextStageDoor
	nextStageDoor = new NextStageDoor;
	nextStageDoor->Init();

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

			if (roomInfo[i][j] == RoomTypes::BOSS)
			{
				bossRow = (INT)i;
				bossColumn = (INT)j;
			}
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
				NamingObstacleInfo((INT)i, (INT)j, "CURSE", 0);
			}
			if (roomInfo[i][j] == RoomTypes::ITEM)
			{
				// string 저장
				NamingObstacleInfo((INT)i, (INT)j, "ITEM", 1);
			}
			if (roomInfo[i][j] == RoomTypes::NORMAL)
			{
				// string 저장
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

	// 저장되어있는 파일을 Load할 벡터의 Size 초기화
	storeObstacle.resize(roomTypeCount);

	// Stage에 Obstacle 생성
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

	// Stage에 NormalMonster 생성
	normalMonster.resize(stageSize);
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		normalMonster[i].resize(stageSize);
		for (size_t j = 0; j < normalMonster[i].size(); ++j)
		{
			LoadNormalMonster((INT)i, (INT)j, normalMonsterFileInfo[i][j].index, normalMonsterFileInfo[i][j].count);
		}
	}

	// AStar
	normalMonsterAStar.resize(stageSize);
	for (size_t i = 0; i < normalMonsterAStar.size(); ++i)
	{
		normalMonsterAStar[i].resize(stageSize);
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

	//BossMonster
	bossMonster = new BossMonster;
	bossMonster->Init();

	// BossMonsterHP
	bossMonsterHP = new BossMonsterHP;
	bossMonsterHP->Init();

	// PlayerTear
	playerTear = new PlayerTear;
	playerTear->SetBossMonster(bossMonster);
	playerTear->SetNormalMonsterInfo(&normalMonster);
	playerTear->SetObstacleInfo(&obstacle);
	playerTear->SetTileInfo(colliderTileInfo);
	playerTear->Init();

	// Player
	player = new Player;
	player->SetBossColumn(bossColumn);
	player->SetBossMonster(bossMonster);
	player->SetBossRow(bossRow);
	player->SetCurrCloumn(currColumn);
	player->SetCurrRow(currRow);
	player->SetDoorInfo(&doorInfo);
	player->SetNextStageDoor(nextStageDoor);
	player->SetNormalMonsterInfo(&normalMonster);
	player->SetObstacleInfo(&obstacle);
	player->SetPlayerTear(playerTear);
	player->SetStageSize(stageSize);
	player->SetTileInfo(colliderTileInfo);
	player->Init();

	// PlayerUI
	playerHP = new PlayerHP;
	playerHP->SetPlayerHP(player->GetPlayerHP());
	playerHP->Init();

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
	SAFE_RELEASE(bossMonster);
	SAFE_RELEASE(bossMonsterAStar);
	SAFE_RELEASE(bossMonsterHP);
	SAFE_RELEASE(door);
	SAFE_RELEASE(minimap);
	SAFE_RELEASE(nextStageDoor);
	SAFE_RELEASE(player);
	SAFE_RELEASE(playerHP);
	SAFE_RELEASE(playerTear);

	for (size_t i = 0; i < normalMonsterAStar.size(); ++i)
	{
		for (size_t j = 0; j < normalMonsterAStar[i].size(); ++j)
		{
			for (size_t k = 0; k < normalMonsterAStar[i][j].size(); ++k)
			{
				SAFE_RELEASE(normalMonsterAStar[i][j][k]);
			}
		}
	}
	normalMonsterAStar.clear();

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
	normalMonster.clear();

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
	obstacle.clear();
}

void Stage01Scene::Update()
{
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

	// PlayerTear
	playerTear->SetPlayer(player);
	playerTear->SetCurrCloumn(currColumn);
	playerTear->SetCurrRow(currRow);
	playerTear->Update();

	if (currColumn == bossColumn && currRow == bossRow)
	{
		playerTear->CollideWithBossMonster();
	}

	// Player Update
	player->SetCurrCloumn(currColumn);
	player->SetCurrRow(currRow);
	player->Update();

	// Stage 클리어
	if ((currColumn == bossColumn && currRow == bossRow) && player->GetIsGameClear())
	{
		GET_SINGLETON_SCENE->ChangeScene("Title");
		return;
	}

	// PlayerUI Update
	playerHP->SetPlayerHP(player->GetPlayerHP());
	playerHP->Update();

	// Map Update
	MoveToNextMap();

	// 만약 AStar size != 0 이라면 삭제
	if (normalMonsterAStar[currRow][currColumn].empty() == false)
	{
		for (size_t i = 0; i < normalMonsterAStar[currRow][currColumn].size(); ++i)
		{
			SAFE_RELEASE(normalMonsterAStar[currRow][currColumn][i]);
		}

		normalMonsterAStar[currRow][currColumn].clear();
	}

	SAFE_RELEASE(bossMonsterAStar);

	// NormalMonster count 만큼 생성
	normalMonsterAStar[currRow][currColumn].resize(normalMonster[currRow][currColumn].size());
	for (size_t i = 0; i < normalMonsterAStar[currRow][currColumn].size(); ++i)
	{
		normalMonsterAStar[currRow][currColumn][i] = new AStar;
	}

	// BossMonsterAStar
	bossMonsterAStar = new AStar;

	// NormalMonsterAStar TargetPos 설정
	for (size_t i = 0; i < normalMonsterAStar[currRow][currColumn].size(); ++i)
	{
		normalMonsterAStar[currRow][currColumn][i]->SetTargetPosX((FLOAT)player->GetPos().x);
		normalMonsterAStar[currRow][currColumn][i]->SetTargetPosY((FLOAT)player->GetPos().y);
	}

	if (currColumn == bossColumn && currRow == bossRow)
	{
		// BossMonsterAStar TargetPos 설정
		bossMonsterAStar->SetTargetPosX((FLOAT)player->GetPos().x);
		bossMonsterAStar->SetTargetPosY((FLOAT)player->GetPos().y);
	}

	// Obstacle Update
	for (size_t i = 0; i < obstacle[currRow][currColumn].size(); ++i)
	{
		obstacle[currRow][currColumn][i]->Update();
	}
	
	for (size_t i = 0; i < normalMonster[currRow][currColumn].size(); ++i)
	{
		// NormalMonsterAStar StartPos 설정
		normalMonsterAStar[currRow][currColumn][i]->SetStartPosX((FLOAT)normalMonster[currRow][currColumn][i]->GetNormalMonsterPosX());
		normalMonsterAStar[currRow][currColumn][i]->SetStartPosY((FLOAT)normalMonster[currRow][currColumn][i]->GetNormalMonsterPosY());
	}

	if (currColumn == bossColumn && currRow == bossRow)
	{
		// BossMonsterAStar StartPos 설정
		bossMonsterAStar->SetStartPosX((FLOAT)bossMonster->GetPos().x);
		bossMonsterAStar->SetStartPosY((FLOAT)bossMonster->GetPos().y);
	}

	// NormalMonsterAStar Update
	if (normalMonster[currRow][currColumn].empty() == false)
	{
		for (size_t i = 0; i < normalMonsterAStar[currRow][currColumn].size(); ++i)
		{
			normalMonsterAStar[currRow][currColumn][i]->Init();
			normalMonsterAStar[currRow][currColumn][i]->Update();
		}
	}

	// NormalMonster Update
	for (size_t i = 0; i < normalMonster[currRow][currColumn].size(); ++i)
	{
		normalMonster[currRow][currColumn][i]->SetNormalMonsterAStar(normalMonsterAStar[currRow][currColumn][i]);
		normalMonster[currRow][currColumn][i]->SetNormalMonsterPathWay(normalMonsterAStar[currRow][currColumn][i]->GetPathWay());
		normalMonster[currRow][currColumn][i]->SetNormalMonsterState(MonsterStates::MOVE);
		normalMonster[currRow][currColumn][i]->SetPlayer(player);
		normalMonster[currRow][currColumn][i]->Update();
	}

	if (currColumn == bossColumn && currRow == bossRow)
	{
		// BossMonsterAStar Update
		bossMonsterAStar->Init();
		bossMonsterAStar->Update();

		// BossMonster Update
		bossMonster->SetBossMonsterAStar(bossMonsterAStar);
		bossMonster->SetBossMonsterPathWay(bossMonsterAStar->GetPathWay());
		bossMonster->SetPlayer(player);
		bossMonster->Update();

		// BossRoom에서 normalMonster 추가 생성
		if (false == bossMonster->GetInitializeNormalMonsterInfo().empty())
		{
			addNormalMonsterIndex[1] += (INT)bossMonster->GetInitializeNormalMonsterInfo().size();

			normalMonster[bossRow][bossColumn].resize(addNormalMonsterIndex[1]);
			for (size_t i = addNormalMonsterIndex[0]; i < normalMonster[bossRow][bossColumn].size(); ++i)
			{
				normalMonster[bossRow][bossColumn][i] = new NormalMonster;
				normalMonster[bossRow][bossColumn][i]->SetNormalMonsterPos(bossMonster->GetInitializeNormalMonsterInfo()[i - addNormalMonsterIndex[0]].pos);
				normalMonster[bossRow][bossColumn][i]->SetNormalMonsterType(bossMonster->GetInitializeNormalMonsterInfo()[i - addNormalMonsterIndex[0]].type);
				normalMonster[bossRow][bossColumn][i]->Init();
			}

			addNormalMonsterIndex[0] = addNormalMonsterIndex[1];

			bossMonster->InitializeNormalMonsterInfo();
		}
	}

	// BossMonsterHP Update
	if ((currColumn == bossColumn && currRow == bossRow) && playerTear->GetAttackedBossMonster())
	{
		bossMonsterHP->SetPlayerAttackValue(player->GetPlayerAttackValue());
		bossMonsterHP->Update();
		playerTear->SetAttackedBossMonster(false);
	}

	if (bossMonsterHP->GetIsGameClear())
	{
		bossMonster->SetBossmonsterState(MonsterStates::DEAD);
	}

	// DoorEditing Update
	door->SetBossColumn(bossColumn);
	door->SetBossRow(bossRow);	
	door->SetCurrCloumn(currColumn);
	door->SetCurrRow(currRow);
	door->SetNormalMonsterInfo(&normalMonster);
	door->SetBossMonster(bossMonster);
	door->Update();

	// Minimap Update
	minimap->SetCurrCloumn(currColumn);
	minimap->SetCurrRow(currRow);
	minimap->Update();

	// PlayerTear와 NormalMonster충돌
	playerTear->CollideWithNormalMonster();

	if ((currColumn == bossColumn && currRow == bossRow) && false == normalMonster[bossRow][bossColumn].empty())
	{
		if (playerTear->GetAttackedNormalMonster())
		{
			--addNormalMonsterIndex[0];
			--addNormalMonsterIndex[1];
			playerTear->SetAttackedNormalMonster(false);
		}
	}

	// BossMonster가 죽었을 때
	if (bossMonsterHP->GetIsGameClear() && normalMonster[bossRow][bossColumn].empty())
	{
		bossMonster->SetIsAlive(false);

		if (openNextStageDoor)
		{
			nextStageDoor->Update();
			nextStageDoor->SetOpenNextStageDoor(true);
		}
	}

	// Player가 죽었을 때
	if (player->GetIsGameOver())
	{
		GET_SINGLETON_SCENE->ChangeScene("Title");
		return;
	}
}

void Stage01Scene::Render(HDC hdc)
{
	// Map Render
	TileRender(hdc);

	// Door Render
	door->Render(hdc);

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

	// NormalMonster Render
	for (size_t i = 0; i < normalMonster[currRow][currColumn].size(); ++i)
	{
		normalMonster[currRow][currColumn][i]->Render(hdc);
	}

	if ((currColumn == bossColumn && currRow == bossRow))
	{
		if (false == bossMonsterHP->GetIsGameClear())
		{
			// BossMonster Render
			bossMonster->Render(hdc);
		}
		else
		{
			if (normalMonster[bossRow][bossColumn].empty())
			{
				// NextStageDoor Render
				nextStageDoor->Render(hdc);

				openNextStageDoor = true;
			}
		}
	}

	// Tear
	playerTear->Render(hdc);

	// Player Render
	player->Render(hdc);

	// PlayerUI Render
	playerHP->Render(hdc);

	if ((currColumn == bossColumn && currRow == bossRow) && bossMonsterHP->GetIsGameClear() == false)
	{
		// BossMonsterHP Render
		bossMonsterHP->Render(hdc);
	}

	// Minimap Render
	minimap->Render(hdc);
}

void Stage01Scene::MoveToNextMap()
{
	if (player->GetEnterNextDoor()[UPPER_DOOR])
	{
		// 상
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
		// 하
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
		// 좌
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
		// 우
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
	// .monster 랜덤 설정
	char	fileName[MAX_PATH];
	int		index = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	index = dis(gen) % normalMonsterMaxIndex;

	int counts[4] = { 6, 6, 3, 0 };

	sprintf_s(fileName, "Save/Monster%02d_%02d.monster", index, counts[index]);

	normalMonsterFileInfo[row][column].index = fileName;
	normalMonsterFileInfo[row][column].count = counts[index];
}

void Stage01Scene::NamingObstacleInfo(int row, int column, const char* loadObstacleFileName, int obstacleIndex)
{
	// .obstacle 랜덤 설정
	char	fileName[MAX_PATH];
	int		index = 0;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	index = dis(gen) % obstacleMaxIndex[obstacleIndex];

	vector<int> counts[3];
	
	counts[0].resize(1);
	counts[0] = { 1 };
	counts[1].resize(3);
	counts[1] = { 1, 3, 3 };
	counts[2].resize(17);
	counts[2] = { 4, 4, 4, 4, 4, 4, 4, 4, 20, 4, 5, 24, 1, 1, 1, 5, 0, 0 };

	sprintf_s(fileName, "Save/%s%02d_%02d.obstacle", loadObstacleFileName, index, counts[obstacleIndex][index]);

	obstacleFileInfo[row][column].index = fileName;
	obstacleFileInfo[row][column].count = counts[obstacleIndex][index];
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
			MessageBox(_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapLoadFileInfo, &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Basement 맵 데이터 로드에 실패! !", "에러", MB_OK);
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
			MessageBox(_hWnd, "Normal Monster 데이터 로드에 실패! !", "에러", MB_OK);
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
				MessageBox(_hWnd, "storeObstacle[0] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
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
				MessageBox(_hWnd, "storeObstacle[1] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
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
				MessageBox(_hWnd, "storeObstacle[2] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
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
