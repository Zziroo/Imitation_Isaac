#include "stdafx.h"
#include "BossMonsterHP.h"

#include "Image.h"

void BossMonsterHP::Init()
{
	img = GET_SINGLETON_IMAGE->FindImage("Image/UI/Boss_HP.bmp");

	pos = { WIN_SIZE_X * DEVIDE_HALF, 75.0f };
}

void BossMonsterHP::Release()
{
}

void BossMonsterHP::Update()
{
#ifdef _DEBUG
	UI::Update();
#endif
}

void BossMonsterHP::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y);

	// Debug
	UI::Render(hdc);
}

void BossMonsterHP::OnDebug(HDC hdc)
{
}
