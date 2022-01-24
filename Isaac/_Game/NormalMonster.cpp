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
		monsterInfo.moveSpeed = 20.0f;
		monsterInfo.type = NormalMonsterTypes::ATTACKFLY;
		monsterInfo.objectSize = 20.0f;
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::FLY:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp");
		monsterInfo.type = NormalMonsterTypes::FLY;
		monsterInfo.moveSpeed = 10.0f;
		monsterInfo.objectSize = 20.0f;
		DesignateNorMalMonsterShape(monsterInfo.pos.x, monsterInfo.pos.y, monsterInfo.objectSize);
		break;
	case NormalMonsterTypes::POOTER:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp");
		monsterInfo.type = NormalMonsterTypes::POOTER;
		monsterInfo.moveSpeed = 10.0f;
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

	if (monsterInfo.state == MonsterStates::MOVE && aStar->GetLocatedInside())
	{
		Move();
	}

	// Debug
	Monster::Update();
}

void NormalMonster::Render(HDC hdc)
{
	monsterInfo.img->Render(hdc, (INT)monsterInfo.pos.x, (INT)monsterInfo.pos.y, frameX, frameY);

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
		++frameY;
		if (IsMaxFrameY())
		{
			frameY = 0;
		}
		monsterInfo.elapsedAnimeCount = 0;
	}
}

void NormalMonster::ApproachTargetPoint()
{
	// 기저 조건
	if (pathWay.empty())
	{
		return;
	}

	POINTFLOAT targetSpotPos = {
		(FLOAT)(pathWay.top().X * TILE_SIZE),
		(FLOAT)(pathWay.top().Y * TILE_SIZE)
	};

	// 다가갈 위치의 X좌표와 NormalMonster의 pos.x위치의 차이로 NormalMonster pos.x 이동
	if (targetSpotPos.x >= monsterInfo.pos.x)
	{
		monsterInfo.pos.x += monsterInfo.moveSpeed * Timer::GetDeltaTime();
	}
	else
	{
		monsterInfo.pos.x -= monsterInfo.moveSpeed * Timer::GetDeltaTime();
	}

	// 다가갈 위치의 Y좌표와 NormalMonster의 pos.y위치의 차이로 NormalMonster pos.y 이동
	if (targetSpotPos.y >= monsterInfo.pos.y)
	{
		monsterInfo.pos.y += monsterInfo.moveSpeed * Timer::GetDeltaTime();
	}
	else
	{
		monsterInfo.pos.y -= monsterInfo.moveSpeed * Timer::GetDeltaTime();
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

	//if (monsterInfo.pos.x == targetSpotPos.x && monsterInfo.pos.y == targetSpotPos.y)
	//{
		pathWay.pop();
	//}

	ApproachTargetPoint();
}

void NormalMonster::ChangeAnimation()
{
	switch (monsterInfo.type)
	{
	case NormalMonsterTypes::ATTACKFLY:	
		AdvanceAnimation(3);
		break;
	case NormalMonsterTypes::FLY: case NormalMonsterTypes::POOTER:
		AdvanceAnimation(5);
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

	ApproachTargetPoint();

	RECT playerBodyShape = player->GetPlayerBodyShape();
	RECT playerHeadShape = player->GetPlayerHeadShape();
	if (IntersectRect(&colliderRect, &playerBodyShape, &monsterInfo.shape) || IntersectRect(&colliderRect, &playerHeadShape, &monsterInfo.shape))
	{
		monsterInfo.pos = buffPos;
		monsterInfo.shape = buffShape;
	}
}

bool NormalMonster::IsMaxFrameY() const
{
	return frameY == monsterInfo.img->GetMaxFrameY() + 1;
}
