#pragma once

#include "GameObject.h"

class Image;
class MapEditing : public GameObject
{
private:
	TILE_INFO						mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO						mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO						mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO						mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<string>					ThinOutMapInfo;			// Sample Tile ���� ������ ���� ����
	vector<vector<bool>>			isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���ߺ���
	vector<vector<string>>			stage;					// Stage

	int								countLinkedMap = 1;		// �� Stage�ȿ� �ʵ��� ����ž��ִ��� Ȯ���ϱ� ���� ����
	int								stageSize = 0;			// Stage ũ��
	int								startPoint = 0;			// Stage�� �߾�(����) ����

public:
	void							ArrangeStageIndex(SampleTileTypes sampleType, int loadIndex, int stageNum);
	void							CountLinkedMap(int row, int column);
	void							CreateStage();
	void							CreateStageSize();
	void							DesignateBossMap(int row, int column);
	void							DesignateMap(int row, int column, size_t index);
	void							Init(int stageNum = 0);

	vector<vector<string>>			GetStage() { return this->stage; }
	int								GetStageSize() { return this->stageSize; }
	int								GetStartPoint() { return this->startPoint; }

	virtual ~MapEditing() = default;
};

