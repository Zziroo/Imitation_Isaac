#include "MainConfig.h"
#include "Player.h"

#include "Image.h"
#include "WeaponManager.h"

void Player::Init()
{
    Player::FindIamge();

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - 30) * 0.5f);

    moveSpeed = 100.0f;

    elapsedAnime = 0;

    // Weapon
    weaponTear = new WeaponManager;
    weaponTear->Init();
}

HRESULT Player::FindIamge()
{
    // playerImg
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:
        bodyImg = GETSINGLETON_IMAGE->FindImage("Image/Character/Body.bmp");
        headImg = GETSINGLETON_IMAGE->FindImage("Image/Character/Head.bmp");
        break;
    case ObjectStates::HURT:
        otherStateImg = GETSINGLETON_IMAGE->FindImage("Image/Character/Hurt.bmp");
        break;
    case ObjectStates::ITEMPICKUP:
        otherStateImg = GETSINGLETON_IMAGE->FindImage("Image/Character/ItemPickUp.bmp");
        break;
    case ObjectStates::JUMP:
        otherStateImg = GETSINGLETON_IMAGE->FindImage("Image/Character/Jump.bmp");
        break;
    case ObjectStates::STAT:
        otherStateImg = GETSINGLETON_IMAGE->FindImage("Image/Character/Stat.bmp");
        break;
    default:
        throw(out_of_range("범위를 벗어남")); // 수정 필요
        break;
    }
    // 예외 처리
    if (bodyImg == nullptr)
    {
        cout << "Not Found : Image/BackGround/Body.bmp\n";
        return E_FAIL;
    }
    if (headImg == nullptr)
    {
        cout << "Not Found : Image/BackGround/Head.bmp\n";
        return E_FAIL;
    }
    if (otherStateImg == nullptr)
    {
        switch (playerState)
        {
        case ObjectStates::HURT:
            cout << "Not Found : Image/BackGround/Hurt.bmp\n";
            return E_FAIL;
            break;
        case ObjectStates::ITEMPICKUP:
            cout << "Not Found : Image/BackGround/ItemPickUp.bmp\n";
            return E_FAIL;
            break;
        case ObjectStates::JUMP:
            cout << "Not Found : Image/BackGround/Jump.bmp\n";
            return E_FAIL;
            break;
        case ObjectStates::STAT:
            cout << "Not Found : Image/BackGround/Stat.bmp\n";
            return E_FAIL;
            break;
        default:
            break;
        }
    }

    return S_OK;
}

void Player::Release()
{
    SAFE_RELEASE(weaponTear);
}

void Player::Update()
{
    Player::PressInputKey();    // 입력키
    weaponTear->Update();       // weapon

    if (GETSINGLETON_KEY->IsStayKeyDown(VK_LCONTROL) && GETSINGLETON_KEY->IsOnceKeyDown('E')) { debugMode = !debugMode; }   // debug
}

void Player::Render(HDC hdc)
{
    // playerImage
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:
        bodyImg->Render(hdc, (INT)(player.bodyPos.x), (INT)(player.bodyPos.y), bodyImg->GetCurrFrameX(), bodyImg->GetCurrFrameY());
        headImg->Render(hdc, (INT)(player.headPos.x), (INT)(player.headPos.y), headImg->GetCurrFrameX(), headImg->GetCurrFrameY());
        break;
    case ObjectStates::HURT:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case ObjectStates::ITEMPICKUP:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case ObjectStates::JUMP:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case ObjectStates::STAT:
        otherStateImg->Render(hdc, (INT)(pos.x + 9), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    default:
        break;
    }

    // weapon
    weaponTear->Render(hdc);

    // debug
    if(debugMode)
    {
        // playerRectangle
        Rectangle(hdc, (INT)(player.bodyShape.left), (INT)(player.bodyShape.top), (INT)(player.bodyShape.right), (INT)(player.bodyShape.bottom));
        Ellipse(hdc, (INT)(player.headShape.left), (INT)(player.headShape.top), (INT)(player.headShape.right), (INT)(player.headShape.bottom));
        // player.headPos
        wsprintf(text, "player.headPos.x : %d", (INT)(player.headPos.x));
        TextOut(hdc, (INT)((WIN_SIZE_X * 0.5f) + 250), INT((WIN_SIZE_Y * 0.5f) - 40), text, (INT)(strlen(text)));
        wsprintf(text, "player.headPos.y : %d", (INT)(player.headPos.y));
        TextOut(hdc, (INT)((WIN_SIZE_X * 0.5f) + 250), INT((WIN_SIZE_Y * 0.5f) - 20), text, (INT)(strlen(text)));
        // MousePointer
        wsprintf(text, "MousePosX : %d", g_ptMouse.x);
        TextOut(hdc, (INT)((WIN_SIZE_X * 0.5f) + 250), INT((WIN_SIZE_Y * 0.5f) + 20), text, (INT)(strlen(text)));
        wsprintf(text, "MousePosY : %d", g_ptMouse.y);
        TextOut(hdc, (INT)((WIN_SIZE_X * 0.5f) + 250), INT((WIN_SIZE_Y * 0.5f) + 40), text, (INT)(strlen(text)));
        // 기울기
        float slope = (FLOAT)((player.headShape.bottom - player.headShape.top)) / (FLOAT)((player.headShape.right - player.headShape.left));
        // section01
        float section01 = player.headShape.bottom - (FLOAT)(player.headShape.right * slope);
        float section02 = slope * WIN_SIZE_X + section01;
        MoveToEx(hdc, 0, section01, NULL);
        LineTo(hdc, WIN_SIZE_X, section02);
        // section02
        section01 = player.headShape.top + (FLOAT)(player.headShape.right * slope);
        section02 = -(slope * WIN_SIZE_X) + section01;
        MoveToEx(hdc, 0, section01, NULL);
        LineTo(hdc, WIN_SIZE_X, section02);
    }
}

void Player::PressInputKey()
{
    // 이동키
    if (GETSINGLETON_KEY->IsStayKeyDown('W'))                               // 상
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::UP;
        player.bodyPos.y -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
        player.headPos.y -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    else if (GETSINGLETON_KEY->IsStayKeyDown('S'))                          // 하
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::DOWN;
        player.bodyPos.y += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
        player.headPos.y += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    if (GETSINGLETON_KEY->IsStayKeyDown('D'))                               // 우
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::RIGHT;
        player.bodyPos.x += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
        player.headPos.x += moveSpeed * GETSINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    else if (GETSINGLETON_KEY->IsStayKeyDown('A'))                           // 좌
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::LEFT;
        player.bodyPos.x -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
        player.headPos.x -= moveSpeed * GETSINGLETON_TIME->GetDeltaTime();
        
        Player::ChangeAnimation();
    }
    // bodyShape
    player.bodyShape.left = (LONG)(player.bodyPos.x - (player.bodySize * 0.5f) - 14);		// Left
    player.bodyShape.top = (LONG)(player.bodyPos.y - (player.bodySize * 0.5f));			    // Top
    player.bodyShape.right = (LONG)(player.bodyPos.x + (player.bodySize * 0.5f) + 14);		// Right
    player.bodyShape.bottom = (LONG)(player.bodyPos.y + (player.bodySize * 0.5f));			// Bottom
    // headShape
    player.headShape.left = (LONG)(player.headPos.x - (player.headSize * 0.5f) - 5);		// Left
    player.headShape.top = (LONG)(player.headPos.y - (player.headSize * 0.5f));			    // Top
    player.headShape.right = (LONG)(player.headPos.x + (player.headSize * 0.5f) + 5);		// Right
    player.headShape.bottom = (LONG)(player.headPos.y + (player.headSize * 0.5f));			// Bottom
    // 이동키 땠을 때
    if (GETSINGLETON_KEY->IsOnceKeyUp('W') || GETSINGLETON_KEY->IsOnceKeyUp('S') || GETSINGLETON_KEY->IsOnceKeyUp('D') || GETSINGLETON_KEY->IsOnceKeyUp('A'))
    {
        playerState = ObjectStates::IDLE;
        bodyImg->SetCurrFrameX(0);
        bodyImg->SetCurrFrameY(0);

        headImg->SetCurrFrameX(0);
    }
    // 공격키
    if (GETSINGLETON_KEY->IsStayKeyDown(VK_LBUTTON)) { Player::FireWeapon(g_ptMouse.x, g_ptMouse.y); }
}

#define MAX_BODY_FRAME 9
void Player::ChangeAnimation()
{
    if (playerDir == MoveDir::UP)
    {
        bodyImg->SetCurrFrameY(0);
        headImg->SetCurrFrameX(4);
    }
    if (playerDir == MoveDir::DOWN)
    {
        bodyImg->SetCurrFrameY(0);
        headImg->SetCurrFrameX(0);
    }
    if (playerDir == MoveDir::RIGHT)
    {
        bodyImg->SetCurrFrameY(1);
        headImg->SetCurrFrameX(2);
    }
    if (playerDir == MoveDir::LEFT)
    {
        bodyImg->SetCurrFrameY(2);
        headImg->SetCurrFrameX(6);
    }

    bodyImg->SetCurrFrameX(bodyImg->GetCurrFrameX() + 1);
    if (bodyImg->GetCurrFrameX() >= MAX_BODY_FRAME) { bodyImg->SetCurrFrameX(0); }
}

void Player::FireWeapon(int x, int y)
{
    float slope = (FLOAT)((player.headShape.bottom - player.headShape.top)) / (FLOAT)((player.headShape.right - player.headShape.left));

    float section01 = slope * x + (player.headShape.bottom - player.headShape.right * slope);
    float section02 = -slope * x + (player.headShape.top + player.headShape.right * slope);

    // 정 중앙을 찍었을 때
    if (x == player.headPos.x && y == player.headPos.y) { weaponTear->WeaponFire(player.headPos, MoveDir::DOWN); }
    // section01 보다 클 때 (하, 좌)
    if (y >= section01)
    {
        // 하
        if (y >= section02) { weaponTear->WeaponFire(player.headPos, MoveDir::DOWN); }
        // 좌
        else { weaponTear->WeaponFire(player.headPos, MoveDir::LEFT); }
    }
    // section01 보다 작을 때 (상, 우)
    else
    {
        // 상
        if(y <= section02) { weaponTear->WeaponFire(player.headPos, MoveDir::UP); }
        // 우
        else { weaponTear->WeaponFire(player.headPos, MoveDir::RIGHT); }
    }
}
