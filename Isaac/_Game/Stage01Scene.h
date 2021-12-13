#pragma once

#include "Scene.h"

class Iamge;
class MapEditing;
class RoomEditing;
class Stage01Scene : public Scene
{
private:
	Image*						drawingAreaImg = nullptr;
	MapEditing*					stage01 = nullptr;
	RoomEditing*				namingRoom = nullptr;

	SampleTileTypes				sampleTileType = SampleTileTypes::BASEMENT;

	TILE_INFO					colliderTileInfo[TILE_ROW * TILE_COLUMN];
	TILE_INFO					mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO					mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO					mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO					mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];

	vector<vector<string>>		stage01Index;
	vector<vector<RoomTypes>>	roomInfo;

	int							_stageSize = 0;
	int							_startPoint = 0;
	int							stageColumn = 0;							// 진행하려는 행
	int							stageRow = 0;								// 진행하려는 열
	int							sampleTileMaxIndex[4] = { 4, 5, 4, 3 };

public:
	virtual HRESULT				Init() override;
	virtual void				Release() override;
	virtual void				Update() override;
	virtual void				Render(HDC hdc) override;

	void						Load(string loadFileName);
	void						LoadMap();
	void						TileRender(HDC hdc);

	virtual ~Stage01Scene() = default;
};

