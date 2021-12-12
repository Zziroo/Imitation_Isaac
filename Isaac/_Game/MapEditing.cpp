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

