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

	TILE_INFO					tileInfo[TILE_ROW][TILE_COLUMN];						// ���� ����
	SAMPLE_TILE_INFO			sampleTileInfo[SAMPLE_TILE_ROW][SAMPLE_TILE_COLUMN];	// ���� ����
	SAMPLE_TILE_INFO			singleSelectedSampleTile;								// Single SampleTile
	vector<SAMPLE_TILE_INFO>	multiSelectedSampleTile[2];								// Multi SampleTile
	bool						multiSelectPoint[2] = { false };						// Multi SampleTile Point([0] : ó��, �� ����, [1] : �׸��� ����)
	bool						isMultiSelect = false;									// Multi SampleTile Point �����ߴ���
	bool						finishDrawing = false;									// ���� ������ �׷ȴ���

	Button*						button = nullptr;
	ButtonFunction*				buttonFunc = nullptr;

	bool						initialTileBtnState = true;								// SampleTile Button �ʱ� ����
	bool						debugMode = false;

	char						text[64] = {};											// MousePointer

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

