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

	vector<string>					ThinOutMapInfo;			// Sample Tile 맵의 종류를 담을 벡터
	vector<vector<bool>>			isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중벡터
	vector<vector<string>>			stage;					// Stage

	int								countLinkedMap = 1;		// 한 Stage안에 맵들이 연결돼어있는지 확인하기 위한 변수
	int								stageSize = 0;			// Stage 크기
	int								startPoint = 0;			// Stage의 중앙(시작) 지점

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

