#include "stdafx.h"
#include "NormalMonster.h"

#include "AStar.h"
#include "Image.h"
#include "Player.h"

void NormalMonster::Init()
{
	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Attack_Fly.bmp");
		monsterInfo.moveSpeed = 200.0f;
		monsterInfo.type = NormalMonsterTypes::ATTACKFLY;
		monsterInfo.objectSize = 20.0f;
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::FLY:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp");
		monsterInfo.type = NormalMonsterTypes::FLY;
		monsterInfo.moveSpeed = 100.0f;
		monsterInfo.objectSize = 20.0f;
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::POOTER:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp");
		monsterInfo.type = NormalMonsterTypes::POOTER;
		monsterInfo.moveSpeed = 100.0f;
		monsterInfo.objectSize = 26.0f;
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize, -3.0f, 1.0f, -3.0f, 1.0f);
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

	if (monsterInfo.state == MonsterStates::MOVE)
	{
		startPoint = 2;
		Move();
	}

	// Debug
	Monster::Update();
}

void NormalMonster::Render(HDC hdc)
{
	monsterInfo.img->Render(hdc, (INT)monsterInfo.pos.x, (INT)monsterInfo.pos.y, monsterInfo.img->GetCurrFrameX(), monsterInfo.img->GetCurrFrameY());

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
		if (monsterInfo.img->GetCurrFrameY() > monsterInfo.img->GetMaxFrameY())
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

void NormalMonster::DesignateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	monsterInfo.shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	monsterInfo.shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	monsterInfo.shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	monsterInfo.shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}

void NormalMonster::Move()
{
	POINTFLOAT	buffPos = monsterInfo.pos;
	RECT		buffShape = monsterInfo.shape;

	if (monsterInfo.type != NormalMonsterTypes::NONE)
	{
		for (int i = 0; i < TILE_ROW; ++i)
		{
			for (int j = 0; j < TILE_COLUMN; ++j)
			{
				if (aStar->GetAStarMap()[i][j] == 2)
				{
					monsterInfo.pos.x = (FLOAT)(j * TILE_SIZE);
					monsterInfo.pos.y = (FLOAT)(i * TILE_SIZE);
				}
			}
		}
	}

	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY: case NormalMonsterTypes::FLY:
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::POOTER:
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize, -3.0f, 1.0f, -3.0f, 1.0f);
		break;
	default:
		break;
	}

	RECT playerBodyShape = player->GetPlayerBodyShape();
	RECT playerHeadShape = player->GetPlayerHeadShape();
	if (IntersectRect(&colliderRect, &playerBodyShape, &monsterInfo.shape) || IntersectRect(&colliderRect, &playerHeadShape, &monsterInfo.shape))
	{
		monsterInfo.pos = buffPos;
		monsterInfo.shape = buffShape;
	}
}
