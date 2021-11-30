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
	// Weapon
	weaponTear = new WeaponManager;
	weaponTear->Init();

	return S_OK;
}

void InGameScene::Release()
{
	SAFE_RELEASE(playerIsaac);
	SAFE_RELEASE(weaponTear);
}

void InGameScene::Update()
{
	weaponTear->Update();
	playerIsaac->Update();
}

void InGameScene::Render(HDC hdc)
{
	playerIsaac->Render(hdc);
	weaponTear->Render(hdc);
}
