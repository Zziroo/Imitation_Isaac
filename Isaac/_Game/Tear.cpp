#include "stdafx.h"
#include "Tear.h"

#include "Image.h"

void Tear::Init()
{
    objectSize = 30.0f;
    moveSpeed = 750.0f;
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));
}

void Tear::Release()
{
}

void Tear::Update()
{
    // ���� �ʱ�ȭ
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

void Tear::InitializeWeapon()
{
    // ȭ���� ����� ���� �ʱ�ȭ
    if (shape.left > WIN_SIZE_X || shape.right < 0 || shape.top > WIN_SIZE_Y || shape.bottom < 0)
    {
        isFire = false;
    }
    // �� �Ǵ� �� Ÿ�ϰ� �浹 �ϸ� �ʱ�ȭ
    for (int i = 0; i < (TILE_ROW * TILE_COLUMN); ++i)
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
