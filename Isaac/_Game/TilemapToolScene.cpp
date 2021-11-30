#include "MainConfig.h"
#include "TilemapToolScene.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);

	return S_OK;
}

void TilemapToolScene::Release()
{
}

void TilemapToolScene::Update()
{
}

void TilemapToolScene::Render(HDC hdc)
{
}
