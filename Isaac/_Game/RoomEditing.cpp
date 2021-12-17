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
	// Stage01�� ��ȸ�ϸ鼭 "Save/BASEMENT01.map"�� Tilemap�� Boss Room���� ����
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
	// RoomTypes::NORMAL �� �������� ����
	// 1. NORMAL�� �ƴ� �� �Լ��� �ٽ� ȣ���� ���� ����
	if (roomInfo[randRow][randColumn] != RoomTypes::NORMAL || roomInfo[randRow][randColumn] == RoomTypes::BOSS)
	{
		// ������ ����
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
	// 2. ������ �� ������ Ư�� ���� ������ �Լ��� �ٽ� ȣ���� ���� ����
	// ��
	if (topRow >= 0)
	{
		if (roomInfo[topRow][randColumn] != RoomTypes::NORMAL)
		{
			// ������ ����
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// ��
	if (bottomRow < _stageSize)
	{
		if (roomInfo[bottomRow][randColumn] != RoomTypes::NORMAL)
		{
			// ������ ����
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// ��
	if (leftColumn >= 0)
	{
		if (roomInfo[randRow][leftColumn] != RoomTypes::NORMAL)
		{
			// ������ ����
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}
	// ��
	if (rightColumn < _stageSize)
	{
		if (roomInfo[randRow][rightColumn] != RoomTypes::NORMAL)
		{
			// ������ ����
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<int> dis(0, 99);

			DeginateItemRoom(dis(gen) % _stageSize, dis(gen) % _stageSize);
			return;
		}
	}

	// NORMAL�� BOSS���� �ƴ��� �� �� ���� RoomType�� ItemRoom���� ����
	roomInfo[randRow][randColumn] = RoomTypes::ITEM;
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
	if (topRow >= 0 && stageIndex[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		DeclareRoomName(topRow, searchColumn);				// Naming �ϱ�
		isTransitMap[topRow][searchColumn] = true;			// ��� = true
		NamingRoom(topRow, searchColumn);
	}
	// �Ʒ��� �� �ڸ��� ������� ������ (stage01[mapSize(�� ��)][N] ���� && ���� ���� && �湮�ߴ���)
	if (bottomRow < _stageSize && stageIndex[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		DeclareRoomName(bottomRow, searchColumn);			// Naming �ϱ�
		isTransitMap[bottomRow][searchColumn] = true;		// ��� = true
		NamingRoom(bottomRow, searchColumn);
	}
	// ���� �� �ڸ��� ������� ������ (stage01[N][-1(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (leftColumn >= 0 && stageIndex[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		DeclareRoomName(searchRow, leftColumn);				// Naming �ϱ�
		isTransitMap[searchRow][leftColumn] = true;			// ��� = true
		NamingRoom(searchRow, leftColumn);
	}
	// ������ �� �ڸ��� ������� ������ (stage01[N][mapSize(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (rightColumn < _stageSize && stageIndex[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		DeclareRoomName(searchRow, rightColumn);			// Naming �ϱ�
		isTransitMap[searchRow][rightColumn] = true;		// ��� = true
		NamingRoom(searchRow, rightColumn);
	}
}

void RoomEditing::Init(int stageNum)
{
	stage = new MapEditing;
	stage->Init(stageNum);
	// Stage01�� Size�� �ޱ�
	_stageSize = stage->GetStageSize();
	// StartPoint�� �ޱ�
	_startPoint = stage->GetStartPoint();
	// Stage Size��ŭ resize�ϰ�
	stageIndex.resize(_stageSize);
	for (size_t i = 0; i < stageIndex.size(); ++i)
	{
		stageIndex[i].resize(_stageSize);
		for (size_t j = 0; j < stageIndex[i].size(); ++j)
		{
			// Stage ������ �޾ƿ���
			stageIndex[i][j] = stage->GetStage()[i][j];
		}
	}
	// Room�� ������ ��� ���� Stage Size ���ϱ�
	roomInfo.resize(_stageSize);
	for (size_t i = 0; i < roomInfo.size(); ++i)
	{
		roomInfo[i].resize(_stageSize);
		for (size_t j = 0; j < roomInfo[i].size(); ++j)
		{
			roomInfo[i][j] = RoomTypes::NONE;
		}
	}
	// Start ������ ����
	roomInfo[_startPoint][_startPoint] = RoomTypes::START;
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
	// BASEMENT01.map�� Tilemap�� BOSS ROOM���� ����
	DeginateBossRoom();
	// ItemRoom ����
	// 1. ������ ����
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	// 2. �Լ��� ���� ItemRoom ����
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
