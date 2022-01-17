#include "stdafx.h"
#include "PlayerUI.h"

#include "Image.h"

void PlayerUI::Init()
{
    if (playerHP % 2)
    {
        ++playerHPImageCount;
    }

    playerHPImageCount += (playerHP / 2);

    playerHPInfo.resize(playerHPImageCount);

    for (size_t i = 0; i < playerHPInfo.size(); ++i)
    {
        playerHPInfo[i].pos = { startPos.x + (40 * i), startPos.y };
        playerHPInfo[i].img = GET_SINGLETON_IMAGE->FindImage("Image/UI/Player_HP.bmp");
    }
}

void PlayerUI::Release()
{
}

void PlayerUI::Update()
{
#ifdef _DEBUG
    UI::Update();
#endif

    Hurt();
}

void PlayerUI::Render(HDC hdc)
{
    for (size_t i = 0; i < playerHPInfo.size(); ++i)
    {
        playerHPInfo[i].img->Render(hdc, playerHPInfo[i].pos.x, playerHPInfo[i].pos.y, playerHPInfo[i].frameX, playerHPInfo[i].frameY);
    }

    // Debug
    UI::Render(hdc);
}

void PlayerUI::OnDebug(HDC hdc)
{
}

void PlayerUI::Hurt()
{
    if (playerHP == 10)
    {
        playerHPInfo[4].frameX = 0;
    }
    else if (playerHP == 9)
    {
        playerHPInfo[4].frameX = 1;
    }
    else if (playerHP == 8)
    {
        playerHPInfo[4].frameX = 2;
        playerHPInfo[3].frameX = 0;
    }
    else if (playerHP == 7)
    {
        playerHPInfo[4].frameX = 2;
        playerHPInfo[3].frameX = 1;
    }
    else if (playerHP == 6)
    {
        playerHPInfo[3].frameX = 2;
        playerHPInfo[2].frameX = 0;
    }
    else if (playerHP == 5)
    {
        playerHPInfo[3].frameX = 2;
        playerHPInfo[2].frameX = 1;
    }
    else if (playerHP == 4)
    {
        playerHPInfo[2].frameX = 2;
        playerHPInfo[1].frameX = 0;
    }
    else if (playerHP == 3)
    {
        playerHPInfo[2].frameX = 2;
        playerHPInfo[1].frameX = 1;
    }
    else if (playerHP == 2)
    {
        playerHPInfo[1].frameX = 2;
        playerHPInfo[0].frameX = 0;
    }
    else if (playerHP == 1)
    {
        playerHPInfo[1].frameX = 2;
        playerHPInfo[0].frameX = 1;
    }
    else
    {
        playerHPInfo[0].frameX = 2;
    }
}
