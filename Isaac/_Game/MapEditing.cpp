#include "MainConfig.h"
#include "MapEditing.h"

void MapEditing::Init()
{
	// ��� �ʵ��� ����
	SampleTileTypes sampleType = SampleTileTypes::BASEMENT;
	for (int i = 0; i < 100; ++i)
	{
		size_t originIndex = stage[0].size();	// ���� ����� ����(�߰��� �ƴ��� ���ϱ� ����)
		EditStage(sampleType, i);				// map�� �߰�
		if (originIndex == stage[0].size())		// �� �̻� �߰��� �ȵ� �� == ���� �� �̻� ���� ��
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
	// �������� ������ �̵�
	for (size_t i = 0; i < stage[0].size(); ++i)
	{
		string str = "Save/BASEMENT01.map";
		if (stage[0].at(i) == str)
		{
			string bossMap = stage[0].at(i);
			stage[0].erase(stage[0].begin() + 1);		// ���� �ʿ�
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
			stage[1].erase(stage[1].begin() + 1);		// ���� �ʿ�
			stage[1].push_back(bossMap);
			break;
		}
	}
	// ���� ������ stage ũ�� ����
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
	// Stage �ʱ�ȭ
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
	// stage[0]�� ����
	if (sampleType != SampleTileTypes::CAVE)
	{
		stage[0].push_back(loadFileName);
	}
	// stage[1]�� ����
	if (sampleType != SampleTileTypes::BASEMENT)
	{
		stage[1].push_back(loadFileName);
	}

	CloseHandle(hFile);
}

