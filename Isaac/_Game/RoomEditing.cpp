#include "MainConfig.h"
#include "RoomEditing.h"

#include "MapEditing.h"

void RoomEditing::Release()
{
	SAFE_RELEASE(stage);
}

void RoomEditing::DeclareRoomName(int row, int column)
{
	if (stageIndex[row][column].substr(5, 1) == "B")
	{
		roomInfo[row][column] = RoomTypes::NORMAL;
	}
	if (stageIndex[row][column].substr(5, 1) == "C")
	{
		if (stageIndex[row][column].substr(6, 1) == "A")
		{
			roomInfo[row][column] = RoomTypes::NORMAL;
		}
		if (stageIndex[row][column].substr(6, 1) == "E")
		{
			roomInfo[row][column] = RoomTypes::PRIVATE;
		}
	}
	if (stageIndex[row][column].substr(5, 1) == "D")
	{
		if (stageIndex[row][column].substr(11, 1) == "0")
		{
			roomInfo[row][column] = RoomTypes::CURSE;
		}
		if (stageIndex[row][column].substr(11, 1) == "1")
		{
			roomInfo[row][column] = RoomTypes::SATAN;
		}
	}
	if(stageIndex[row][column].empty())
	{
		roomInfo[row][column] = RoomTypes::NONE;
	}
}

void RoomEditing::DeginateBossRoom()
{
	// Stage01을 순회하면서 "Save/BASEMENT01.map"인 Tilemap을 Boss Room으로 지정
	for (size_t i = 0; i < stageIndex.size(); ++i)
	{
		for (size_t j = 0; j < stageIndex[i].size(); ++j)
		{
			if (stageIndex[i][j] == "Save/BASEMENT01.map" || stageIndex[i][j] == "Save/CAVE01.map")
			{
				roomInfo[i][j] = RoomTypes::BOSS;
				break;
			}
		}
	}
}

void RoomEditing::DeginateItemRoom(int row, int column)
{
	const int randRow = row;
	const int randColumn = column;
	// RoomTypes::NORMAL 중 랜덤으로 지정
	// 1. NORMAL이 아닐 시 함수를 다시 호출해 랜덤 생성
	if (roomInfo[randRow][randColumn] != RoomTypes::NORMAL || roomInfo[randRow][randColumn] == RoomTypes::BOSS)
	{
		// 램덤수 생성
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
		return;
	}
	const int topRow = randRow - 1;
	const int bottomRow = randRow + 1;
	const int leftColumn = randColumn - 1;
	const int rightColumn = randColumn + 1;
	// 2. 지정한 방 주위에 특정 방이 있으면 함수를 다시 호출해 랜덤 생성
	// 상
	if (topRow >= 0)
	{
		if (roomInfo[topRow][randColumn] != RoomTypes::NORMAL)
		{
			// 램덤수 생성
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// 하
	if (bottomRow < _stageSize)
	{
		if (roomInfo[bottomRow][randColumn] != RoomTypes::NORMAL)
		{
			// 램덤수 생성
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// 좌
	if (leftColumn >= 0)
	{
		if (roomInfo[randRow][leftColumn] != RoomTypes::NORMAL)
		{
			// 램덤수 생성
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// 우
	if (rightColumn < _stageSize)
	{
		if (roomInfo[randRow][rightColumn] != RoomTypes::NORMAL)
		{
			// 램덤수 생성
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}

	// NORMAL중 BOSS맵이 아닐일 시 그 맵의 RoomType을 ItemRoom으로 설정
	roomInfo[randRow][randColumn] = RoomTypes::ITEM;
}

void RoomEditing::NamingRoom(int row, int column)
{
	int searchRow = row;
	int searchColumn = column;
	// 스택 오버 경고 때문에 정의
	int topRow = searchRow - 1;
	int bottomRow = searchRow + 1;
	int leftColumn = searchColumn - 1;
	int rightColumn = searchColumn + 1;
	// 위쪽 맵 자리가 비어있지 않으면 (stage01[-1(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (topRow >= 0 && stageIndex[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		DeclareRoomName(topRow, searchColumn);				// Naming 하기
		isTransitMap[topRow][searchColumn] = true;			// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 아래쪽 맵 자리가 비어있지 않으면 (stage01[mapSize(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (bottomRow < _stageSize && stageIndex[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		DeclareRoomName(bottomRow, searchColumn);			// Naming 하기
		isTransitMap[bottomRow][searchColumn] = true;		// 통과 = true
		NamingRoom(bottomRow, searchColumn);
	}
	// 왼쪽 맵 자리가 비어있지 않으면 (stage01[N][-1(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (leftColumn >= 0 && stageIndex[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		DeclareRoomName(searchRow, leftColumn);				// Naming 하기
		isTransitMap[searchRow][leftColumn] = true;			// 통과 = true
		NamingRoom(searchRow, leftColumn);
	}
	// 오른쪽 맵 자리가 비어있지 않으면 (stage01[N][mapSize(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (rightColumn < _stageSize && stageIndex[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		DeclareRoomName(searchRow, rightColumn);			// Naming 하기
		isTransitMap[searchRow][rightColumn] = true;		// 통과 = true
		NamingRoom(searchRow, rightColumn);
	}
}

void RoomEditing::Init(int stageNum)
{
	stage = new MapEditing;
	stage->Init(stageNum);
	// Stage01의 Size를 받기
	_stageSize = stage->GetStageSize();
	// StartPoint를 받기
	_startPoint = stage->GetStartPoint();
	// Stage Size만큼 resize하고
	stageIndex.resize(_stageSize);
	for (size_t i = 0; i < stageIndex.size(); ++i)
	{
		stageIndex[i].resize(_stageSize);
		for (size_t j = 0; j < stageIndex[i].size(); ++j)
		{
			// Stage 정보를 받아오기
			stageIndex[i][j] = stage->GetStage()[i][j];
		}
	}
	// Room의 정보를 담기 위한 Stage Size 정하기
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			roomInfo[i][j] = RoomTypes::NONE;
		}
	}
	// Start 지점을 선언
	roomInfo[_startPoint][_startPoint] = RoomTypes::START;
	// 통과했는지의 여부를 알기 위해 vector<vector<bool>> 생성
	isTransitMap.resize(_stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(_stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}
	// Start지점은 true
	isTransitMap[_startPoint][_startPoint] = true;
	// 각 Tilemap들을 경유하며 RoomType으로 Naming
	NamingRoom(_startPoint, _startPoint);
	// BASEMENT01.map인 Tilemap을 BOSS ROOM으로 지정
	DeginateBossRoom();
	// ItemRoom 지정
	// 1. 램덤수 생성
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	// 2. 함수를 통해 ItemRoom 지정
	DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
#ifdef _DEBUG RoomInfo
	cout << "RoomInfo\n";
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
}
