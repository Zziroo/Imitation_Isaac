#include "MainConfig.h"
#include "InGameScene.h"

#include "Image.h"
#include "Player.h"
#include "WeaponManager.h"

HRESULT InGameScene::Init()
{
	// Player
	playerIsaac = new Player;
	playerIsaac->Init();
	// WeaponManager
	playerWeapon = new WeaponManager;
	playerWeapon->Init();

	return S_OK;
}

void InGameScene::Release()
{
	SAFE_RELEASE(playerIsaac);
	SAFE_RELEASE(playerWeapon);
}

void InGameScene::Update()
{
	playerIsaac->Update();
	playerWeapon->Update();
}

void InGameScene::Render(HDC hdc)
{
	playerIsaac->Render(hdc);
	playerWeapon->Render(hdc);
}
