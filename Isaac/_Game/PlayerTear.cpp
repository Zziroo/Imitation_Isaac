#include "stdafx.h"
#include "PlayerTear.h"

#include "Image.h"
#include "Player.h"
#include "Tear.h"

void PlayerTear::Init()
{
	tearImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Weapon_Tear.bmp");

	vecTear.resize(maxTearCount);
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		vecTear[i] = new Tear;
		vecTear[i]->SetTearImage(tearImg);
		vecTear[i]->SetTileInfo(tile);
		vecTear[i]->Init();
	}
}

void PlayerTear::Release()
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		SAFE_RELEASE(vecTear[i]);
	}

	vecTear.clear();
}

void PlayerTear::Update()
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		vecTear[i]->Fire(FireMethods::NORMAL);
		vecTear[i]->Update();
	}
}

void PlayerTear::Render(HDC hdc)
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		vecTear[i]->Render(hdc);
	}
}

void PlayerTear::Fire()
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		if (vecTear[i]->GetIsFire())
		{
			continue;
		}
		vecTear[i]->SetPos(owner->GetPlayerHeadPos());
		vecTear[i]->SetMoveDir(owner->GetPlayerHeadMoveDir());
		vecTear[i]->SetIsFire(true);
		break;
	}
}

PlayerTear::~PlayerTear() noexcept
{
	owner = nullptr;

	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		SAFE_RELEASE(vecTear[i]);
	}

	vecTear.clear();
}
