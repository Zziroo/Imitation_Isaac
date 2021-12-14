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

	vector<string>					ThinOutMapInfo[2];		// Sample Tile ���� ������ ���� ����
	vector<vector<bool>>			isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���ߺ���
	vector<vector<string>>			stage01;				// Stage01

	int								countLinkedMap = 1;		// �� Stage�ȿ� �ʵ��� ����ž��ִ��� Ȯ���ϱ� ���� ����
	int								stageSize = 0;			// Stage ũ��
	int								startPoint = 0;			// Stage�� �߾�(����) ����

public:
	virtual void					Init() override;

	void							ArrangeStageIndex(SampleTileTypes sampleType, int loadIndex);
	void							CountLinkedMap(int row, int column);
	void							CreateStage();
	void							DeginateBossMap(int row, int column);
	void							DeginateMap(int row, int column, size_t index);
	void							SettingStageSize();

	inline vector<vector<string>>	GetStage() { return this->stage01; }
	inline int						GetStageSize() { return this->stageSize; }
	inline int						GetStartPoint() { return this->startPoint; }

	virtual ~MapEditing() = default;
};

