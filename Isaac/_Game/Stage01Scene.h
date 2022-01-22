#pragma once

#include "Scene.h"

class AStar;
class BossMonster;
class DoorEditing;
class Iamge;
class Minimap;
class NormalMonster;
class Obstacle;
class Player;
class PlayerUI;
class PlayerTear;
class Stage01Scene : public Scene
{
private:
	BossMonster*								bossMonster = nullptr;
	AStar*										bossMonsterAStar = nullptr;
	DoorEditing*								door = nullptr;
	Image*										drawingAreaImg = nullptr;
	Image*										infomationStartImg = nullptr;
	Minimap*									minimap = nullptr;
	Player*										player = nullptr;
	PlayerUI*									playerUI = nullptr;
	PlayerTear*									playerTear = nullptr;

	SampleTileTypes								sampleTileType = SampleTileTypes::NONE;

	TILE_INFO									colliderTileInfo[TILE_ROW * TILE_COLUMN];
	TILE_INFO									mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<STORE_NORMAL_MONSTER_INFO>			storeNormalMonster;									// NormalMonster의 정보들을 저장하는 이중 벡터

	vector<vector<FILE_INFO>>					normalMonsterFileInfo;								// .monster 파일의 파일명과 파일 안에 들어있는 Normal Monster의 개수를 저장하는 이중 벡터
	vector<vector<FILE_INFO>>					obstacleFileInfo;									// .obstacle 파일의 파일명과 파일 안에 들어있는 obstacle의 개수를 저장하는 이중 벡터
	vector<vector<RoomTypes>>					roomInfo;											// Map의 정보
	vector<vector<STORE_OBSTACLE_INFO>>			storeObstacle;										// Obstacle의 정보들을 저장하는 이중 벡터
	vector<vector<string>>						stageIndex;											// .map 파일의 파일명

	vector<vector<array<DOOR_INFO, 4>>>			doorInfo;											// 문의 정보
	vector<vector<vector<NormalMonster*>>>		normalMonster;										// NormalMonster
	vector<vector<vector<AStar*>>>				normalMonsterAStar;
	vector<vector<vector<Obstacle*>>>			obstacle;											// Obstacle

	int											currColumn = 0;										// 진행하려는 행
	int											currRow = 0;										// 진행하려는 열
	int											normalMonsterMaxIndex = 4;							// .monster 파일의 Max값
	int											obstacleMaxIndex[3] = { 1, 3, 18 };					// Obstacle의 Max값
	int											roomTypeCount = 3;									// Obstacle에 사용된 roomType
	int											sampleTileMaxIndex[4] = { 4, 5, 4, 3 };				// SampleTile의 Max값
	int											stageNum = 0;										// Stage
	int											stageSize = 0;										// 한 Stage당 크기
	int											startPoint = 0;										// 시작 지점

public:
	virtual HRESULT								Init() override;
	virtual void								Release() override;
	virtual void								Update() override;
	virtual void								Render(HDC hdc) override;

	void										MoveToNextMap();
	void										NamingNormalMonsterInfo(int row, int column);
	void										NamingObstacleInfo(int row, int column, const char* loadObstacleFileName, int obstacleIndex);
	void										LoadMap(string loadTilemapFileName);
	void										LoadNormalMonster(int row, int column, string loadNormalMonsterFileName, int normalMonsterCount);
	void										LoadObstacle(int row, int column, string loadObstacleFileName, int obstacleCount);
	void										SelectMapImage();
	void										TileRender(HDC hdc);

	virtual ~Stage01Scene() = default;
};

