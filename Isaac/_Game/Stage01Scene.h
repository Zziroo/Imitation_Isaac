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

	vector<STORE_NORMAL_MONSTER_INFO>			storeNormalMonster;									// NormalMonster�� �������� �����ϴ� ���� ����

	vector<vector<FILE_INFO>>					normalMonsterFileInfo;								// .monster ������ ���ϸ�� ���� �ȿ� ����ִ� Normal Monster�� ������ �����ϴ� ���� ����
	vector<vector<FILE_INFO>>					obstacleFileInfo;									// .obstacle ������ ���ϸ�� ���� �ȿ� ����ִ� obstacle�� ������ �����ϴ� ���� ����
	vector<vector<RoomTypes>>					roomInfo;											// Map�� ����
	vector<vector<STORE_OBSTACLE_INFO>>			storeObstacle;										// Obstacle�� �������� �����ϴ� ���� ����
	vector<vector<string>>						stageIndex;											// .map ������ ���ϸ�

	vector<vector<array<DOOR_INFO, 4>>>			doorInfo;											// ���� ����
	vector<vector<vector<NormalMonster*>>>		normalMonster;										// NormalMonster
	vector<vector<vector<AStar*>>>				normalMonsterAStar;
	vector<vector<vector<Obstacle*>>>			obstacle;											// Obstacle

	int											currColumn = 0;										// �����Ϸ��� ��
	int											currRow = 0;										// �����Ϸ��� ��
	int											normalMonsterMaxIndex = 4;							// .monster ������ Max��
	int											obstacleMaxIndex[3] = { 1, 3, 18 };					// Obstacle�� Max��
	int											roomTypeCount = 3;									// Obstacle�� ���� roomType
	int											sampleTileMaxIndex[4] = { 4, 5, 4, 3 };				// SampleTile�� Max��
	int											stageNum = 0;										// Stage
	int											stageSize = 0;										// �� Stage�� ũ��
	int											startPoint = 0;										// ���� ����

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

