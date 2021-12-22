#include "MainConfig.h"
#include "NormalMonster.h"

#include "Image.h"

void NormalMonster::Init()
{
	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY:
		monsterInfo.type = NormalMonsterTypes::ATTACKFLY;
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Attack_Fly.bmp");
		objectSize = 20.0f;
		DeginateNorMalMonsterShape(pos.x, pos.y, objectSize);
		break;
	case NormalMonsterTypes::FLY:
		monsterInfo.type = NormalMonsterTypes::FLY;
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp");
		objectSize = 20.0f;
		DeginateNorMalMonsterShape(pos.x, pos.y, objectSize);
		break;
	case NormalMonsterTypes::POOTER:
		monsterInfo.type = NormalMonsterTypes::POOTER;
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp");
		objectSize = 26.0f;
		DeginateNorMalMonsterShape(pos.x, pos.y, objectSize, -3.0f, 1.0f, -3.0f, 1.0f);
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
	cout << monsterInfo.elapsedAnimeCount << "\n";

	// Idle
	if (monsterInfo.state == MonsterStates::IDLE)
	{
		++monsterInfo.elapsedAnimeCount;
		if (monsterInfo.elapsedAnimeCount > 11)
		{
			monsterInfo.img->SetCurrFrameY(monsterInfo.img->GetCurrFrameY() + ADVANCE_FRAME);
			if (monsterInfo.img->GetCurrFrameY() >= monsterInfo.img->GetMaxFrameY())
			{
				monsterInfo.img->SetCurrFrameY(ZERO);
			}
			monsterInfo.elapsedAnimeCount = 0;
		}
	}

	// Debug
	Monster::Update();
}

void NormalMonster::Render(HDC hdc)
{
	monsterInfo.img->Render(hdc, (INT)pos.x, (INT)pos.y, monsterInfo.img->GetCurrFrameX(), monsterInfo.img->GetCurrFrameY());

	// Debug
	Monster::Render(hdc);
}

void NormalMonster::OnDebug(HDC hdc)
{
#ifdef _DEBUG
	if (debugMode)
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
#endif
}

void NormalMonster::DeginateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}
