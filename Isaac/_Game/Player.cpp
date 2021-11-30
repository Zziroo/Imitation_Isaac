#include "MainConfig.h"
#include "Player.h"

#include "Image.h"
#include "WeaponManager.h"

void Player::Init()
{
    Player::FindIamge();

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - ADJUST_SIZE_30) * DEVIDE_HALF);
    moveSpeed = PLAYER_MOVESPEED;
    elapsedAnime = ZERO;

    // Weapon
    weaponTear = new WeaponManager;
    weaponTear->Init();
    weaponTear->SetOwner(this);
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
    {
        // 콘솔
        if (loadWeapon < takeLoadWeapon) { cout << "loadWeapon : " << loadWeapon << "\n"; }  // 무기 장전
        // debug
        GameObject::OnDebuging();   
    }

    Player::TakeAction();       // 입력키
    weaponTear->Update();       // weapon
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
        otherStateImg->Render(hdc, (INT)(pos.x + ADJUST_SIZE_09), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
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
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) - 40), text, (INT)(strlen(text)));
        wsprintf(text, "player.headPos.y : %d", (INT)(player.headPos.y));
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) - 20), text, (INT)(strlen(text)));
        // MousePointer
        wsprintf(text, "Mouse.PosX : %d", g_ptMouse.x);
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) + 20), text, (INT)(strlen(text)));
        wsprintf(text, "Mouse.PosY : %d", g_ptMouse.y);
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) + 40), text, (INT)(strlen(text)));
        // 기울기
        float slope = (FLOAT)((player.headShape.bottom - player.headShape.top)) / (FLOAT)((player.headShape.right - player.headShape.left));
        // section01
        float section01 = player.headShape.bottom - (FLOAT)(player.headShape.right * slope);
        float section02 = slope * WIN_SIZE_X + section01;
        MoveToEx(hdc, 0, (INT)section01, NULL);
        LineTo(hdc, WIN_SIZE_X, (INT)section02);
        // section02
        section01 = player.headShape.top + (FLOAT)(player.headShape.right * slope);
        section02 = -(slope * WIN_SIZE_X) + section01;
        MoveToEx(hdc, 0, (INT)section01, NULL);
        LineTo(hdc, WIN_SIZE_X, (INT)section02);
    }
}

void Player::TakeAction()
{
    // 이동키 땠을 때
    if (GETSINGLETON_KEY->IsOnceKeyUp('W') || GETSINGLETON_KEY->IsOnceKeyUp('S') || GETSINGLETON_KEY->IsOnceKeyUp('D') || GETSINGLETON_KEY->IsOnceKeyUp('A'))
    {
        playerState = ObjectStates::IDLE;
        bodyImg->SetCurrFrameX(START_BODY_FRAME_X);
        bodyImg->SetCurrFrameY(BODY_DEFAULT_DIR);

        headImg->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 공격키 땠을 때
    if (GETSINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON))
    {
        playerState = ObjectStates::IDLE;
        isFire = false;
    }
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
    // 공격키
    if (GETSINGLETON_KEY->IsStayKeyDown(VK_LBUTTON)) 
    { 
        isFire = true;
        Player::FireWeapon(g_ptMouse.x, g_ptMouse.y);
    }
    
    // bodyShape
    player.bodyShape.left = (LONG)(player.bodyPos.x - (player.bodySize * DEVIDE_HALF) - ADJUST_SIZE_14);	// Left
    player.bodyShape.top = (LONG)(player.bodyPos.y - (player.bodySize * DEVIDE_HALF));			            // Top
    player.bodyShape.right = (LONG)(player.bodyPos.x + (player.bodySize * DEVIDE_HALF) + ADJUST_SIZE_14);	// Right
    player.bodyShape.bottom = (LONG)(player.bodyPos.y + (player.bodySize * DEVIDE_HALF));			        // Bottom
    // headShape
    player.headShape.left = (LONG)(player.headPos.x - (player.headSize * DEVIDE_HALF) - ADJUST_SIZE_05);    // Left
    player.headShape.top = (LONG)(player.headPos.y - (player.headSize * DEVIDE_HALF));			            // Top
    player.headShape.right = (LONG)(player.headPos.x + (player.headSize * DEVIDE_HALF) + ADJUST_SIZE_05);	// Right
    player.headShape.bottom = (LONG)(player.headPos.y + (player.headSize * DEVIDE_HALF));			        // Bottom
}

void Player::ChangeAnimation()
{
    if (playerDir == MoveDir::UP)
    {
        bodyImg->SetCurrFrameY(BODY_DEFAULT_DIR);
        if (!isFire) { headImg->SetCurrFrameX(HEAD_LOOK_UP); }
    }
    if (playerDir == MoveDir::DOWN)
    {
        bodyImg->SetCurrFrameY(BODY_DEFAULT_DIR);
        if (!isFire) { headImg->SetCurrFrameX(HEAD_LOOK_DOWN); }
    }
    if (playerDir == MoveDir::RIGHT)
    {
        bodyImg->SetCurrFrameY(BODY_RIGHT_DIR);
        if (!isFire) { headImg->SetCurrFrameX(HEAD_LOOK_RIGHT); }
    }
    if (playerDir == MoveDir::LEFT)
    {
        bodyImg->SetCurrFrameY(BODY_LEFT_DIR);
        if (!isFire) { headImg->SetCurrFrameX(HEAD_LOOK_LEFT); }
    }

    ++elapsedAnime;
    if (elapsedAnime > 5)
    {
        bodyImg->SetCurrFrameX(bodyImg->GetCurrFrameX() + ADVANCE_FRAME);
        if (bodyImg->GetCurrFrameX() >= MAX_BODY_FRAME_X) { bodyImg->SetCurrFrameX(START_BODY_FRAME_X); }
        elapsedAnime = ZERO;
    }
}

void Player::FireWeapon(int x, int y)
{
    ++loadWeapon;

    float slope = (FLOAT)((player.headShape.bottom - player.headShape.top)) / (FLOAT)((player.headShape.right - player.headShape.left));

    float section01 = (FLOAT)(slope * x) + (player.headShape.bottom - (FLOAT)(player.headShape.right * slope));
    float section02 = (FLOAT)((-slope) * x) + (player.headShape.top + (FLOAT)(player.headShape.right * slope));

    if (loadWeapon > takeLoadWeapon)
    {
        // section01 보다 클 때 (하, 좌)
        if (y >= section01)
        {
            // 하
            if (y >= section02)
            {
                headImg->SetCurrFrameX(ATTACKINGSIDE_DOWN);
                weaponTear->WeaponFire(MoveDir::DOWN);
            }
            // 좌
            else
            {
                headImg->SetCurrFrameX(ATTACKINGSIDE_LEFT);
                weaponTear->WeaponFire(MoveDir::LEFT);
            }
        }
        // section01 보다 작을 때 (상, 우)
        else
        {
            // 상
            if (y <= section02)
            {
                headImg->SetCurrFrameX(ATTACKINGSIDE_UP);
                weaponTear->WeaponFire(MoveDir::UP);
            }
            // 우
            else
            {
                headImg->SetCurrFrameX(ATTACKINGSIDE_RIGHT);
                weaponTear->WeaponFire(MoveDir::RIGHT);
            }
        }

        loadWeapon = ZERO;
    }
}
