#include "stdafx.h"
#include "MapEditing.h"

void MapEditing::ArrangeStageIndex(SampleTileTypes sampleType, int loadIndex, int stageNum)
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
	// 한자리 숫자일 때
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
	
	// stage[0]에 삽입
	if (stageNum == 0)
	{
		if (sampleType != SampleTileTypes::CAVE)
		{
			ThinOutMapInfo.push_back(loadFileName);
		}
	}
	if (stageNum == 1)
	{
		if (sampleType != SampleTileTypes::BASEMENT)
		{
			ThinOutMapInfo.push_back(loadFileName);
		}
	}

	CloseHandle(hFile);
}

void MapEditing::CountLinkedMap(int row, int column)
{
	int searchRow = row;
	int searchColumn = column;
	// 스택 오버 경고 때문에 정의
	int topRow = searchRow - 1;
	int bottomRow = searchRow + 1;
	int leftColumn = searchColumn - 1;
	int rightColumn = searchColumn + 1;
	// 위쪽 맵 자리가 비어있지 않으면 (stage01[-1(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (topRow >= 0 && stage[topRow][searchColumn].empty() == false && isTransitMap[topRow][searchColumn] == false)
	{
		++countLinkedMap;									// ++경유
		isTransitMap[topRow][searchColumn] = true;			// 통과 = true
		CountLinkedMap(topRow, searchColumn);
	}
	// 아래쪽 맵 자리가 비어있지 않으면 (stage01[mapSize(맵 밖)][N] 방지 && 맵의 유무 && 방문했는지)
	if (bottomRow < stageSize && stage[bottomRow][searchColumn].empty() == false && isTransitMap[bottomRow][searchColumn] == false)
	{
		++countLinkedMap;									// ++경유
		isTransitMap[bottomRow][searchColumn] = true;		// 통과 = true
		CountLinkedMap(bottomRow, searchColumn);
	}
	// 왼쪽 맵 자리가 비어있지 않으면 (stage01[N][-1(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (leftColumn >= 0 && stage[searchRow][leftColumn].empty() == false && isTransitMap[searchRow][leftColumn] == false)
	{
		++countLinkedMap;									// ++경유
		isTransitMap[searchRow][leftColumn] = true;			// 통과 = true
		CountLinkedMap(searchRow, leftColumn);
	}
	// 오른쪽 맵 자리가 비어있지 않으면 (stage01[N][mapSize(맵 밖)] 방지 && 맵의 유무 && 방문했는지)
	if (rightColumn < stageSize && stage[searchRow][rightColumn].empty() == false && isTransitMap[searchRow][rightColumn] == false)
	{
		++countLinkedMap;									// ++경유
		isTransitMap[searchRow][rightColumn] = true;		// 통과 = true
		CountLinkedMap(searchRow, rightColumn);
	}
}

void MapEditing::CreateStage()
{
	// Stage 초기화
	for (size_t i = 0; i < stage.size(); ++i)
	{
		stage[i].resize(stageSize);
	}
	// 중앙에 Start 지점
	stage[startPoint][startPoint] = ThinOutMapInfo.front();
	// 램덤수 생성
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	// 보스맵을 Start맵과 겹치지 않게 설정
	DesignateBossMap(dis(gen) % stageSize, dis(gen) % stageSize);

	// 나머지 방들을 삽입(시작 지점, 보스 지점 제외)
	for (size_t i = 1; i < (ThinOutMapInfo.size() - 1); ++i)
	{
		DesignateMap(dis(gen) % stageSize, dis(gen) % stageSize, i);
	}

	// 한 Stage안에 맵들이 연결돼어있는지 확인하기 위한 변수
	countLinkedMap = 1;

	// 통과했는지의 여부를 알기 위해 vector<vector<bool>> 생성
	isTransitMap.resize(stageSize);
	for (size_t i = 0; i < isTransitMap.size(); ++i)
	{
		isTransitMap[i].resize(stageSize);
		for (size_t j = 0; j < isTransitMap[i].size(); ++j)
		{
			isTransitMap[i][j] = false;
		}
	}

	// Start지점은 true
	isTransitMap[startPoint][startPoint] = true;

	// Start지점부터 상하좌우 한칸씩 진입해 비어있는지 아닌지 확인 하면서 수를 셈. 총 수가 stage[0].size()와 다르면 다시 처음부터 돌림
	CountLinkedMap(startPoint, startPoint);

	// 연결된 맵의 개수와 Stage[0].size() 다르면 다시 Stage01 구성
	if (countLinkedMap != ThinOutMapInfo.size())
	{
		// 맵을 초기화
		for (size_t i = 0; i < stage.size(); ++i)
		{
			stage[i].clear();
		}

		CreateStage();
	}

	// 서로 붙지 말아야할 타일 지정
	for (size_t i = 0; i < stage.size(); ++i)
	{
		for (size_t j = 0; j < stage[i].size(); ++j)
		{
			// BossMap(BASEMENT01.map 또는 CAVE01.map) 주면에 DEPTH Tilemap이면 다시 구성
			if (stage[i][j] == "Save/BASEMENT01.map" || stage[i][j] == "Save/CAVE01.map")
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 상
				if (topRow >= 0 && (stage[topRow][j] == "Save/CELLAR00.map" || stage[topRow][j] == "Save/DEPTH00.map" || stage[topRow][j] == "Save/DEPTH01.map"))
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 하
				if (bottomRow < stageSize && (stage[bottomRow][j] == "Save/CELLAR00.map" || stage[bottomRow][j] == "Save/DEPTH00.map" || stage[bottomRow][j] == "Save/DEPTH01.map"))
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 좌
				if (leftColumn >= 0 && (stage[i][leftColumn] == "Save/CELLAR00.map" || stage[i][leftColumn] == "Save/DEPTH00.map" || stage[i][leftColumn] == "Save/DEPTH01.map"))
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 우
				if (rightColumn < stageSize && (stage[i][rightColumn] == "Save/CELLAR00.map" || stage[i][rightColumn] == "Save/DEPTH00.map" || stage[i][rightColumn] == "Save/DEPTH01.map"))
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
			}

			// DEPTH00.map 과 DEPTH01.map 서로 붙어 있으면 다시 구성
			if (stage[i][j] == "Save/DEPTH00.map")
			{
				int topRow = (INT)(i - 1);
				int bottomRow = (INT)(i + 1);
				int leftColumn = (INT)(j - 1);
				int rightColumn = (INT)(j + 1);
				// 상
				if (topRow >= 0 && stage[topRow][j] == "Save/DEPTH01.map")
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 하
				if (bottomRow < stageSize && stage[bottomRow][j] == "Save/DEPTH01.map")
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 좌
				if (leftColumn >= 0 && stage[i][leftColumn] == "Save/DEPTH01.map")
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
				// 우
				if (rightColumn < stageSize && stage[i][rightColumn] == "Save/DEPTH01.map")
				{
					// 맵을 초기화
					for (size_t i = 0; i < stage.size(); ++i)
					{
						stage[i].clear();
					}

					CreateStage();
					return;
				}
			}
		}
	}
}

void MapEditing::CreateStageSize()
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

void MapEditing::DesignateBossMap(int row, int column)
{
	int randRow = row;
	int randColumn = column;
	if ((randRow == startPoint && randColumn == startPoint)				// StartPoint X
		|| (randRow == (startPoint - 1) && randColumn == startPoint)	// StartPoint 상
		|| (randRow == (startPoint + 1) && randColumn == startPoint)	// StartPoint 하
		|| (randRow == startPoint && randColumn == (startPoint - 1))	// StartPoint 좌
		|| (randRow == startPoint && randColumn == (startPoint + 1)))	// StartPoint 우
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		DesignateBossMap(dis(gen) % stageSize, dis(gen) % stageSize);
		return;
	}
	// BossMap 설정
	stage[randRow][randColumn] = ThinOutMapInfo.back();
}

void MapEditing::DesignateMap(int row, int column, size_t index)
{
	int randRow = row;
	int randColumn = column;
	if (stage[randRow][randColumn].empty())
	{
		stage[randRow][randColumn] = ThinOutMapInfo[index];
		return;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	randRow = dis(gen) % stageSize;
	randColumn = dis(gen) % stageSize;

	DesignateMap(randRow, randColumn, index);
}

void MapEditing::Init(int stageNum)
{	
	// 모든 맵들을 나열
	if (stageNum == 0)
	{
		SampleTileTypes sampleType = SampleTileTypes::BASEMENT;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();			// 현재 사이즈를 저장(추가가 됐는지 비교하기 위해)
			ArrangeStageIndex(sampleType, i, stageNum);			// map을 추가
			if (originIndex == ThinOutMapInfo.size())			// 더 이상 추가가 안될 때 == 맵이 더 이상 없을 때
			{
				break;
			}
		}

		sampleType = SampleTileTypes::CELLAR;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();
			ArrangeStageIndex(sampleType, i, stageNum);
			if (originIndex == ThinOutMapInfo.size())
			{
				break;
			}
		}

		sampleType = SampleTileTypes::DEPTH;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();
			ArrangeStageIndex(sampleType, i, stageNum);
			if (originIndex == ThinOutMapInfo.size())
			{
				break;
			}
		}

		// 보스맵을 끝으로 이동
		for (size_t i = 0; i < ThinOutMapInfo.size(); ++i)
		{
			string str = "Save/BASEMENT01.map";
			if (ThinOutMapInfo.at(i) == str)
			{
				string bossMap = ThinOutMapInfo.at(i);
				ThinOutMapInfo.erase(ThinOutMapInfo.begin() + 1);
				ThinOutMapInfo.push_back(bossMap);
				break;
			}
		}
	}
	if (stageNum == 1)
	{
		SampleTileTypes sampleType = SampleTileTypes::CAVE;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();
			ArrangeStageIndex(sampleType, i, stageNum);
			if (originIndex == ThinOutMapInfo.size())
			{
				break;
			}
		}

		sampleType = SampleTileTypes::CELLAR;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();
			ArrangeStageIndex(sampleType, i, stageNum);
			if (originIndex == ThinOutMapInfo.size())
			{
				break;
			}
		}

		sampleType = SampleTileTypes::DEPTH;
		for (int i = 0; i < 100; ++i)
		{
			size_t originIndex = ThinOutMapInfo.size();
			ArrangeStageIndex(sampleType, i, stageNum);
			if (originIndex == ThinOutMapInfo.size())
			{
				break;
			}
		}

		// 보스맵을 끝으로 이동
		for (size_t i = 0; i < ThinOutMapInfo.size(); ++i)
		{
			string str = "Save/CAVE01.map";
			if (ThinOutMapInfo.at(i) == str)
			{
				string bossMap = ThinOutMapInfo.at(i);
				ThinOutMapInfo.erase(ThinOutMapInfo.begin() + 1);
				ThinOutMapInfo.push_back(bossMap);
				break;
			}
		}
	}

	// 맵의 개수로 stage 크기 결정
	CreateStageSize();
	// Stage 중앙의 Index
	startPoint = (INT)(stageSize * DEVIDE_HALF);
	// Stage 초기화
	stage.resize(stageSize);
	// Loop
	CreateStage();
#ifdef _DEBUG MapEditing
	cout << "MapEditing\n";
	for (size_t i = 0; i < stage.size(); ++i)
	{
		for (size_t j = 0; j < stage[i].size(); ++j)
		{
			cout << stage[i][j] << "\t";
			if (stage[i][j].empty())
			{
				cout << "########\t";
			}
		}
		cout << "\n";
	}
	cout << "\n";
#endif
}