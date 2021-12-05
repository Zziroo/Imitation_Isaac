#pragma once

#include "Scene.h"

class Button;
class ButtonFunction;
class Image;
class TilemapToolScene : public Scene
{
private:
	Image*						backGround = nullptr;
	Image*						sampleTileImg = nullptr;

	TILE_INFO					tileInfo[TILE_ROW][TILE_COLUMN];
	SAMPLE_TILE_INFO			sampleTileInfo[SAMPLE_TILE_ROW][SAMPLE_TILE_COLUMN];
	SAMPLE_TILE_INFO			singleSelectedSampleTile;
	vector<SAMPLE_TILE_INFO>	multiSelectedSampleTile;
	bool						isMultiSelect = false;
	bool						finishDrawing = false;

	Button*						button = nullptr;
	ButtonFunction*				buttonFunc = nullptr;

	bool						debugMode = false;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	void OnDebug(HDC hdc);

	virtual ~TilemapToolScene() = default;
};

