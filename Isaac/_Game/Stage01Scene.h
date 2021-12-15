#pragma once

#include "Scene.h"

class DoorEditing;
class Iamge;
class Player;
class Stage01Scene : public Scene
{
private:
	DoorEditing*							door = nullptr;
	Image*									drawingAreaImg = nullptr;
	Player*									player = nullptr;

	RECT									colliderRect = {};										// 문과 충돌 처리용
	SampleTileTypes							sampleTileType = SampleTileTypes::BASEMENT;

	TILE_INFO								colliderTileInfo[TILE_ROW * TILE_COLUMN];
	TILE_INFO								mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO								mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<vector<array<DOOR_INFO, 4>>>		doorInfo;
	vector<vector<string>>					stage01Index;
	vector<vector<RoomTypes>>				roomInfo;

	int										_stageSize = 0;
	int										_startPoint = 0;
	int										stageColumn = 0;										// 진행하려는 행
	int										stageRow = 0;											// 진행하려는 열
	int										sampleTileMaxIndex[4] = { 4, 5, 4, 3 };

public:
	virtual HRESULT							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;

	void									Load(string loadFileName);
	void									LoadMap();
	void									TileRender(HDC hdc);

	virtual ~Stage01Scene() = default;
};

