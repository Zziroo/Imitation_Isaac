#pragma once

#include "Scene.h"

class Button;
class ButtonFunction;
class Image;
class TilemapToolScene : public Scene
{
private:
	Image*						backGround = nullptr;
	Image*						sampleBackGround = nullptr;
	Image*						drawingAreaImg = nullptr;
	vector<Image*>				sampleImg;

	SAMPLE_TILE_INFO			singleSelectedSampleTile;								// Single SampleTile
	SampleTileTypes				sampleTileType = SampleTileTypes::NONE;					// 샘플 타일의 종류
	TILE_INFO					mainTileInfo[TILE_ROW][TILE_COLUMN];					// 메인 영역

	vector<SAMPLE_TILE_INFO>	multiSelectedSampleTile[2];								// Multi SampleTile
	vector<SAMPLE_TILE_INFO>	sampleTileInfo[SAMPLE_TILE_ROW][SAMPLE_TILE_COLUMN];	// 그림을 가져오는 샘플 영역
	vector<TILE_INFO>			tempStorageTileInfo[TILE_ROW][TILE_COLUMN];

	Button*						button = nullptr;
	ButtonFunction*				buttonFunc = nullptr;

	bool						multiSelectPoint[2] = { false };						// Multi SampleTile Point([0] : 처음, 끝 지점, [1] : 그리기 영역)
	bool						isMultiSelect = false;									// Multi SampleTile Point 지정했는지
	bool						finishDrawing = false;									// 메인 영역에 그렸는지
	bool						initialTileBtnState = true;								// SampleTile Button 초기 상태
	bool						debugMode = false;

	int							currShowIndex;
	int							sampleTileCurrIndex[4] = {};
	int							sampleTileMaxIndex[4] = { 4, 5, 4, 3 };

	char						text[64] = {};

public:
	virtual HRESULT				Init() override;
	virtual void				Release() override;
	virtual void				Update() override;
	virtual void				Render(HDC hdc) override;
	void						OnDebug(HDC hdc);

	bool						ClickedButton();
	void						DrawMultiTile(RECT rc);
	void						DrawSingleTile(RECT rc);
	void						InitializeMultiPoint();
	void						MarkMultiPoint();
	void						SelectMultiTile(RECT rc);
	void						SelectSingleTile(RECT rc);

	virtual ~TilemapToolScene() = default;
};

