#include "stdafx.h"
#include "PlayerTear.h"

#include "BossMonster.h"
#include "Image.h"
#include "NormalMonster.h"
#include "Obstacle.h"
#include "Player.h"
#include "Tear.h"

void PlayerTear::Init()
{
	tearImg = GET_SINGLETON_IMAGE->FindImage("Image/Weapon/Tear.bmp");

	objectSize = 30.0f;

	vecTear.resize(maxTearCount);
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		vecTear[i] = new Tear;
		vecTear[i]->SetTearImage(tearImg);
		vecTear[i]->SetObstacleInfo(obstacle);
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

	CollideWithObstacle();
}

void PlayerTear::Render(HDC hdc)
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		vecTear[i]->Render(hdc);
	}
}

void PlayerTear::CollideWithBossMonster()
{
	RECT bossMonsterShape = bossMonster->GetShape();
	RECT playerTearShape = {};

	for (int i = 0; i < vecTear.size(); ++i)
	{
		playerTearShape = vecTear[i]->GetShape();
		if (IntersectRect(&colliderRect, &playerTearShape, &bossMonsterShape) && bossMonster->GetBossMonsterState() != MonsterStates::DEAD)
		{
			vecTear[i]->SetIsFire(false);
			vecTear[i]->SetObjectSize(0.0f);

			attackBossMonster = true;
		}
	}
}

void PlayerTear::CollideWithNormalMonster()
{
	// NormalMonster들과 충돌 하면 초기화
	RECT normalMonsterShape = {};
	RECT playerTearShape = {};
	int collideNormalMonsterIndex = 0;
	int eraseIndex = -1;

	for (auto iter = normalMonster[0][currRow][currColumn].begin(); iter != normalMonster[0][currRow][currColumn].end(); ++iter)
	{
		if ((*iter)->GetNormalMonsterImage() == nullptr)
		{
			normalMonster[0][currRow][currColumn].erase(iter);
			return;
		}
		else
		{
			++eraseIndex;
			normalMonsterShape = (*iter)->GetNormalMonsterShape();
			for (int j = 0; j < vecTear.size(); ++j)
			{
				playerTearShape = vecTear[j]->GetShape();
				if (IntersectRect(&colliderRect, &playerTearShape, &normalMonsterShape))
				{
					vecTear[j]->SetIsFire(false);
					SAFE_RELEASE((*iter));
					normalMonster[0][currRow][currColumn].erase(iter);
					attackNormalMonster = true;
					return;
				}
			}
		}
	}
}

void PlayerTear::CollideWithObstacle()
{
	for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
	{
		Obstacle* currentObstacle = obstacle[0][currRow][currColumn][i];

		for (int j = 0; j < vecTear.size(); ++j)
		{
			RECT obstacleShape = currentObstacle->GetShape();
			RECT playerTearShape = vecTear[j]->GetShape();

			if (IntersectRect(&colliderRect, &playerTearShape, &obstacleShape) &&
				currentObstacle->GetObstacleType() != ObstacleTypes::THORN)
			{
				vecTear[j]->SetIsFire(false);
				vecTear[j]->SetObjectSize(0.0f);

				if (ObstacleTypes::BONFIRE == currentObstacle->GetObstacleType())
				{
					currentObstacle->SetNextFrameY();

					if (currentObstacle->IsMaxFrameY())
					{
						currentObstacle->SetObstacleDamaged(false);
						currentObstacle->SetObjectSize(0.0f);
						currentObstacle->DesignateObstacleShape(currentObstacle->GetPos());
					}

					return;
				}
				else if (ObstacleTypes::DDONG == currentObstacle->GetObstacleType())
				{
					currentObstacle->SetNextFrameX();

					if (currentObstacle->IsMaxFrameX())
					{
						currentObstacle->SetObjectSize(0.0f);
						currentObstacle->DesignateObstacleShape(currentObstacle->GetPos());
					}

					return;
				}
			}
		}
	}
}

void PlayerTear::ExtinctWeapon()
{
	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		if (vecTear[i]->GetIsFire())
		{
			vecTear[i]->SetIsFire(false);
		}
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
		vecTear[i]->SetCurrCloumn(currColumn);
		vecTear[i]->SetCurrRow(currRow);
		vecTear[i]->SetPos(player->GetPlayerHeadPos());
		vecTear[i]->SetObjectSize(objectSize);
		vecTear[i]->SetMoveDir(player->GetPlayerHeadMoveDir());
		vecTear[i]->SetIsFire(true);
		break;
	}
}

PlayerTear::~PlayerTear() noexcept
{
	player = nullptr;

	for (size_t i = 0; i < vecTear.size(); ++i)
	{
		SAFE_RELEASE(vecTear[i]);
	}

	vecTear.clear();
}
