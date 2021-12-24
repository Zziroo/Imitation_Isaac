#include "stdafx.h"
#include "Tear.h"

#include "GameObject.h"
#include "Image.h"

void Tear::Init()
{
    tear = GET_SINGLETON_IMAGE->FindImage("Image/Character/Weapon_Tear.bmp");

    pos.x = WIN_SIZE_X * DEVIDE_HALF;
    pos.y = (WIN_SIZE_Y * DEVIDE_HALF) - 150;
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
    if (isFire)
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
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));

    InitializeWeapon();     // 무기 초기화

    Weapon::Update();
}

void Tear::Render(HDC hdc)
{
    if (isFire)
    {
        tear->Render(hdc, (INT)(pos.x), (INT)(pos.y), tear->GetCurrFrameX(), tear->GetCurrFrameY());
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

void Tear::Init(GameObject* owner)
{

}

void Tear::InitializeWeapon()
{
    // 화면을 벗어나면 무기 초기화
    if (shape.left > WIN_SIZE_X || shape.right < 0 || shape.top > WIN_SIZE_Y || shape.bottom < 0)
    {
        isFire = false;
    }
}
