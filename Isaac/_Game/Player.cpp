#include "MainConfig.h"
#include "Player.h"

#include "Image.h"
#include "WeaponManager.h"

void Player::Init()
{
    // playerImg
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:
        bodyInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Character/Body.bmp");
        headInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Character/Head.bmp");
        break;
    case ObjectStates::HURT:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Hurt.bmp");
        break;
    case ObjectStates::ITEMPICKUP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/ItemPickUp.bmp");
        break;
    case ObjectStates::JUMP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Jump.bmp");
        break;
    case ObjectStates::STAT:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Stat.bmp");
        break;
    default:
        throw(out_of_range("범위를 벗어남"));
        break;
    }

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - ADJUST_SIZE_30) * DEVIDE_HALF);
    moveSpeed = PLAYER_MOVESPEED;
    elapsedAnime = ZERO;

    // Weapon
    weaponTear = new WeaponManager;
    weaponTear->Init();
    weaponTear->SetOwner(this);
}

void Player::Release()
{
    SAFE_RELEASE(weaponTear);
}

void Player::Update()
{
#ifdef _DEBUG
    GameObject::Update();
    if (loadWeapon < takeLoadWeapon) 
    { 
        cout << "loadWeapon : " << loadWeapon << "\n";  // 무기 장전
    }
#endif

    Player::TakeAction();       // 입력키
    weaponTear->Update();       // weapon
}

void Player::Render(HDC hdc)
{
    // playerImage
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:
        bodyInfo.image->Render(hdc, (INT)(bodyInfo.pos.x), (INT)(bodyInfo.pos.y), bodyInfo.image->GetCurrFrameX(), bodyInfo.image->GetCurrFrameY());
        headInfo.image->Render(hdc, (INT)(headInfo.pos.x), (INT)(headInfo.pos.y), headInfo.image->GetCurrFrameX(), headInfo.image->GetCurrFrameY());
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

    // Debug
    GameObject::Render(hdc);
}

void Player::OnDebug(HDC hdc)
{
    if (debugMode)
    {
        // playerRectangle
        Rectangle(hdc, (INT)(bodyInfo.shape.left), (INT)(bodyInfo.shape.top), (INT)(bodyInfo.shape.right), (INT)(bodyInfo.shape.bottom));
        Ellipse(hdc, (INT)(headInfo.shape.left), (INT)(headInfo.shape.top), (INT)(headInfo.shape.right), (INT)(headInfo.shape.bottom));

        // player.pos
        wsprintf(text, "player.pos.x : %d", (INT)(headInfo.pos.x));
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) - 40), text, (INT)(strlen(text)));
        wsprintf(text, "player.pos.y : %d", (INT)(headInfo.pos.y));
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) - 20), text, (INT)(strlen(text)));
        // MousePointer
        wsprintf(text, "Mouse.PosX : %d", g_ptMouse.x);
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) + 20), text, (INT)(strlen(text)));
        wsprintf(text, "Mouse.PosY : %d", g_ptMouse.y);
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) + 40), text, (INT)(strlen(text)));
        // 기울기
        float slope = (FLOAT)((headInfo.shape.bottom - headInfo.shape.top)) / (FLOAT)((headInfo.shape.right - headInfo.shape.left));
        // section01
        float section01 = headInfo.shape.bottom - (FLOAT)(headInfo.shape.right * slope);
        float section02 = slope * WIN_SIZE_X + section01;
        MoveToEx(hdc, 0, (INT)section01, NULL);
        LineTo(hdc, WIN_SIZE_X, (INT)section02);
        // section02
        section01 = headInfo.shape.top + (FLOAT)(headInfo.shape.right * slope);
        section02 = -(slope * WIN_SIZE_X) + section01;
        MoveToEx(hdc, 0, (INT)section01, NULL);
        LineTo(hdc, WIN_SIZE_X, (INT)section02);
    }
}

void Player::ChangeAnimation()
{
    if (playerDir == MoveDir::UP)
    {
        bodyInfo.image->SetCurrFrameY(BODY_DEFAULT_DIR);
        if (!isFire) 
        { 
            headInfo.image->SetCurrFrameX(HEAD_LOOK_UP);
        }
    }
    if (playerDir == MoveDir::DOWN)
    {
        bodyInfo.image->SetCurrFrameY(BODY_DEFAULT_DIR);
        if (!isFire) 
        { 
            headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
        }
    }
    if (playerDir == MoveDir::RIGHT)
    {
        bodyInfo.image->SetCurrFrameY(BODY_RIGHT_DIR);
        if (!isFire) 
        { 
            headInfo.image->SetCurrFrameX(HEAD_LOOK_RIGHT);
        }
    }
    if (playerDir == MoveDir::LEFT)
    {
        bodyInfo.image->SetCurrFrameY(BODY_LEFT_DIR);
        if (!isFire) 
        { 
            headInfo.image->SetCurrFrameX(HEAD_LOOK_LEFT);
        }
    }

    ++elapsedAnime;
    if (elapsedAnime > 5)
    {
        bodyInfo.image->SetCurrFrameX(bodyInfo.image->GetCurrFrameX() + ADVANCE_FRAME);
        if (bodyInfo.image->GetCurrFrameX() >= MAX_BODY_FRAME_X)
        { 
            bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        }

        elapsedAnime = ZERO;
    }
}

void Player::FireWeapon(int x, int y)
{
    ++loadWeapon;

    float slope = (FLOAT)((headInfo.shape.bottom - headInfo.shape.top)) / (FLOAT)((headInfo.shape.right - headInfo.shape.left));

    float section01 = (FLOAT)(slope * x) + (headInfo.shape.bottom - (FLOAT)(headInfo.shape.right * slope));
    float section02 = (FLOAT)((-slope) * x) + (headInfo.shape.top + (FLOAT)(headInfo.shape.right * slope));

    if (loadWeapon > takeLoadWeapon)
    {
        // section01 보다 클 때 (하, 좌)
        if (y >= section01)
        {
            // 하
            if (y >= section02)
            {
                headInfo.image->SetCurrFrameX(ATTACKINGSIDE_DOWN);
                weaponTear->WeaponFire(MoveDir::DOWN);
            }
            // 좌
            else
            {
                headInfo.image->SetCurrFrameX(ATTACKINGSIDE_LEFT);
                weaponTear->WeaponFire(MoveDir::LEFT);
            }
        }
        // section01 보다 작을 때 (상, 우)
        else
        {
            // 상
            if (y <= section02)
            {
                headInfo.image->SetCurrFrameX(ATTACKINGSIDE_UP);
                weaponTear->WeaponFire(MoveDir::UP);
            }
            // 우
            else
            {
                headInfo.image->SetCurrFrameX(ATTACKINGSIDE_RIGHT);
                weaponTear->WeaponFire(MoveDir::RIGHT);
            }
        }

        loadWeapon = ZERO;
    }
}

void Player::TakeAction()
{
    // 이동키 땠을 때
    if (GET_SINGLETON_KEY->IsOnceKeyUp('W') || GET_SINGLETON_KEY->IsOnceKeyUp('S') || GET_SINGLETON_KEY->IsOnceKeyUp('D') || GET_SINGLETON_KEY->IsOnceKeyUp('A'))
    {
        playerState = ObjectStates::IDLE;
        bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        bodyInfo.image->SetCurrFrameY(BODY_DEFAULT_DIR);

        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 공격키 땠을 때
    if (GET_SINGLETON_KEY->IsOnceKeyUp(VK_LBUTTON))
    {
        playerState = ObjectStates::IDLE;
        isFire = false;
    }
    // 이동키
    if (GET_SINGLETON_KEY->IsStayKeyDown('W'))                               // 상
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::UP;
        bodyInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    else if (GET_SINGLETON_KEY->IsStayKeyDown('S'))                          // 하
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::DOWN;
        bodyInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    if (GET_SINGLETON_KEY->IsStayKeyDown('D'))                               // 우
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::RIGHT;
        bodyInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    else if (GET_SINGLETON_KEY->IsStayKeyDown('A'))                           // 좌
    {
        playerState = ObjectStates::WALK;
        playerDir = MoveDir::LEFT;
        bodyInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();

        Player::ChangeAnimation();
    }
    // 공격키
    if (GET_SINGLETON_KEY->IsStayKeyDown(VK_LBUTTON))
    {
        isFire = true;
        Player::FireWeapon(g_ptMouse.x, g_ptMouse.y);
    }

    // bodyShape
    bodyInfo.shape.left = (LONG)(bodyInfo.pos.x - (bodyInfo.size * DEVIDE_HALF) - ADJUST_SIZE_14);	    // Left
    bodyInfo.shape.top = (LONG)(bodyInfo.pos.y - (bodyInfo.size * DEVIDE_HALF));			            // Top
    bodyInfo.shape.right = (LONG)(bodyInfo.pos.x + (bodyInfo.size * DEVIDE_HALF) + ADJUST_SIZE_14);	    // Right
    bodyInfo.shape.bottom = (LONG)(bodyInfo.pos.y + (bodyInfo.size * DEVIDE_HALF));			            // Bottom
    // headShape
    headInfo.shape.left = (LONG)(headInfo.pos.x - (headInfo.size * DEVIDE_HALF) - ADJUST_SIZE_05);      // Left
    headInfo.shape.top = (LONG)(headInfo.pos.y - (headInfo.size * DEVIDE_HALF));			            // Top
    headInfo.shape.right = (LONG)(headInfo.pos.x + (headInfo.size * DEVIDE_HALF) + ADJUST_SIZE_05);	    // Right
    headInfo.shape.bottom = (LONG)(headInfo.pos.y + (headInfo.size * DEVIDE_HALF));			            // Bottom
}
