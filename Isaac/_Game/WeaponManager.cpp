#include "MainConfig.h"
#include "WeaponManager.h"

#include "Player.h"
#include "Weapon.h"

void WeaponManager::Init()
{
	vecWeapon.resize(maxWeaponCount);

	for (size_t i = 0; i < vecWeapon.size(); ++i)
	{
		vecWeapon[i] = new Weapon;		// vecWeapon.push_back(new Weapon); ¶ûÀÇ Â÷ÀÌÁ¡
		vecWeapon[i]->Init();
	}
}

HRESULT WeaponManager::FindIamge()
{
	return E_NOTIMPL;
}

void WeaponManager::Release()
{
	for (size_t i = 0; i < vecWeapon.size(); ++i) { SAFE_RELEASE(vecWeapon[i]); }
	vecWeapon.clear();
}

void WeaponManager::Update()
{
	for (size_t i = 0; i < vecWeapon.size(); ++i) { vecWeapon[i]->Update(); }
}

void WeaponManager::Render(HDC hdc)
{
	for (size_t i = 0; i < vecWeapon.size(); ++i) { vecWeapon[i]->Render(hdc); }
}

void WeaponManager::WeaponFire(MoveDir moveDir)
{
	for (size_t i = 0; i < vecWeapon.size(); ++i) 
	{ 
		if (vecWeapon[i]->GetIsFire())
			continue;
		vecWeapon[i]->SetIsFire(true);
		vecWeapon[i]->SetPos(owner->GetPlayerHeadPos());
		vecWeapon[i]->SetMoveDir(moveDir);
		break;
	}
}
