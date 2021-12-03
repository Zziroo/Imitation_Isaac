#pragma once

#include "Scene.h"

class Button;
class ButtonFunction;
class Image;
class TilemapToolScene : public Scene
{
private:
	Button*				button = nullptr;
	ButtonFunction*		buttonFunc = nullptr;

	Image*				backGround = nullptr;

	SAMPLE_TILE_INFO	sampleTileInfo[SAMPLE_TILE_ROW][SAMPLE_TILE_COLUMN];
	TILE_INFO			tileInfo[TILE_ROW][TILE_COLUMN];

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual ~TilemapToolScene() = default;
};

