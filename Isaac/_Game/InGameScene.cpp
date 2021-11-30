#include "MainConfig.h"
#include "InGameScene.h"

#include "Image.h"
#include "Player.h"

HRESULT InGameScene::Init()
{
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
	playerIsaac->Render(hdc);
}
