#include "stdafx.h"
#include "BossMonster.h"

#include "Image.h"

void BossMonster::Init()
{
	monsterInfo.type = BossMonsterTypes::DUKE;

	switch (monsterInfo.type)
	{
	case BossMonsterTypes::DUKE:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Duke.bmp");
		pos = { WIN_SIZE_X * DEVIDE_HALF, WIN_SIZE_Y * DEVIDE_HALF };
		objectSize = 176.0f;
		moveSpeed = 20.0f;
		DesignateBossMonsterShape(pos.x, pos.y, objectSize, 0.0f, -10.0f, 0.0f, -15.0f);
		break;
	default:
		break;
	}
}

void BossMonster::Release()
{
}

void BossMonster::Update()
{


	// Debug
	Monster::Update();
}

void BossMonster::Render(HDC hdc)
{
	monsterInfo.img->Render(hdc, pos.x, pos.y, monsterInfo.img->GetCurrFrameX(), monsterInfo.img->GetCurrFrameY());

	// Debug
	Monster::Render(hdc);
}

void BossMonster::OnDebug(HDC hdc)
{
#ifdef _DEBUG
	if (debugMode)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
#endif
}

void BossMonster::DesignateBossMonsterShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}
