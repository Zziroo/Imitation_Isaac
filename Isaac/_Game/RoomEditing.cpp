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
	// Room의 정보를 담기 위한 Stage Size 정하기
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
	}
	// Start 지점을 선언
	roomInfo[_startPoint][_startPoint] = RoomType::START;
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

	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			switch (roomInfo[i][j])
			{
			case RoomType::BOSS:
				cout << "BOSS\t";
				break;
			case RoomType::COURSE:
				cout << "COURSE\t";
				break;
			case RoomType::ITEM:
				cout << "ITEM\t";
				break;
			case RoomType::NORMAL:
				cout << "NORMAL\t";
				break;
			case RoomType::PRIVATE:
				cout << "PRIVATE\t";
				break;
			case RoomType::SATAN:
				cout << "SATAN\t";
				break;
			case RoomType::START:
				cout << "START\t";
				break;
			default:
				cout << "####\t";
			}
		}
		cout << "\n";
	}
}

void RoomEditing::Release()
{
	SAFE_RELEASE(stage01);
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
	if (topRow >= 0 && stage01Index[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, topRow, searchColumn);		// Naming 하기
		isTransitMap[topRow][searchColumn] = true;							// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 아래쪽 맵 자리가 비어있지 않으면 (stage01[mapSize(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (bottomRow < _stageSize && stage01Index[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, bottomRow, searchColumn);	// Naming 하기
		isTransitMap[bottomRow][searchColumn] = true;						// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 왼쪽 맵 자리가 비어있지 않으면 (stage01[N][-1(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (leftColumn >= 0 && stage01Index[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, searchRow, leftColumn);		// Naming 하기
		isTransitMap[searchRow][leftColumn] = true;							// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 오른쪽 맵 자리가 비어있지 않으면 (stage01[N][mapSize(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (rightColumn < _stageSize && stage01Index[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, searchRow, rightColumn);	// Naming 하기
		isTransitMap[searchRow][rightColumn] = true;						// 통과 = true
		NamingRoom(topRow, searchColumn);
	}
	// 수정 필요!! => Item Room 필수
}

void RoomEditing::DeclareRoomName(vector<vector<string>> stageIndex, vector<vector<RoomType>> _roomInfo, int row, int column)
{
	if (stageIndex[row][column].substr(5, 1) == "B")
	{
		_roomInfo[row][column] = RoomType::NORMAL;
	}
	if (stageIndex[row][column].substr(5, 1) == "C")
	{
		if (stageIndex[row][column].substr(6, 1) == "A")
		{
			_roomInfo[row][column] = RoomType::NORMAL;
		}
		if (stageIndex[row][column].substr(6, 1) == "E")
		{
			_roomInfo[row][column] = RoomType::PRIVATE;
		}
	}
	if (stageIndex[row][column].substr(5, 1) == "D")
	{
		if (stageIndex[row][column].substr(12, 1) == "0")
		{
			_roomInfo[row][column] = RoomType::COURSE;
		}
		if (stageIndex[row][column].substr(12, 1) == "1")
		{
			_roomInfo[row][column] = RoomType::SATAN;
		}
	}
}
