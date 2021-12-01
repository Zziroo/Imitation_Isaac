#include "MainConfig.h"
#include "TilemapToolScene.h"

#include "Button.h"
#include "ButtonFunction.h"
#include "Image.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);

	backGround = GETSINGLETON_IMAGE->FindImage("Image/BackGround/BackGround_Black.bmp");

	quitFunc = new ButtonFunction();
	exitBtn = new Button();
	exitBtn->Init();
	exitBtn->SetFunction(&ButtonFunction::QuitProgram, quitFunc);

	return S_OK;
}

void TilemapToolScene::Release()
{
	SAFE_RELEASE(exitBtn);
}

void TilemapToolScene::Update()
{
	exitBtn->Update();
}

void TilemapToolScene::Render(HDC hdc)
{
	backGround->Render(hdc);
	exitBtn->Render(hdc);
}
