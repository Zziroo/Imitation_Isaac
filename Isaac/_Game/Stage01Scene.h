#pragma once

#include "Scene.h"

class DoorEditing;
class Iamge;
class Minimap;
class Obstacle;
class Player;
class Stage01Scene : public Scene
{
private:
	typedef struct tagObstacleFileInfo
	{
		string								index;					// roomType마다 파일의 이름을 기억
		int									count = 0;				// roomType마다 obstacle의 개수를 기억
	} OBSTACLE_FILE_INFO;

private:
	DoorEditing*							door = nullptr;
	Image*									drawingAreaImg = nullptr;
	Image*									infomationStartImg = nullptr;
	Minimap*								minimap = nullptr;
	Player*									player = nullptr;

	SampleTileTypes							sampleTileType = SampleTileTypes::BASEMENT;

	TILE_INFO								colliderTileInfo[TILE_ROW * TILE_COLUMN];
	TILE_INFO								mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<vector<RoomTypes>>				roomInfo;
	vector<vector<array<DOOR_INFO, 4>>>		doorInfo;

	vector<vector<string>>					stageIndex;

	int										stageSize = 0;
	int										startPoint = 0;
	int										currColumn = 0;										// 진행하려는 행
	int										currRow = 0;										// 진행하려는 열
	int										sampleTileMaxIndex[4] = { 4, 5, 4, 3 };
	int										stageNum = 0;

	vector<vector<vector<Obstacle*>>>		obstacle;											// Obstacle
	vector<vector<OBSTACLE_FILE_INFO>>		obstacleFileInfo;									// .obstacle 파일의 파일명과 파일 안에 들어있는 obstacle의 개수를 저장하는 이중 벡터
	vector<vector<STORE_OBSTACLE_INFO>>		storeObstacle;
	vector<vector<int>>						sumObstacleCount;									// 저장한 obstacleFileInfo의 count들을 각각 더하여 총 몇개를 할당 받을 건지 Render할 때 얼마만큼 보여줄지 정하기 위한 이중 벡터
	int										obstacleMaxIndex[3] = { 1, 3, 15 };
	int										totalObstacleCount = 0;
	int										roomTypeCount = 3;

public:
	virtual HRESULT							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;

	void									NamingObstacleInfo(int row, int column, string loadObstacleFileName, int obstacleIndex);
	void									LoadMap(string loadTilemapFileName);
	void									LoadObstacle(int row, int column, string loadObstacleFileName, int obstacleCount);
	void									SelectMapImage();
	void									TileRender(HDC hdc);

	virtual ~Stage01Scene() = default;
};

