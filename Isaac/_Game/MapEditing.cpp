#include "MainConfig.h"
#include "MapEditing.h"

void MapEditing::Init()
{
	// 모든 맵들을 나열
	SampleTileTypes sampleType = SampleTileTypes::BASEMENT;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[0].size();	// 현재 사이즈를 저장(추가가 됐는지 비교하기 위해)
		EditStage(sampleType, i);				// map을 추가
		if (originIndex == stage[0].size())		// 더 이상 추가가 안될 때 == 맵이 더 이상 없을 때
		{
			break;
		}
	}
	sampleType = SampleTileTypes::CAVE;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[1].size();
		EditStage(sampleType, i);
		if (originIndex == stage[1].size())
		{
			break;
		}
	}
	sampleType = SampleTileTypes::CELLAR;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[0].size();
		EditStage(sampleType, i);
		if (originIndex == stage[0].size())
		{
			break;
		}
	}
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[1].size();
		EditStage(sampleType, i);
		if (originIndex == stage[1].size())
		{
			break;
		}
	}
	sampleType = SampleTileTypes::DEPTH;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[0].size();
		EditStage(sampleType, i);
		if (originIndex == stage[0].size())
		{
			break;
		}
	}
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[1].size();
		EditStage(sampleType, i);
		if (originIndex == stage[1].size())
		{
			break;
		}
	}
	// 보스맵을 끝으로 이동
	for (size_t i = 0; i < stage[0].size(); ++i)
	{
		string str = "Save/BASEMENT01.map";
		if (stage[0].at(i) == str)
		{
			string bossMap = stage[0].at(i);
			stage[0].erase(stage[0].begin() + 1);		// 수정 필요
			stage[0].push_back(bossMap);
			break;
		}
	}
	for (size_t i = 0; i < stage[1].size(); ++i)
	{
		string str = "Save/CAVE01.map";
		if (stage[1].at(i) == str)
		{
			string bossMap = stage[1].at(i);
			stage[1].erase(stage[1].begin() + 1);		// 수정 필요
			stage[1].push_back(bossMap);
			break;
		}
	}
	// 맵의 개수로 stage 크기 결정
	if (4 <= stage[0].size() && stage[0].size() < ((4 - 1) * (4 - 1)) - 2)
	{
		stageSize = 3;
	}
	if (((4 - 1) * (4 - 1)) - 2 <= stage[0].size() && stage[0].size() < ((5 - 1) * (5 - 1)) - 2)
	{
		stageSize = 4;
	}
	if (((5 - 1) * (5 - 1)) - 2 <= stage[0].size() && stage[0].size() < ((6 - 1) * (6 - 1)) - 2)
	{
		stageSize = 5;
	}
	// Stage 초기화
	stage01.resize(stageSize);
	for (size_t i = 0; i < stage01.size(); ++i)
	{
		stage01[i].resize(stageSize);
	}
	// Stage 중앙의 Index
	startPoint = stageSize * DEVIDE_HALF;
	// 중앙에 Start 지점
	stage01[startPoint][startPoint] = stage[0].front();
	// 램덤수 생성
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);
	// 보스맵을 Start맵과 겹치지 않게 설정							=> 수정/Start지점 상,하,좌,우 도 겹치지 않게 설정해야함!!
	int row = DeginateBossMap(dis(gen) % stageSize);
	int column = DeginateBossMap(dis(gen) % stageSize);
	stage01[row][column] = stage[0].back();
	// 나머지 방들을 삽입(시작 지점, 보스 지점 제외)
	for (size_t i = 1; i < (stage[0].size() - 1); ++i)
	{
		DeginateMap(dis(gen) % stageSize, dis(gen) % stageSize, i);
	}
	// 모든 맵들이 연결돼있지 않으면 어떻게 할 것인가?
	// 1. 다시 처음부터 돌린다.
	// 2. Start지점의 상하좌우 단계의 맵이 없고 그 다음의 상하좌우 단계의 맵이 존재할 때 존재하지 않은 배열에 기본 맵을 추가(오류 : 전부 다 생길 위험 있음)
}

void MapEditing::Release()
{
}

void MapEditing::Update()
{
}

void MapEditing::Render(HDC hdc)
{
}

int MapEditing::DeginateBossMap(int point)
{
	if (startPoint != point)
	{
		return point;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	return DeginateBossMap(dis(gen) % stageSize);
}

void MapEditing::DeginateMap(int row, int column, size_t index)
{
	int randRow = row;
	int randColumn = column;
	if (stage01[randRow][randColumn].empty())
	{
		stage01[randRow][randColumn] = stage[0].at(index);
		return;
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	randRow = dis(gen) % stageSize;
	randColumn = dis(gen) % stageSize;

	DeginateMap(randRow, randColumn, index);
}

void MapEditing::EditStage(SampleTileTypes sampleType, int loadIndex)
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

	// 중복 불가 처리
	for (size_t i = 0; i < stage[0].size(); ++i)
	{
		if (stage[0].at(i) == loadFileName)
		{
			return;
		}
	}
	for (size_t i = 0; i < stage[1].size(); ++i)
	{
		if (stage[1].at(i) == loadFileName)
		{
			return;
		}
	}
	// stage[0]에 삽입
	if (sampleType != SampleTileTypes::CAVE)
	{
		stage[0].push_back(loadFileName);
	}
	// stage[1]에 삽입
	if (sampleType != SampleTileTypes::BASEMENT)
	{
		stage[1].push_back(loadFileName);
	}

	CloseHandle(hFile);
}

