#include "stdafx.h"
#include "PlayerTear.h"

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

void PlayerTear::CollideWithNormalMonster()
{
	// NormalMonster들과 충돌 하면 초기화
	RECT normalMonsterShape = {};
	RECT playerTearShape = {};
	int collideNormalMonsterIndex = 0;

	for (auto iter = normalMonster[0][currRow][currColumn].begin(); iter != normalMonster[0][currRow][currColumn].end(); ++iter)
	{
		normalMonsterShape = (*iter)->GetNormalMonsterShape();
		for (int j = 0; j < vecTear.size(); ++j)
		{
			playerTearShape = vecTear[j]->GetShape();
			if (IntersectRect(&colliderRect, &playerTearShape, &normalMonsterShape))
			{
				vecTear[j]->SetIsFire(false);
				normalMonster[0][currRow][currColumn].erase(iter);
				return;
			}
		}
	}
}

void PlayerTear::CollideWithObstacle()
{
	// 장애물와 충돌 하면 초기화												// 문제 발생! ! => 왜 모든 이미지가 변하는지 모르겠습니다.
	RECT obstacleShape = {};
	RECT playerTearShape = {};
	int collideObstacleIndex = 0;

	for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
	{
		obstacleShape = obstacle[0][currRow][currColumn][i]->GetShape();
		for (int j = 0; j < vecTear.size(); ++j)
		{
			playerTearShape = vecTear[j]->GetShape();
			if (IntersectRect(&colliderRect, &playerTearShape, &obstacleShape) && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::THORN)
			{
				collideObstacleIndex = (INT)i;
				vecTear[j]->SetIsFire(false);
				// Obstacle이 Bonfire일 때
				if (obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleType() == ObstacleTypes::BONFIRE)
				{
					obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->SetCurrFrameY(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetCurrFrameY() + ADVANCE_FRAME);
					if (obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetCurrFrameY() >= obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetMaxFrameY() - 1)
					{
						obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->SetCurrFrameY(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetMaxFrameY() - 1);
						obstacle[0][currRow][currColumn][collideObstacleIndex]->SetObstacleDamaged(false);
						obstacle[0][currRow][currColumn][collideObstacleIndex]->SetObjectSize(0.0f);
						obstacle[0][currRow][currColumn][collideObstacleIndex]->DeginateObstacleShape(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetPos().x, obstacle[0][currRow][currColumn][collideObstacleIndex]->GetPos().y, obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObjectSize());
					}
					break;
				}
				// Obstacle이 DDong일 때
				if (obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleType() == ObstacleTypes::DDONG)
				{
					obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->SetCurrFrameX(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetCurrFrameX() + ADVANCE_FRAME);
					if (obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetCurrFrameX() >= obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetMaxFrameX() - 1)
					{
						obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->SetCurrFrameX(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObstacleImage()->GetMaxFrameX() - 1);
						obstacle[0][currRow][currColumn][collideObstacleIndex]->SetObjectSize(0.0f);
						obstacle[0][currRow][currColumn][collideObstacleIndex]->DeginateObstacleShape(obstacle[0][currRow][currColumn][collideObstacleIndex]->GetPos().x, obstacle[0][currRow][currColumn][collideObstacleIndex]->GetPos().y, obstacle[0][currRow][currColumn][collideObstacleIndex]->GetObjectSize());
					}
					break;
				}
			}
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
		vecTear[i]->SetPos(owner->GetPlayerHeadPos());
		vecTear[i]->SetObjectSize(objectSize);
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
