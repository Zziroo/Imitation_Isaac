#include "MainConfig.h"
#include "InGameScene.h"

#include "Image.h"
#include "Player.h"

HRESULT InGameScene::Init()
{
	// Black BackGround
	//sampleImg = GETSINGLETON_IMAGE->FindImage("Image/BackGround/BackGround_Black.bmp");
	//if (sampleImg == nullptr)
	//{
	//	cout << "Not Found : Image/BackGround/BackGround_Black.bmp\n";
	//	return E_FAIL;
	//}
	// Player
	playerIsaac = new Player;
	playerIsaac->Init();

	return S_OK;
}

void InGameScene::Release()
{
	SAFE_RELEASE(playerIsaac);
}

void InGameScene::Update()
{
	playerIsaac->Update();
}

void InGameScene::Render(HDC hdc)
{
	//sampleImg->Render(hdc);
	playerIsaac->Render(hdc);
}
