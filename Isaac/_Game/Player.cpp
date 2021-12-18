#include "MainConfig.h"
#include "Player.h"

#include "Image.h"
#include "WeaponManager.h"

void Player::Init()
{
    // playerImg
    switch (playerState)
    {
    case PlayerStates::IDLE:    case PlayerStates::WALK:    case PlayerStates::ATTACK:
        bodyInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Character/Body.bmp");
        headInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Character/Head.bmp");
        break;
    case PlayerStates::HURT:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Hurt.bmp");
        break;
    case PlayerStates::ITEMPICKUP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/ItemPickUp.bmp");
        break;
    case PlayerStates::JUMP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Jump.bmp");
        break;
    case PlayerStates::STAT:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/Stat.bmp");
        break;
    default:
        break;
    }

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - ADJUST_SIZE_30) * DEVIDE_HALF);
    moveSpeed = PLAYER_MOVESPEED;
    elapsedAnimeCount = ZERO;

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
#endif
    TakeAction();
    BlinkEye();

    // Weapon
    weaponTear->Update();
    if (isFire)
    {
        ++fireDelay;
        if (fireDelay > 50)
        {
            isFire = false;
            fireDelay = 0;
        }
    }
}

void Player::Render(HDC hdc)
{
    // playerImage
    switch (playerState)
    {
    case PlayerStates::IDLE:    case PlayerStates::WALK:    case PlayerStates::ATTACK:
        bodyInfo.image->Render(hdc, (INT)(bodyInfo.pos.x), (INT)(bodyInfo.pos.y), bodyInfo.image->GetCurrFrameX(), bodyInfo.image->GetCurrFrameY());
        headInfo.image->Render(hdc, (INT)(headInfo.pos.x), (INT)(headInfo.pos.y), headInfo.image->GetCurrFrameX(), headInfo.image->GetCurrFrameY());
        break;
    case PlayerStates::HURT:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case PlayerStates::ITEMPICKUP:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case PlayerStates::JUMP:
        otherStateImg->Render(hdc, (INT)(pos.x), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    case PlayerStates::STAT:
        otherStateImg->Render(hdc, (INT)(pos.x + ADJUST_SIZE_09), (INT)(pos.y), otherStateImg->GetCurrFrameX(), otherStateImg->GetCurrFrameY());
        break;
    default:
        break;
    }

    // Weapon
    weaponTear->Render(hdc);

    // Debug
    GameObject::Render(hdc);
}

void Player::OnDebug(HDC hdc)
{
    if (debugMode)
    {
        if (Input::GetButton('M'))
        {
            // Tile
            for (int i = 0; i < (TILE_ROW * TILE_COLUMN); ++i)
            {
                Rectangle(hdc, tile[i].rc.left, tile[i].rc.top, tile[i].rc.right, tile[i].rc.bottom);
            }
        }

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
        float slope = CalculateSlope(headInfo.shape);
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

void Player::ApplyAttackFrame(int attackFrame, int usuallyFrame)
{
    if (headInfo.image->GetCurrFrameX() == attackFrame)
    {
        ++headInfo.blinkEye;
        if (headInfo.blinkEye > 20)
        {
            headInfo.image->SetCurrFrameX(usuallyFrame);
            headInfo.blinkEye = 0;
        }
    }
}

void Player::ApplyBodyFrame(ObjectDir moveDir, int bodyFrameY)
{
    if (bodyInfo.moveDir == moveDir)
    {
        bodyInfo.image->SetCurrFrameY(bodyFrameY);
    }
}

void Player::ApplyHeadFrame(ObjectDir moveDir, int headFrameX)
{
    if (playerState == PlayerStates::WALK && headInfo.moveDir == moveDir)
    {
        headInfo.image->SetCurrFrameX(headFrameX);
    }
}

void Player::ApplyHeadDir(ObjectDir moveDir, int attckFrame)
{
    if (headInfo.image->GetCurrFrameX() == attckFrame)
    {
        headInfo.moveDir = moveDir;
    }
}

void Player::BlinkEye()
{
    ChangeAttackFrame();
}

void Player::ChangeAnimation()
{
    ChangeBodyFrame();
    ChangeHeadFrame();

    ++elapsedAnimeCount;
    if (elapsedAnimeCount > 5)
    {
        bodyInfo.image->SetCurrFrameX(bodyInfo.image->GetCurrFrameX() + ADVANCE_FRAME);
        if (bodyInfo.image->GetCurrFrameX() >= MAX_BODY_FRAME_X)
        { 
            bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        }

        elapsedAnimeCount = ZERO;
    }
}

void Player::ChangeAttackFrame()
{
    ApplyAttackFrame(ATTACKING_UPSIDE, HEAD_LOOK_UP);
    ApplyAttackFrame(ATTACKING_DOWNSIDE, HEAD_LOOK_DOWN);
    ApplyAttackFrame(ATTACKING_LEFTSIDE, HEAD_LOOK_LEFT);
    ApplyAttackFrame(ATTACKING_RIGHTSIDE, HEAD_LOOK_RIGHT);
}

void Player::ChangeBodyFrame()
{
    ApplyBodyFrame(ObjectDir::UP, BODY_DEFAULT_DIR);
    ApplyBodyFrame(ObjectDir::DOWN, BODY_DEFAULT_DIR);
    ApplyBodyFrame(ObjectDir::LEFT, BODY_LEFT_DIR);
    ApplyBodyFrame(ObjectDir::RIGHT, BODY_RIGHT_DIR);
}

void Player::ChangeHeadFrame()
{
    if (!ClosedEye())
    {
        ApplyHeadFrame(ObjectDir::UP, HEAD_LOOK_UP);
        ApplyHeadFrame(ObjectDir::DOWN, HEAD_LOOK_DOWN);
        ApplyHeadFrame(ObjectDir::LEFT, HEAD_LOOK_LEFT);
        ApplyHeadFrame(ObjectDir::RIGHT, HEAD_LOOK_RIGHT);
    }
}

void Player::ChangeHeadDir()
{
    ApplyHeadDir(ObjectDir::UP, ATTACKING_UPSIDE);
    ApplyHeadDir(ObjectDir::DOWN, ATTACKING_DOWNSIDE);
    ApplyHeadDir(ObjectDir::LEFT, ATTACKING_LEFTSIDE);
    ApplyHeadDir(ObjectDir::RIGHT, ATTACKING_RIGHTSIDE);
}

bool Player::ClosedEye()
{
    return headInfo.image->GetCurrFrameX() == 1 || headInfo.image->GetCurrFrameX() == 3 || headInfo.image->GetCurrFrameX() == 5 || headInfo.image->GetCurrFrameX() == 7;
}

void Player::DevideHeadDir(int pointY, float section, int dir1, int dir2)
{
    if (pointY >= section)
    {
        headInfo.image->SetCurrFrameX(dir1);      // 하 , 우
    }
    else
    {
        headInfo.image->SetCurrFrameX(dir2);      // 좌 , 상
    }

    ChangeHeadDir();
}

void Player::FireWeapon(int x, int y)
{
    float slope = CalculateSlope(headInfo.shape);
    float section01 = (FLOAT)(slope * x) + (headInfo.shape.bottom - (FLOAT)(headInfo.shape.right * slope));
    float section02 = (FLOAT)((-slope) * x) + (headInfo.shape.top + (FLOAT)(headInfo.shape.right * slope));

    // section01 보다 클 때 (하, 좌)
    if (y >= section01)
    {
        DevideHeadDir(y, section02, ATTACKING_DOWNSIDE, ATTACKING_LEFTSIDE);
    }
    // section01 보다 작을 때 (상, 우)
    else
    {
        DevideHeadDir(y, section02, ATTACKING_RIGHTSIDE, ATTACKING_UPSIDE);
    }

    isFire = true;
    weaponTear->WeaponFire();
}

void Player::Move()
{
    if (playerState != PlayerStates::IDLE)
    {
        ChangeAnimation();
    }

    POINTFLOAT buffBodyPos = bodyInfo.pos;
    RECT buffBodyShape = bodyInfo.shape;
    POINTFLOAT buffHeadPos = headInfo.pos;
    RECT buffHeadShape = headInfo.shape;

    switch (bodyInfo.moveDir)
    {
    case ObjectDir::UP:
        bodyInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::DOWN:
        bodyInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::LEFT:
        bodyInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::RIGHT:
        bodyInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    default:
        break;
    }

    switch (headInfo.moveDir)
    {
    case ObjectDir::UP:
        headInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::DOWN:
        headInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::LEFT:
        headInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    case ObjectDir::RIGHT:
        headInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        break;
    default:
        break;
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
    // 벽 타일과 부딪혔을 때 이동하지 않게 하기
    for (int i = 0; i < (TILE_ROW * TILE_COLUMN); ++i)
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &tile[i].rc))
        {
            if ((tile[i].terrain == TileTypes::WALL))
            {
                bodyInfo.pos = buffBodyPos;
                bodyInfo.shape = buffBodyShape;
                headInfo.pos = buffHeadPos;
                headInfo.shape = buffHeadShape;
            }
        }
    }

#pragma region DoorStates::OPENED
    // 열린 문과 부딪혔을 때 반대편으로 이동하기
    // 위쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][0].shape))
    {
        // 위쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][0].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][0].img != nullptr)
        {
            enterNextDoor[0] = true;
            headInfo.pos = { 640.0f, 625.0f };
            headInfo.shape = {
                (LONG)(headInfo.pos.x - (PLAYER_HEADSIZE * DEVIDE_HALF) - ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y - (PLAYER_HEADSIZE * DEVIDE_HALF)),
                (LONG)(headInfo.pos.x + (PLAYER_HEADSIZE * DEVIDE_HALF) + ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y + (PLAYER_HEADSIZE * DEVIDE_HALF))
            };
            bodyInfo.pos = { headInfo.pos.x, headInfo.pos.y + +42.5f };
            bodyInfo.shape = {
                (LONG)(bodyInfo.pos.x - (PLAYER_BODYSIZE * DEVIDE_HALF) - ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y - (PLAYER_BODYSIZE * DEVIDE_HALF)),
                (LONG)(bodyInfo.pos.x + (PLAYER_BODYSIZE * DEVIDE_HALF) + ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y + (PLAYER_BODYSIZE * DEVIDE_HALF))
            };
        }
    }
    // 아래쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][1].shape))
    {
        // 아래쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][1].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][1].img != nullptr)
        {
            enterNextDoor[1] = true;
            headInfo.pos = { 640.0f, 95.0f };
            headInfo.shape = {
                (LONG)(headInfo.pos.x - (PLAYER_HEADSIZE * DEVIDE_HALF) - ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y - (PLAYER_HEADSIZE * DEVIDE_HALF)),
                (LONG)(headInfo.pos.x + (PLAYER_HEADSIZE * DEVIDE_HALF) + ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y + (PLAYER_HEADSIZE * DEVIDE_HALF))
            };
            bodyInfo.pos = { headInfo.pos.x, headInfo.pos.y + +42.5f };
            bodyInfo.shape = {
                (LONG)(bodyInfo.pos.x - (PLAYER_BODYSIZE * DEVIDE_HALF) - ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y - (PLAYER_BODYSIZE * DEVIDE_HALF)),
                (LONG)(bodyInfo.pos.x + (PLAYER_BODYSIZE * DEVIDE_HALF) + ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y + (PLAYER_BODYSIZE * DEVIDE_HALF))
            };
        }
    }
    // 왼쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][2].shape) || IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][2].shape))
    {
        // 왼쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][2].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][2].img != nullptr)
        {
            enterNextDoor[2] = true;
            headInfo.pos = { 1100.0f, 380.0f };
            headInfo.shape = {
                (LONG)(headInfo.pos.x - (PLAYER_HEADSIZE * DEVIDE_HALF) - ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y - (PLAYER_HEADSIZE * DEVIDE_HALF)),
                (LONG)(headInfo.pos.x + (PLAYER_HEADSIZE * DEVIDE_HALF) + ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y + (PLAYER_HEADSIZE * DEVIDE_HALF))
            };
            bodyInfo.pos = { headInfo.pos.x, headInfo.pos.y + +42.5f };
            bodyInfo.shape = {
                (LONG)(bodyInfo.pos.x - (PLAYER_BODYSIZE * DEVIDE_HALF) - ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y - (PLAYER_BODYSIZE * DEVIDE_HALF)),
                (LONG)(bodyInfo.pos.x + (PLAYER_BODYSIZE * DEVIDE_HALF) + ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y + (PLAYER_BODYSIZE * DEVIDE_HALF))
            };
        }
    }
    // 오른쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][3].shape) || IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][3].shape))
    {
        // 오른쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][3].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][3].img != nullptr)
        {
            enterNextDoor[3] = true;
            headInfo.pos = { 170.0f, 380.0f };
            headInfo.shape = {
                (LONG)(headInfo.pos.x - (PLAYER_HEADSIZE * DEVIDE_HALF) - ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y - (PLAYER_HEADSIZE * DEVIDE_HALF)),
                (LONG)(headInfo.pos.x + (PLAYER_HEADSIZE * DEVIDE_HALF) + ADJUST_SIZE_05),
                (LONG)(headInfo.pos.y + (PLAYER_HEADSIZE * DEVIDE_HALF))
            };
            bodyInfo.pos = { headInfo.pos.x, headInfo.pos.y + +42.5f };
            bodyInfo.shape = {
                (LONG)(bodyInfo.pos.x - (PLAYER_BODYSIZE * DEVIDE_HALF) - ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y - (PLAYER_BODYSIZE * DEVIDE_HALF)),
                (LONG)(bodyInfo.pos.x + (PLAYER_BODYSIZE * DEVIDE_HALF) + ADJUST_SIZE_14),
                (LONG)(bodyInfo.pos.y + (PLAYER_BODYSIZE * DEVIDE_HALF))
            };
        }
    }
#pragma endregion
#pragma region DoorStates::CLOSED/LOCKED
    // 닫힌 문(잠긴 문)과 부딪혔을 때 이동하기 않게 하기
    // 위쪽 문과 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][0].shape))
    {
        // 위쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][0].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][0].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = buffBodyPos;
            bodyInfo.shape = buffBodyShape;
            headInfo.pos = buffHeadPos;
            headInfo.shape = buffHeadShape;
        }
    }
    // 아래쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][1].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][1].shape))
    {
        // 아래쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][1].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][1].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = buffBodyPos;
            bodyInfo.shape = buffBodyShape;
            headInfo.pos = buffHeadPos;
            headInfo.shape = buffHeadShape;
        }
    }
    // 왼쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][2].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][2].shape))
    {
        // 왼쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][2].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][2].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = buffBodyPos;
            bodyInfo.shape = buffBodyShape;
            headInfo.pos = buffHeadPos;
            headInfo.shape = buffHeadShape;
        }
    }
    // 오른쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][3].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][3].shape))
    {
        // 오른쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][3].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][3].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = buffBodyPos;
            bodyInfo.shape = buffBodyShape;
            headInfo.pos = buffHeadPos;
            headInfo.shape = buffHeadShape;
        }
    }
#pragma endregion
}

void Player::TakeAction()
{
    // 이동키 땠을 때
    if (Input::GetButtonUp('W') || Input::GetButtonUp('S') || Input::GetButtonUp('D') || Input::GetButtonUp('A'))
    {
        playerState = PlayerStates::IDLE;
        bodyInfo.moveDir = ObjectDir::DOWN;
        headInfo.moveDir = ObjectDir::DOWN;
        bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        bodyInfo.image->SetCurrFrameY(BODY_DEFAULT_DIR);
        
        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 공격키 땠을 때
    if (Input::GetButtonUp(VK_LBUTTON))
    {
        headInfo.moveDir = ObjectDir::DOWN;
        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 이동키
    // 우
    if (Input::GetButton('D'))
    {
        playerState = PlayerStates::WALK;
        bodyInfo.moveDir = ObjectDir::RIGHT;
        headInfo.moveDir = ObjectDir::RIGHT;
        Move();
    }
    // 좌
    else if (Input::GetButton('A'))
    {
        playerState = PlayerStates::WALK;
        bodyInfo.moveDir = ObjectDir::LEFT;
        headInfo.moveDir = ObjectDir::LEFT;
        Move();
    }
    // 상
    if (Input::GetButton('W'))
    {
        playerState = PlayerStates::WALK;
        bodyInfo.moveDir = ObjectDir::UP;
        headInfo.moveDir = ObjectDir::UP;
        Move();
    }
    // 하
    else if (Input::GetButton('S'))
    {
        playerState = PlayerStates::WALK;
        bodyInfo.moveDir = ObjectDir::DOWN;
        headInfo.moveDir = ObjectDir::DOWN;
        Move();
    }

    // 공격키
    if (Input::GetButton(VK_LBUTTON) && !isFire)
    {
        playerState = PlayerStates::ATTACK;
        FireWeapon(g_ptMouse.x, g_ptMouse.y);
    }
}

float Player::CalculateSlope(RECT rc)
{
    return (FLOAT)((rc.bottom - rc.top)) / (FLOAT)((rc.right - rc.left));
}
