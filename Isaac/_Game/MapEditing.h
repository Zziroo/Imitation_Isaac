#pragma once

#include "GameObject.h"

class Image;
class MapEditing : public GameObject
{
private:
	TILE_INFO				mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO				mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO				mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO				mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<string>			stage[2];			// ���� �̸��� ���� �׸�
	vector<vector<string>>	stage01;			// Stage01
	int						stageSize = 0;		// Stage ũ��
	int						startPoint = 0;		// Stage�� �߾�(����) ����

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;

	int						DeginateBossMap(int point);
	void					DeginateMap(int row, int column, size_t index);
	void					EditStage(SampleTileTypes sampleType, int loadIndex);
};

