#pragma once

#include "Scene.h"

class DoorEditing;
class Iamge;
class Minimap;
class NormalMonster;
class Obstacle;
class Player;
class Stage01Scene : public Scene
{
private:
	DoorEditing*								door = nullptr;
	Image*										drawingAreaImg = nullptr;
	Image*										infomationStartImg = nullptr;
	Minimap*									minimap = nullptr;
	Player*										player = nullptr;

	SampleTileTypes								sampleTileType = SampleTileTypes::BASEMENT;

	TILE_INFO									colliderTileInfo[TILE_ROW * TILE_COLUMN];
	TILE_INFO									mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO									mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<vector<array<DOOR_INFO, 4>>>			doorInfo;
	vector<vector<RoomTypes>>					roomInfo;

	vector<vector<string>>						stageIndex;

	int											stageSize = 0;
	int											startPoint = 0;
	int											currColumn = 0;										// �����Ϸ��� ��
	int											currRow = 0;										// �����Ϸ��� ��
	int											sampleTileMaxIndex[4] = { 4, 5, 4, 3 };
	int											stageNum = 0;

	vector<vector<vector<Obstacle*>>>			obstacle;											// Obstacle
	vector<vector<FILE_INFO>>					obstacleFileInfo;									// .obstacle ������ ���ϸ�� ���� �ȿ� ����ִ� obstacle�� ������ �����ϴ� ���� ����
	vector<vector<STORE_OBSTACLE_INFO>>			storeObstacle;										// Obstacle�� �������� �����ϴ� ���� ����
	int											obstacleMaxIndex[3] = { 1, 3, 18 };
	int											roomTypeCount = 3;

	vector<vector<vector<NormalMonster*>>>		normalMonster;										// NormalMonster
	vector<vector<FILE_INFO>>					normalMonsterFileInfo;								// .monster ������ ���ϸ�� ���� �ȿ� ����ִ� Normal Monster�� ������ �����ϴ� ���� ����
	vector<STORE_NORMAL_MONSTER_INFO>			storeNormalMonster;									// NormalMonster�� �������� �����ϴ� ���� ����
	int											normalMonsterMaxIndex = 4;

public:
	virtual HRESULT								Init() override;
	virtual void								Release() override;
	virtual void								Update() override;
	virtual void								Render(HDC hdc) override;

	void										LoadMap(string loadTilemapFileName);
	void										LoadNormalMonster(int row, int column, string loadNormalMonsterFileName, int normalMonsterCount);
	void										NamingNormalMonsterInfo(int row, int column);
	void										LoadObstacle(int row, int column, string loadObstacleFileName, int obstacleCount);
	void										NamingObstacleInfo(int row, int column, string loadObstacleFileName, int obstacleIndex);
	void										SelectMapImage();
	void										TileRender(HDC hdc);

	virtual ~Stage01Scene() = default;
};

