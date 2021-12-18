#pragma once

#include "Scene.h"
#include <utility>

class Button;
class Image;
class TilemapToolScene : public Scene
{
private:
	Image*						backGround = nullptr;
	Image*						sampleBackGround = nullptr;
	Image*						drawingAreaImg = nullptr;
	vector<Image*>				sampleTileImg;

	SAMPLE_TILE_INFO			sampleTileInfo[BASEMENT_TILE_ROW][SAMPLE_TILE_COLUMN];	// �׸��� �������� ���� ����
	SAMPLE_TILE_INFO			singleSelectedSampleTile;								// Single SampleTile
	SampleTileTypes				sampleTileType = SampleTileTypes::NONE;					// ���� Ÿ���� ����
	TILE_INFO					tempTileInfo[TILE_ROW][TILE_COLUMN];					// ���� ����(�ӽ�)
	TILE_INFO					mainBasementTileInfo[BASEMENT_TILE_ROW][TILE_COLUMN];	// ���� ����(Basement)
	TILE_INFO					mainCaveTileInfo[CAVE_TILE_ROW][TILE_COLUMN];			// ���� ����(Cave)
	TILE_INFO					mainCellarTileInfo[CELLAR_TILE_ROW][TILE_COLUMN];		// ���� ����(Cellar)
	TILE_INFO					mainDepthTileInfo[DEPTH_TILE_ROW][TILE_COLUMN];			// ���� ����(Depth)

	vector<SAMPLE_TILE_INFO>	multiSelectedSampleTile[2];								// Multi SampleTile

	Button*						button = nullptr;

	bool						multiSelectPoint[2] = { false };						// Multi SampleTile Point([0] : ó��, �� ����, [1] : �׸��� ����)
	bool						isMultiSelect = false;									// Multi SampleTile Point �����ߴ���
	bool						finishDrawing = false;									// ���� ������ �׷ȴ���
	bool						initialTileBtnState = true;								// SampleTile Button �ʱ� ����
	bool						debugMode = false;

	int							currShowIndex;
	int							sampleTileCurrIndex[4] = {};
	int							sampleTileMaxIndex[4] = { 4, 5, 4, 3 };
	int							saveIndex[4] = {};

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
	void						Load(int loadIndex = 0);
	void						MarkMultiPoint();
	void						Save(int saveIndex = 0);
	void						SelectMultiTile(RECT rc);
	void						SelectSingleTile(RECT rc);

	virtual ~TilemapToolScene() = default;
};

