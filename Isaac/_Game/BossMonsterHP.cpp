#include "stdafx.h"
#include "BossMonsterHP.h"

#include "Image.h"

void BossMonsterHP::Init()
{
	img[0] = GET_SINGLETON_IMAGE->FindImage("Image/UI/Boss_HP_BackGround.bmp");
	img[1] = GET_SINGLETON_IMAGE->FindImage("Image/UI/Boss_HP.bmp");

	bossPos[0] = { WIN_SIZE_X * DEVIDE_HALF, 75.0f };
	bossPos[1] = { WIN_SIZE_X * DEVIDE_HALF + 25.0f, 78.0f };
}

void BossMonsterHP::Release()
{
}

void BossMonsterHP::Update()
{
#ifdef _DEBUG
	UI::Update();
#endif

	DamagedByPlayerTear();

	GameClear();
}

void BossMonsterHP::Render(HDC hdc)
{
	img[0]->Render(hdc, (INT)bossPos[0].x, (INT)bossPos[0].y);
	img[1]->DamagedBossMonsterHP(hdc, (INT)bossPos[1].x, (INT)bossPos[1].y, bossMonsterHP);

	// Debug
	UI::Render(hdc);
}

void BossMonsterHP::OnDebug(HDC hdc)
{
}

void BossMonsterHP::DamagedByPlayerTear()
{
	if (isGameClear)
	{
		return;
	}

	bossMonsterHP -= playerAttackValue;
}

void BossMonsterHP::GameClear()
{
	if (bossMonsterHP <= 0)
	{
		isGameClear = true;
	}
}
