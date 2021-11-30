#include "MainConfig.h"
#include "Weapon.h"

#include "Image.h"

void Weapon::Init()
{
    Weapon::FindIamge();

    pos.x = WIN_SIZE_X * 0.5f;
    pos.y = (WIN_SIZE_Y * 0.5f) - 150;
    objectSize = 30.0f;
    moveSpeed = 500.0f;
    shape.left = (LONG)(pos.x - (objectSize * 0.5f));
    shape.top = (LONG)(pos.y - (objectSize * 0.5f));
    shape.right = (LONG)(pos.x + (objectSize * 0.5f));
    shape.bottom = (LONG)(pos.y + (objectSize * 0.5f));
}

HRESULT Weapon::FindIamge()
{
	tear = GETSINGLETON_IMAGE->FindImage("Image/Character/Weapon_Tear.bmp");
	if (tear == nullptr)
    {
        cout << "Not Found : Image/Character/Weapon_Tear.bmp\n";
        return E_FAIL;
    }
	return S_OK;
}

void Weapon::Release()
{
}

void Weapon::Update()
{
    if (isFire)
    {
        switch (weaponDir)
        {
        case MoveDir::UP:
            pos.y -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::DOWN:
            pos.y += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::LEFT:
            pos.x -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
            break;
        case MoveDir::RIGHT:
            pos.x += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
            break;
        default:
            break;
        }
    }
    shape.left = (LONG)(pos.x - (objectSize * 0.5f));
    shape.top = (LONG)(pos.y - (objectSize * 0.5f));
    shape.right = (LONG)(pos.x + (objectSize * 0.5f));
    shape.bottom = (LONG)(pos.y + (objectSize * 0.5f));
}

void Weapon::Render(HDC hdc)
{
    // Rectangle
    Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
    // Image
    tear->Render(hdc, (INT)(pos.x), (INT)(pos.y), tear->GetCurrFrameX(), tear->GetCurrFrameY());
}
