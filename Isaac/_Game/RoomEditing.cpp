#include "MainConfig.h"
#include "RoomEditing.h"

#include "MapEditing.h"

void RoomEditing::Init()
{
	stage01 = new MapEditing;
	stage01->Init();
	// Stage01�� Size�� �ޱ�
	_stageSize = stage01->GetStageSize();
	// StartPoint�� �ޱ�
	_startPoint = stage01->GetStartPoint();
	// Stage Size��ŭ resize�ϱ�
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
	// Room�� ������ ��� ���� Stage Size ���ϱ�
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
	}
	// Start ������ ����
	roomInfo[_startPoint][_startPoint] = RoomType::START;
	// ����ߴ����� ���θ� �˱� ���� vector<vector<bool>> ����
	isTransitMap.resize(_stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(_stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}
	// Start������ true
	isTransitMap[_startPoint][_startPoint] = true;
	// �� Tilemap���� �����ϸ� RoomType���� Naming
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
	// ���� ���� ��� ������ ����
	int topRow = searchRow - 1;
	int bottomRow = searchRow + 1;
	int leftColumn = searchColumn - 1;
	int rightColumn = searchColumn + 1;
	// ���� �� �ڸ��� ������� ������ (stage01[-1(�� ��)][N] ���� && ���� ���� && �湮�ߴ���)
	if (topRow >= 0 && stage01Index[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, topRow, searchColumn);		// Naming �ϱ�
		isTransitMap[topRow][searchColumn] = true;							// ��� = true
		NamingRoom(topRow, searchColumn);
	}
	// �Ʒ��� �� �ڸ��� ������� ������ (stage01[mapSize(�� ��)][N] ���� && ���� ���� && �湮�ߴ���)
	if (bottomRow < _stageSize && stage01Index[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, bottomRow, searchColumn);	// Naming �ϱ�
		isTransitMap[bottomRow][searchColumn] = true;						// ��� = true
		NamingRoom(topRow, searchColumn);
	}
	// ���� �� �ڸ��� ������� ������ (stage01[N][-1(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (leftColumn >= 0 && stage01Index[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, searchRow, leftColumn);		// Naming �ϱ�
		isTransitMap[searchRow][leftColumn] = true;							// ��� = true
		NamingRoom(topRow, searchColumn);
	}
	// ������ �� �ڸ��� ������� ������ (stage01[N][mapSize(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (rightColumn < _stageSize && stage01Index[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		DeclareRoomName(stage01Index, roomInfo, searchRow, rightColumn);	// Naming �ϱ�
		isTransitMap[searchRow][rightColumn] = true;						// ��� = true
		NamingRoom(topRow, searchColumn);
	}
	// ���� �ʿ�!! => Item Room �ʼ�
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
