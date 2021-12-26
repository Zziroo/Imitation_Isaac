#include "stdafx.h"
#include "NormalMonster.h"

#include "Image.h"

void NormalMonster::Init()
{
	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Attack_Fly.bmp");
		monsterInfo.moveSpeed = 200.0f;
		monsterInfo.type = NormalMonsterTypes::ATTACKFLY;
		monsterInfo.objectSize = 20.0f;
		DeginateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::FLY:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp");
		monsterInfo.type = NormalMonsterTypes::FLY;
		monsterInfo.moveSpeed = 100.0f;
		monsterInfo.objectSize = 20.0f;
		DeginateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::POOTER:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp");
		monsterInfo.type = NormalMonsterTypes::POOTER;
		monsterInfo.moveSpeed = 100.0f;
		monsterInfo.objectSize = 26.0f;
		DeginateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize, -3.0f, 1.0f, -3.0f, 1.0f);
		break;
	default:
		break;
	}
}

void NormalMonster::Release()
{
}

void NormalMonster::Update()
{
	ChangeAnimation();

	Move();

	// Debug
	Monster::Update();
}

void NormalMonster::Render(HDC hdc)
{
	monsterInfo.img->Render(hdc, (INT)monsterInfo.pos.x, (INT)monsterInfo.pos.y, monsterInfo.img->GetCurrFrameX(), monsterInfo.img->GetCurrFrameY());

	//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	//for (int r = 0; r < 14; ++r)
	//{
	//	for (int c = 0; c < 26; ++c)
	//	{
	//		Rectangle(hdc, 120 + (c * 40), 120 + (r * 40), 120 + ((c + 1) * 40), 120 + ((r + 1) * 40));
	//	}
	//}
	//SelectObject(hdc, oldBrush);
	//DeleteObject(myBrush);

	// Debug
	Monster::Render(hdc);
}

void NormalMonster::OnDebug(HDC hdc)
{
#ifdef _DEBUG
	if (debugMode)
	{
		Ellipse(hdc, monsterInfo.shape.left, monsterInfo.shape.top, monsterInfo.shape.right, monsterInfo.shape.bottom);
	}
#endif
}

void NormalMonster::AdvanceAnimation(int elapsedCount)
{
	++monsterInfo.elapsedAnimeCount;
	if (monsterInfo.elapsedAnimeCount > elapsedCount)
	{
		monsterInfo.img->SetCurrFrameY(monsterInfo.img->GetCurrFrameY() + ADVANCE_FRAME);
		if (monsterInfo.img->GetCurrFrameY() >= monsterInfo.img->GetMaxFrameY())
		{
			monsterInfo.img->SetCurrFrameY(ZERO);
		}
		monsterInfo.elapsedAnimeCount = 0;
	}
}

void NormalMonster::ChangeAnimation()
{
	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY:
		AdvanceAnimation(6);
		break;
	case NormalMonsterTypes::FLY: case NormalMonsterTypes::POOTER:
		AdvanceAnimation(11);
		break;
	default:
		break;
	}
}

void NormalMonster::Move()
{
}

void NormalMonster::DeginateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	monsterInfo.shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	monsterInfo.shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	monsterInfo.shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	monsterInfo.shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}
