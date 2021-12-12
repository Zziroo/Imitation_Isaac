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

	vector<vector<bool>>	isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중벡터
	vector<string>			stage[2];				// 맵의 이름을 담을 벡터
	vector<vector<string>>	stage01;				// Stage01

	int						countLinkedMap = 1;		// 한 Stage안에 맵들이 연결돼어있는지 확인하기 위한 변수
	int						stageSize = 0;			// Stage 크기
	int						startPoint = 0;			// Stage의 중앙(시작) 지점

public:
	virtual void			Init() override;

	void					ArrangeStageIndex(SampleTileTypes sampleType, int loadIndex);
	void					CountLinkedMap(int row, int column);
	void					CreateStage();
	void					DeginateBossMap(int row, int column);
	void					DeginateMap(int row, int column, size_t index);
	void					SettingStageSize();
};

