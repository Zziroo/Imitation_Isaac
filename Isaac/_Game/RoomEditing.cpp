#include "MainConfig.h"
#include "RoomEditing.h"

#include "MapEditing.h"

void RoomEditing::Init()
{
	stage01 = new MapEditing;
	stage01->Init();
	// Stage01의 Size를 받기
	_stageSize = stage01->GetStageSize();
	// StartPoint를 받기
	_startPoint = stage01->GetStartPoint();
	// Stage Size만큼 resize하기
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
#ifdef _DEBUG Stage01Index
	// 맵의 정보를 콘솔창에 보여줌
	cout << "RoomEditing\n";
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
#endif
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
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			switch (roomInfo[i][j])
			{
			case RoomTypes::BOSS:
				cout << "BOSS\t";
				break;
			case RoomTypes::COURSE:
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
			default:
				cout << "####\t";
			}
		}
		cout << "\n";
	}
#endif
}

void RoomEditing::Release()
{
	SAFE_RELEASE(stage01);
}

void RoomEditing::DeclareRoomName(int row, int column)
{
	if (stage01Index[row][column].substr(5, 1) == "B")
	{
		roomInfo[row][column] = RoomTypes::NORMAL;
	}
	if (stage01Index[row][column].substr(5, 1) == "C")
	{
		if (stage01Index[row][column].substr(6, 1) == "A")
		{
			roomInfo[row][column] = RoomTypes::NORMAL;
		}
		if (stage01Index[row][column].substr(6, 1) == "E")
		{
			roomInfo[row][column] = RoomTypes::PRIVATE;
		}
	}
	if (stage01Index[row][column].substr(5, 1) == "D")
	{
		if (stage01Index[row][column].substr(11, 1) == "0")
		{
			roomInfo[row][column] = RoomTypes::COURSE;
		}
		if (stage01Index[row][column].substr(11, 1) == "1")
		{
			roomInfo[row][column] = RoomTypes::SATAN;
		}
	}
}

void RoomEditing::DeginateBossRoom()
{
	// Stage01을 순회하면서 "Save/BASEMENT01.map"인 Tilemap을 Boss Room으로 지정
	for (size_t i = 0; i < stage01Index.size(); ++i)
	{
		for (size_t j = 0; j < stage01Index[i].size(); ++j)
		{
			if (stage01Index[i][j] == "Save/BASEMENT01.map")
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
	// 2. NORMAL일 시 그 맵의 RoomType을 ItemRoom으로 설정
	roomInfo[randRow][randColumn] = RoomTypes::ITEM;
}

void RoomEditing::NamingRoom(int row, int column)
{
#ifdef _DEBUG via Tilemap
	cout << stage01Index[row][column] << "\n";
#endif
	int searchRow = row;
	int searchColumn = column;
	// 스택 오버 경고 때문에 정의
	int topRow = searchRow - 1;
	int bottomRow = searchRow + 1;
	int leftColumn = searchColumn - 1;
	int rightColumn = searchColumn + 1;
	// 위쪽 맵 자리가 비어있지 않으면 (stage01[-1(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (topRow >= 0 && stage01Index[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		DeclareRoomName(topRow, searchColumn);				// Naming 하기
		isTransitMap[topRow][searchColumn] = true;			// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 아래쪽 맵 자리가 비어있지 않으면 (stage01[mapSize(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (bottomRow < _stageSize && stage01Index[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		DeclareRoomName(bottomRow, searchColumn);			// Naming 하기
		isTransitMap[bottomRow][searchColumn] = true;		// 통과 = true
		NamingRoom(bottomRow, searchColumn);
	}
	// 왼쪽 맵 자리가 비어있지 않으면 (stage01[N][-1(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (leftColumn >= 0 && stage01Index[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		DeclareRoomName(searchRow, leftColumn);				// Naming 하기
		isTransitMap[searchRow][leftColumn] = true;			// 통과 = true
		NamingRoom(searchRow, leftColumn);
	}
	// 오른쪽 맵 자리가 비어있지 않으면 (stage01[N][mapSize(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (rightColumn < _stageSize && stage01Index[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		DeclareRoomName(searchRow, rightColumn);			// Naming 하기
		isTransitMap[searchRow][rightColumn] = true;		// 통과 = true
		NamingRoom(searchRow, rightColumn);
	}
}
