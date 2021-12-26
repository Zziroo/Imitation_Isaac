#include "stdafx.h"
#include "Tear.h"

#include "Image.h"
#include "Obstacle.h"

void Tear::Init()
{
    moveSpeed = 750.0f;
}

void Tear::Release()
{
}

void Tear::Update()
{
    // Size 초기화
    InitializeSize();

    // 무기 초기화
    InitializeWeapon();

    Weapon::Update();
}

void Tear::Render(HDC hdc)
{
    if (isFire && tearImg != nullptr)
    {
        tearImg->Render(hdc, (INT)pos.x, (INT)pos.y);
    }

    Weapon::Render(hdc);
}

void Tear::OnDebug(HDC hdc)
{
    if (debugMode)
    {
        Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
    }
}

void Tear::CollideWithObstacle()
{
    RECT obstacleShape = {};
    int collideObstacleIndex = 0;

    for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
    {
        obstacleShape = obstacle[0][currRow][currColumn][i]->GetObstacleShape();
        if (IntersectRect(&colliderRect, &shape, &obstacleShape) && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::THORN)
        {
            collideObstacleIndex = (INT)i;
            isFire = false;
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
            }
        }

    }
}

void Tear::CollideWithMap()
{
    // 상
    for (int i = 0; i < TILE_COLUMN; ++i)
    {
        if (tile[i].terrain == TileTypes::WALL || tile[i].terrain == TileTypes::DOOR)
        {
            if (IntersectRect(&colliderRect, &shape, &tile[i].rc))
            {
                isFire = false;
            }
        }
    }
    // 나머지 방향의 벽 또는 문 타일
    for (int i = 94; i < (TILE_ROW * TILE_COLUMN); ++i)
    {
        if (tile[i].terrain == TileTypes::WALL || tile[i].terrain == TileTypes::DOOR)
        {
            if (IntersectRect(&colliderRect, &shape, &tile[i].rc))
            {
                isFire = false;
            }
        }
    }
}

void Tear::Fire(FireMethods method)
{
    if (isFire)
    {
        switch (method)
        {        
        case FireMethods::GUIEDED:
            break;
        case FireMethods::NORMAL:
            GiveDirectionNormalTear();
            break;
        case FireMethods::ROTATE:
            break;
        case FireMethods::SPRINKLE:
            break;
        default:
            break;
        }
    }

    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));
}

void Tear::GiveDirectionNormalTear()
{
    switch (tearDir)
    {
    case ObjectDir::UP:
        pos.y -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::DOWN:
        pos.y += moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::LEFT:
        pos.x -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::RIGHT:
        pos.x += moveSpeed * Timer::GetDeltaTime();
        break;
    default:
        break;
    }
}

void Tear::InitializeSize()
{
    if (isFire == false)
    {
        objectSize = 0.0f;
    }
}

void Tear::InitializeWeapon()
{
    // 화면을 벗어나면 무기 초기화
    OutsideOfMap();

    // 벽 또는 문 타일과 충돌 하면 초기화
    CollideWithMap();

    // 장애물와 충돌 하면 초기화
    CollideWithObstacle();
}

void Tear::OutsideOfMap()
{
    if (shape.left > WIN_SIZE_X || shape.top > WIN_SIZE_Y || shape.right < 0 || shape.bottom < 0)
    {
        isFire = false;
    }
}
