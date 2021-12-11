#pragma once

#include "Scene.h"

class Image;
class Player;
class WeaponManager;
class InGameScene : public Scene
{
private:
	Image*				drawingAreaImg = nullptr;
	Player*				playerIsaac = nullptr;

	int					sampleTileMaxIndex[4] = { 4, 5, 4, 3 };

	TILE_INFO			mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];
	TILE_INFO			mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];
	TILE_INFO			mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];
	TILE_INFO			mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];
	SampleTileTypes		sampleTileType = SampleTileTypes::BASEMENT;

public:
	virtual HRESULT		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;

	void				Load(int loadIndex = 0);
	void				TileRender(HDC hdc);

	virtual ~InGameScene() = default;
};

