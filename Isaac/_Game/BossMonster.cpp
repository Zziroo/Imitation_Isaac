#include "stdafx.h"
#include "BossMonster.h"

#include "AStar.h"
#include "Image.h"
#include "Player.h"

#define PI 3.14159265357989

void BossMonster::Init()
{
	monsterInfo.type = BossMonsterTypes::DUKE;

	switch (monsterInfo.type)
	{
	case BossMonsterTypes::DUKE:
		monsterInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Duke.bmp");
		pos = { WIN_SIZE_X * DEVIDE_HALF, WIN_SIZE_Y * DEVIDE_HALF };
		objectSize = 176.0f;
		moveSpeed = 5.0f;
		DesignateBossMonsterShape(pos.x, pos.y, objectSize, 0.0f, -10.0f, 0.0f, -15.0f);
		break;
	default:
		break;
	}

	DesignateMonsterSpawnPosition();
}

void BossMonster::Release()
{
}

void BossMonster::Update()
{
	cout << "elapsedCreatenormalMonsterAnimation : " << elapsedCreatenormalMonsterAnimation << "\n";

	if (monsterInfo.state == MonsterStates::IDLE)
	{
		ChangeBossMonsterState();

		if (false == isSpawnNormalMonster)
		{
			ProgressNormalMonsterSpawnAnimation();
		}
		else
		{
			elapsedCreatenormalMonsterAnimation += Timer::GetDeltaTime();
			if (elapsedCreatenormalMonsterAnimation >= 1.0f)
			{
				InitializeBossMonsterAnimation();

				elapsedCreatenormalMonsterAnimation = 0.0f;
			}
		}
	}

	if (monsterInfo.state == MonsterStates::MOVE && aStar->GetLocatedInside())
	{
		Move();

		elapsedCreatenormalMonsterAnimation = 0.0f;
	}

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

		for (int i = 0; i < 8; ++i)
		{
			Ellipse(hdc, spawnShape[i].left, spawnShape[i].top, spawnShape[i].right, spawnShape[i].bottom);
		}
	}
#endif
}

void BossMonster::ApproachTargetPoint()
{
	if (pathWay.empty())
	{
		ChangeBossMonsterState();

		isSpawnNormalMonster = false;

		return;
	}

	POINTFLOAT targetSpotPos = {
		(FLOAT)(pathWay.top().X * TILE_SIZE),
		(FLOAT)(pathWay.top().Y * TILE_SIZE)
	};

	// 다가갈 위치의 X좌표와 NormalMonster의 pos.x위치의 차이로 NormalMonster pos.x 이동
	if (targetSpotPos.x >= pos.x)
	{
		pos.x += moveSpeed * Timer::GetDeltaTime();
	}
	else
	{
		pos.x -= moveSpeed * Timer::GetDeltaTime();
	}

	// 다가갈 위치의 Y좌표와 NormalMonster의 pos.y위치의 차이로 NormalMonster pos.y 이동
	if (targetSpotPos.y >= pos.y)
	{
		pos.y += moveSpeed * Timer::GetDeltaTime();
	}
	else
	{
		pos.y -= moveSpeed * Timer::GetDeltaTime();
	}

	DesignateBossMonsterShape(pos.x, pos.y, objectSize, 0.0f, -10.0f, 0.0f, -15.0f);

	DesignateMonsterSpawnPosition();

	pathWay.pop();

	ApproachTargetPoint();
}

void BossMonster::ChangeBossMonsterState()
{
	elapsedChangeMonsterState += Timer::GetDeltaTime();
	if (elapsedChangeMonsterState > 5.0f)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		int changeStateVariable = dis(gen) % 3;

		if (changeStateVariable == 2)
		{
			monsterInfo.state = MonsterStates::IDLE;
		}
		else
		{
			monsterInfo.state = MonsterStates::MOVE;
		}

		elapsedChangeMonsterState = 0.0f;
	}
}

void BossMonster::DesignateBossMonsterShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}

void BossMonster::DesignateNormalMonsterInfo()
{
	isSpawnNormalMonster = true;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 99);

	int index = dis(gen) % 8 + 1;

	normalMonsterInfo.resize(index);

	DesignateNormalMonsterSpawnPositionInfo();
	DesignateNormalMonsterTypeInfo();
}

void BossMonster::DesignateNormalMonsterSpawnPositionInfo()
{
	for (size_t i = 0; i < normalMonsterInfo.size(); ++i)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		int index = dis(gen) % 8;

		normalMonsterInfo[i].pos = normalMonsterSpawnPos[i];
	}
}

void BossMonster::DesignateNormalMonsterTypeInfo()
{
	for (size_t i = 0; i < normalMonsterInfo.size(); ++i)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, 99);

		int index = dis(gen) % 3;

		switch (index)
		{
		case 0:
			normalMonsterInfo[i].type = NormalMonsterTypes::ATTACKFLY;
			break;
		case 1: case 2:
			normalMonsterInfo[i].type = NormalMonsterTypes::FLY;
			break;
		default:
			break;
		}
	}
}

void BossMonster::DesignateMonsterSpawnPosition()
{
	for (int i = 0; i < 8; ++i)
	{
		float angle = (45.0f * i) * (PI / 180.0f);
		float size = (objectSize * DEVIDE_HALF) + 25.0f;

		normalMonsterSpawnPos[i].x = pos.x + cos(angle) * size;
		normalMonsterSpawnPos[i].y = pos.y - sin(angle) * size;
	}

#ifdef _DEBUG
	for (int i = 0; i < 8; ++i)
	{
		spawnShape[i] = {
			(LONG)(normalMonsterSpawnPos[i].x - 5),
			(LONG)(normalMonsterSpawnPos[i].y - 5),
			(LONG)(normalMonsterSpawnPos[i].x + 5),
			(LONG)(normalMonsterSpawnPos[i].y + 5)
		};
	}
#endif
}

void BossMonster::InitializeBossMonsterAnimation()
{
	monsterInfo.img->SetCurrFrameX(ZERO);
	monsterInfo.img->SetCurrFrameY(ZERO);
}

void BossMonster::InitializeNormalMonsterInfo()
{
	normalMonsterInfo.clear();
}

void BossMonster::Move()
{
	POINTFLOAT	buffPos = pos;
	RECT		buffShape = shape;

	ApproachTargetPoint();

	RECT playerBodyShape = player->GetPlayerBodyShape();
	RECT playerHeadShape = player->GetPlayerHeadShape();
	if (IntersectRect(&colliderRect, &shape, &playerBodyShape) || IntersectRect(&colliderRect, &shape, &playerHeadShape))
	{
		pos = buffPos;
		shape = buffShape;
	}
}

void BossMonster::ProgressNormalMonsterSpawnAnimation()
{
	monsterInfo.img->SetCurrFrameY(1);

	elapsedCreatenormalMonsterAnimation += Timer::GetDeltaTime();
	if (elapsedCreatenormalMonsterAnimation >= 0.25f)
	{
		monsterInfo.img->SetCurrFrameX(1);

		// NormalMonster 정보 생성
		DesignateNormalMonsterInfo();
	}
}
