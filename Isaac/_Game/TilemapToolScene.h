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
	Image*						sampleTileImg = nullptr;

	TILE_INFO					mainTileInfo[TILE_ROW][TILE_COLUMN];					// ���� ����
	vector<TILE_INFO>			tempStorageTileInfo[TILE_ROW][TILE_COLUMN];				// �ӽ� ���� ���
	SAMPLE_TILE_INFO			sampleTileInfo[SAMPLE_TILE_ROW][SAMPLE_TILE_COLUMN];	// ���� ����
	SAMPLE_TILE_INFO			singleSelectedSampleTile;								// Single SampleTile
	vector<SAMPLE_TILE_INFO>	multiSelectedSampleTile[2];								// Multi SampleTile

	Button*						button = nullptr;
	ButtonFunction*				buttonFunc = nullptr;

	bool						multiSelectPoint[2] = { false };						// Multi SampleTile Point([0] : ó��, �� ����, [1] : �׸��� ����)
	bool						isMultiSelect = false;									// Multi SampleTile Point �����ߴ���
	bool						finishDrawing = false;									// ���� ������ �׷ȴ���
	bool						initialTileBtnState = true;								// SampleTile Button �ʱ� ����
	bool						debugMode = false;

	int							tempStorageIndex = 1;									// �ӽ� ���� ��� Index
	int							sampleTileNum[4] = { 0 };
	int							tileMaxIndex[4] = { 3, 4, 3, 2 };

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

