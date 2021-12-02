#include "MainConfig.h"
#include "TilemapToolScene.h"

#include "Button.h"
#include "ButtonFunction.h"
#include "Image.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);

	backGround = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround_Black.bmp");

	quitFunc = new ButtonFunction;
	button = new Button;
	button->Init();
	button->SetFunction(&ButtonFunction::QuitProgram, quitFunc);

	return S_OK;
}

void TilemapToolScene::Release()
{
	SAFE_RELEASE(button);
	SAFE_DELETE(quitFunc);
}

void TilemapToolScene::Update()
{
	button->Update();
}

void TilemapToolScene::Render(HDC hdc)
{
	backGround->Render(hdc);
	button->Render(hdc);
}
