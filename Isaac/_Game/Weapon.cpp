#include "MainConfig.h"
#include "Weapon.h"

#include "Image.h"

void Weapon::Init()
{
    Weapon::FindIamge();

    pos.x = WIN_SIZE_X * DEVIDE_HALF;
    pos.y = (WIN_SIZE_Y * DEVIDE_HALF) - 150;
    objectSize = 30.0f;
    moveSpeed = 500.0f;
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));
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
    shape.left = (LONG)(pos.x - (objectSize * DEVIDE_HALF));
    shape.top = (LONG)(pos.y - (objectSize * DEVIDE_HALF));
    shape.right = (LONG)(pos.x + (objectSize * DEVIDE_HALF));
    shape.bottom = (LONG)(pos.y + (objectSize * DEVIDE_HALF));

    Weapon::InitializeWeapon();     // ���� �ʱ�ȭ

    //GameObject::OnDebuging();     �� �Լ��� ����ϰ� ������ �ȵ�.
}

void Weapon::Render(HDC hdc)
{
    if (isFire) { tear->Render(hdc, (INT)(pos.x), (INT)(pos.y), tear->GetCurrFrameX(), tear->GetCurrFrameY()); }    // Image

    if (debugMode) { Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom); }                              // Rectangle
}

void Weapon::InitializeWeapon()
{
    // ȭ���� ����� ���� �ʱ�ȭ
    if (shape.left > WIN_SIZE_X || shape.right < 0 || shape.top > WIN_SIZE_Y || shape.bottom < 0) { isFire = false; }
}