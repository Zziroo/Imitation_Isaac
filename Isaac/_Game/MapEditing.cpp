#include "MainConfig.h"
#include "MapEditing.h"

void MapEditing::Init()
{
	// ��� �ʵ��� ����
	SampleTileTypes sampleType = SampleTileTypes::BASEMENT;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[0].size();	// ���� ����� ����(�߰��� �ƴ��� ���ϱ� ����)
		ArrangeStageIndex(sampleType, i);				// map�� �߰�
		if (originIndex == ThinOutMapInfo[0].size())		// �� �̻� �߰��� �ȵ� �� == ���� �� �̻� ���� ��
		{
			break;
		}
	}
	sampleType = SampleTileTypes::CAVE;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[1].size();
		ArrangeStageIndex(sampleType, i);
		if (originIndex == ThinOutMapInfo[1].size())
		{
			break;
		}
	}
	sampleType = SampleTileTypes::CELLAR;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[0].size();
		ArrangeStageIndex(sampleType, i);
		if (originIndex == ThinOutMapInfo[0].size())
		{
			break;
		}
	}
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[1].size();
		ArrangeStageIndex(sampleType, i);
		if (originIndex == ThinOutMapInfo[1].size())
		{
			break;
		}
	}
	sampleType = SampleTileTypes::DEPTH;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[0].size();
		ArrangeStageIndex(sampleType, i);
		if (originIndex == ThinOutMapInfo[0].size())
		{
			break;
		}
	}
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = ThinOutMapInfo[1].size();
		ArrangeStageIndex(sampleType, i);
		if (originIndex == ThinOutMapInfo[1].size())
		{
			break;
		}
	}
	// �������� ������ �̵�
	for (size_t i = 0; i < ThinOutMapInfo[0].size(); ++i)
	{
		string str = "Save/BASEMENT01.map";
		if (ThinOutMapInfo[0].at(i) == str)
		{
			string bossMap = ThinOutMapInfo[0].at(i);
			ThinOutMapInfo[0].erase(ThinOutMapInfo[0].begin() + 1);		// ���� �ʿ�
			ThinOutMapInfo[0].push_back(bossMap);
			break;
		}
	}
	for (size_t i = 0; i < ThinOutMapInfo[1].size(); ++i)
	{
		string str = "Save/CAVE01.map";
		if (ThinOutMapInfo[1].at(i) == str)
		{
			string bossMap = ThinOutMapInfo[1].at(i);
			ThinOutMapInfo[1].erase(ThinOutMapInfo[1].begin() + 1);		// ���� �ʿ�
			ThinOutMapInfo[1].push_back(bossMap);
			break;
		}
	}
	// ���� ������ stage ũ�� ����
	SettingStageSize();
	// Stage �߾��� Index
	startPoint = (INT)(stageSize * DEVIDE_HALF);
	// Stage �ʱ�ȭ
	stage01.resize(stageSize);
	// Loop
	CreateStage();
#ifdef _DEBUG MapEditing
	cout << "MapEditing\n";
	for (size_t i = 0; i < stage01.size(); ++i)
	{
		for (size_t j = 0; j < stage01[i].size(); ++j)
		{
			cout << stage01[i][j] << "\t";
			if (stage01[i][j].empty())
			{
				cout << "########\t";
			}
		}
		cout << "\n";
	}
	cout << "\n";
#endif
}

void MapEditing::ArrangeStageIndex(SampleTileTypes sampleType, int loadIndex)
{
	string loadFileName = "Save/";
	switch (sampleType)
	{
	case SampleTileTypes::BASEMENT:
		loadFileName += "BASEMENT";
		break;
	case SampleTileTypes::CAVE:
		loadFileName += "CAVE";
		break;
	case SampleTileTypes::CELLAR:
		loadFileName += "CELLAR";
		break;
	case SampleTileTypes::DEPTH:
		loadFileName += "DEPTH";
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}
	// ���ڸ� ������ ��
	if (loadIndex < 10)
	{
		loadFileName += "0";
	}
	loadFileName += to_string(loadIndex) + ".map";

	HANDLE hFile = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD mapSaveFileInfo = sizeof(tagTile) * TILE_ROW * TILE_COLUMN;

	DWORD readByte;
	switch (sampleType)
	{
	case SampleTileTypes::BASEMENT:
		if (ReadFile(hFile, mainBasementTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			return;
		}
		break;
	case SampleTileTypes::CAVE:
		if (ReadFile(hFile, mainCaveTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			return;
		}
		break;
	case SampleTileTypes::CELLAR:
		if (ReadFile(hFile, mainCellarTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			return;
		}
		break;
	case SampleTileTypes::DEPTH:
		if (ReadFile(hFile, mainDepthTileInfo, mapSaveFileInfo, &readByte, NULL) == false)
		{
			return;
		}
		break;
	case SampleTileTypes::NONE:
		break;
	default:
		break;
	}

	// �ߺ� �Ұ� ó��
	for (size_t i = 0; i < ThinOutMapInfo[0].size(); ++i)
	{
		if (ThinOutMapInfo[0][i] == loadFileName)
		{
			CloseHandle(hFile);
			return;
		}
	}
	for (size_t i = 0; i < ThinOutMapInfo[1].size(); ++i)
	{
		if (ThinOutMapInfo[1][i] == loadFileName)
		{
			CloseHandle(hFile);
			return;
		}
	}
	// stage[0]�� ����
	if (sampleType != SampleTileTypes::CAVE)
	{
		ThinOutMapInfo[0].push_back(loadFileName);
	}
	// stage[1]�� ����
	if (sampleType != SampleTileTypes::BASEMENT)
	{
		ThinOutMapInfo[1].push_back(loadFileName);
	}

	CloseHandle(hFile);
}

void MapEditing::CountLinkedMap(int row, int column)
{
	int searchRow = row;
	int searchColumn = column;
	// ���� ���� ��� ������ ����
	int topRow = searchRow - 1;
	int bottomRow = searchRow + 1;
	int leftColumn = searchColumn - 1;
	int rightColumn = searchColumn + 1;
	// ���� �� �ڸ��� ������� ������ (stage01[-1(�� ��)][N] ���� && ���� ���� && �湮�ߴ���)
	if (topRow >= 0 && stage01[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		++countLinkedMap;									// ++����
		isTransitMap[topRow][searchColumn] = true;			// ��� = true
		CountLinkedMap(topRow, searchColumn);
	}
	// �Ʒ��� �� �ڸ��� ������� ������ (stage01[mapSize(�� ��)][N] ���� && ���� ���� && �湮�ߴ���)
	if (bottomRow < stageSize && stage01[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		++countLinkedMap;									// ++����
		isTransitMap[bottomRow][searchColumn] = true;		// ��� = true
		CountLinkedMap(bottomRow, searchColumn);
	}
	// ���� �� �ڸ��� ������� ������ (stage01[N][-1(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (leftColumn >= 0 && stage01[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		++countLinkedMap;									// ++����
		isTransitMap[searchRow][leftColumn] = true;			// ��� = true
		CountLinkedMap(searchRow, leftColumn);
	}
	// ������ �� �ڸ��� ������� ������ (stage01[N][mapSize(�� ��)] ���� && ���� ���� && �湮�ߴ���)
	if (rightColumn < stageSize && stage01[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		++countLinkedMap;									// ++����
		isTransitMap[searchRow][rightColumn] = true;		// ��� = true
		CountLinkedMap(searchRow, rightColumn);
	}
}

void MapEditing::CreateStage()
{
	// Stage �ʱ�ȭ
	for (size_t i = 0; i < stage01.size(); ++i)
	{
		stage01[i].resize(stageSize);
	}
	// �߾ӿ� Start ����
	stage01[startPoint][startPoint] = ThinOutMapInfo[0].front();
	// ������ ����
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	// �������� Start�ʰ� ��ġ�� �ʰ� ����
	DeginateBossMap(dis(gen) % stageSize, dis(gen) % stageSize);
	// ������ ����� ����(���� ����, ���� ���� ����)
	for (size_t i = 1; i < (ThinOutMapInfo[0].size() - 1); ++i)
	{
		DeginateMap(dis(gen) % stageSize, dis(gen) % stageSize, i);
	}
	// �� Stage�ȿ� �ʵ��� ����ž��ִ��� Ȯ���ϱ� ���� ����
	countLinkedMap = 1;
	// ����ߴ����� ���θ� �˱� ���� vector<vector<bool>> ����
	isTransitMap.resize(stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}
	// Start������ true
	isTransitMap[startPoint][startPoint] = true;
	// Start�������� �����¿� ��ĭ�� ������ ����ִ��� �ƴ��� Ȯ�� �ϸ鼭 ���� ��. �� ���� stage[0].size()�� �ٸ��� �ٽ� ó������ ����
	CountLinkedMap(startPoint, startPoint);
	// ����� ���� ������ Stage[0].size() �ٸ��� �ٽ� Stage01 ����
	if (countLinkedMap != ThinOutMapInfo[0].size())
	{
		// ���� �ʱ�ȭ
		for (size_t i = 0; i < stage01.size(); ++i)
		{
			stage01[i].clear();
		}

		CreateStage();
	}
	// ���� ���� ���ƾ��� Ÿ�� ����
	for (size_t i = 0; i < stage01.size(); ++i)
	{
		for (size_t j = 0; j < stage01[i].size(); ++j)
		{
			// BossMap(BASEMENT01.map) �ָ鿡 DEPTH Tilemap�̸� �ٽ� ����
			if (stage01[i][j] == "Save/BASEMENT01.map")
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// ��
				if (topRow >= 0 && (stage01[topRow][j] == "Save/CELLAR00.map" || stage01[topRow][j] == "Save/DEPTH00.map" || stage01[topRow][j] == "Save/DEPTH01.map"))
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (bottomRow < stageSize && (stage01[bottomRow][j] == "Save/CELLAR00.map" || stage01[bottomRow][j] == "Save/DEPTH00.map" || stage01[bottomRow][j] == "Save/DEPTH01.map"))
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (leftColumn >= 0 && (stage01[i][leftColumn] == "Save/CELLAR00.map" || stage01[i][leftColumn] == "Save/DEPTH00.map" || stage01[i][leftColumn] == "Save/DEPTH01.map"))
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (rightColumn < stageSize && (stage01[i][rightColumn] == "Save/CELLAR00.map" || stage01[i][rightColumn] == "Save/DEPTH00.map" || stage01[i][rightColumn] == "Save/DEPTH01.map"))
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
			}
			// DEPTH00.map �� DEPTH01.map ���� �پ� ������ �ٽ� ����
			if (stage01[i][j] == "Save/DEPTH00.map")
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// ��
				if (topRow >= 0 && stage01[topRow][j] == "Save/DEPTH01.map")
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (bottomRow < stageSize && stage01[bottomRow][j] == "Save/DEPTH01.map")
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (leftColumn >= 0 && stage01[i][leftColumn] == "Save/DEPTH01.map")
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
				// ��
				if (rightColumn < stageSize && stage01[i][rightColumn] == "Save/DEPTH01.map")
				{
					// ���� �ʱ�ȭ
					for (size_t i = 0; i < stage01.size(); ++i)
					{
						stage01[i].clear();
					}

					CreateStage();
					return;
				}
			}
		}
	}
}

void MapEditing::DeginateBossMap(int row, int column)
{
	int randRow = row;
	int randColumn = column;
	if ((randRow == startPoint && randColumn == startPoint)				// StartPoint X
		|| (randRow == (startPoint - 1) && randColumn == startPoint)	// StartPoint ��
		|| (randRow == (startPoint + 1) && randColumn == startPoint)	// StartPoint ��
		|| (randRow == startPoint && randColumn == (startPoint - 1))	// StartPoint ��
		|| (randRow == startPoint && randColumn == (startPoint + 1)))	// StartPoint ��
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		DeginateBossMap(dis(gen) % stageSize, dis(gen) % stageSize);
		return;
	}
	// BossMap ����
	stage01[randRow][randColumn] = ThinOutMapInfo[0].back();
}

void MapEditing::DeginateMap(int row, int column, size_t index)
{
	int randRow = row;
	int randColumn = column;
	if (stage01[randRow][randColumn].empty())
	{
		stage01[randRow][randColumn] = ThinOutMapInfo[0][index];
		return;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	randRow = dis(gen) % stageSize;
	randColumn = dis(gen) % stageSize;

	DeginateMap(randRow, randColumn, index);
}

void MapEditing::SettingStageSize()
{
	if (ThinOutMapInfo[0].size() < ((4 - 1) * (4 - 1)) - 2)
	{
		stageSize = 3;
	}
	if (((4 - 1) * (4 - 1)) - 2 <= ThinOutMapInfo[0].size() && ThinOutMapInfo[0].size() < ((5 - 1) * (5 - 1)) - 2)
	{
		stageSize = 4;
	}
	if (((5 - 1) * (5 - 1)) - 2 <= ThinOutMapInfo[0].size() && ThinOutMapInfo[0].size() < ((6 - 1) * (6 - 1)) - 2)
	{
		stageSize = 5;
	}
	if (((6 - 1) * (6 - 1)) - 2 <= ThinOutMapInfo[0].size() && ThinOutMapInfo[0].size() < ((7 - 1) * (7 - 1)) - 2)
	{
		stageSize = 6;
	}
	if (((7 - 1) * (7 - 1)) - 2 <= ThinOutMapInfo[0].size() && ThinOutMapInfo[0].size() < ((8 - 1) * (8 - 1)) - 2)
	{
		stageSize = 7;
	}
	if (((8 - 1) * (8 - 1)) - 2 <= ThinOutMapInfo[0].size() && ThinOutMapInfo[0].size() < ((9 - 1) * (9 - 1)) - 2)
	{
		stageSize = 8;
	}
}
