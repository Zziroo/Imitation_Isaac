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

	vector<string>			stage[2];			// 맵의 이름을 담을 그릇
	vector<vector<string>>	stage01;			// Stage01
	int						stageSize = 0;		// Stage 크기

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;

	void					EditStage(SampleTileTypes sampleType, int loadIndex);
};

