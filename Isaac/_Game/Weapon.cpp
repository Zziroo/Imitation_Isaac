#include "MainConfig.h"
#include "Weapon.h"

#include "Image.h"

void Weapon::Init()
{
    tear = GET_SINGLETON_IMAGE->FindImage("Image/Character/Weapon_Tear.bmp");

    pos.x = WIN_SIZE_X * DEVIDE_HALF;
    pos.y = (WIN_SIZE_Y * DEVIDE_HALF) - 150;
    objectSize = 30.0f;
    moveSpeed = 500.0f;
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));
}

void Weapon::Release()
{
}

void Weapon::Update()
{
    GameObject::Update();

    if (isFire)
    {
        switch (weaponDir)
        {
        case MoveDir::UP:
            pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::DOWN:
            pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::LEFT:
            pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::RIGHT:
            pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
            break;
        default:
            break;
        }
    }
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));

    Weapon::InitializeWeapon();     // 무기 초기화

}

void Weapon::Render(HDC hdc)
{
    //if (isFire) 
    { 
        tear->Render(hdc, (INT)(pos.x), (INT)(pos.y), tear->GetCurrFrameX(), tear->GetCurrFrameY());     // Image
    }

    GameObject::Render(hdc);                          
}

void Weapon::OnDebug(HDC hdc)
{
    if (debugMode)
    {
        Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
    }
}

void Weapon::InitializeWeapon()
{
    // 화면을 벗어나면 무기 초기화
    if (shape.left > WIN_SIZE_X || shape.right < 0 || shape.top > WIN_SIZE_Y || shape.bottom < 0) 
    { 
        isFire = false;
    }
}
