#include "MainConfig.h"
#include "Player.h"

#include "Image.h"

void Player::Init()
{
    // playerImg
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:    case ObjectStates::ATTACK:
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
        break;
    }

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - ADJUST_SIZE_30) * DEVIDE_HALF);
    moveSpeed = PLAYER_MOVESPEED;
    elapsedAnime = ZERO;
}

void Player::Release()
{
}

void Player::Update()
{
#ifdef _DEBUG
    GameObject::Update();
#endif
    TakeAction();
    Move();
    BlinkEye();
}

void Player::Render(HDC hdc)
{
    // playerImage
    switch (playerState)
    {
    case ObjectStates::IDLE:    case ObjectStates::WALK:    case ObjectStates::ATTACK:
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

void Player::ApplyBodyFrame(MoveDir moveDir, int bodyFrameY)
{
    if (bodyInfo.moveDir == moveDir)
    {
        bodyInfo.image->SetCurrFrameY(bodyFrameY);
    }
}

void Player::ApplyHeadFrame(MoveDir moveDir, int headFrameX)
{
    if (playerState == ObjectStates::WALK && headInfo.moveDir == moveDir)
    {
        headInfo.image->SetCurrFrameX(headFrameX);
    }
}

void Player::ApplyHeadDir(MoveDir moveDir, int attckFrame)
{
    if (headInfo.image->GetCurrFrameX() == attckFrame)
    {
        headInfo.moveDir = moveDir;
    }
}

void Player::BlinkEye()
{
    ChangeAttackFrame();
    
    isFire = false;
}

void Player::ChangeAnimation()
{
    ChangeBodyFrame();
    ChangeHeadFrame();

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

void Player::ChangeAttackFrame()
{
    ApplyAttackFrame(ATTACKING_UPSIDE, HEAD_LOOK_UP);
    ApplyAttackFrame(ATTACKING_DOWNSIDE, HEAD_LOOK_DOWN);
    ApplyAttackFrame(ATTACKING_LEFTSIDE, HEAD_LOOK_LEFT);
    ApplyAttackFrame(ATTACKING_RIGHTSIDE, HEAD_LOOK_RIGHT);
}

void Player::ChangeBodyFrame()
{
    ApplyBodyFrame(MoveDir::UP, BODY_DEFAULT_DIR);
    ApplyBodyFrame(MoveDir::DOWN, BODY_DEFAULT_DIR);
    ApplyBodyFrame(MoveDir::LEFT, BODY_LEFT_DIR);
    ApplyBodyFrame(MoveDir::RIGHT, BODY_RIGHT_DIR);
}

void Player::ChangeHeadFrame()
{
    if (!ClosedEye())
    {
        ApplyHeadFrame(MoveDir::UP, HEAD_LOOK_UP);
        ApplyHeadFrame(MoveDir::DOWN, HEAD_LOOK_DOWN);
        ApplyHeadFrame(MoveDir::LEFT, HEAD_LOOK_LEFT);
        ApplyHeadFrame(MoveDir::RIGHT, HEAD_LOOK_RIGHT);
    }
}

void Player::ChangeHeadDir()
{
    ApplyHeadDir(MoveDir::UP, ATTACKING_UPSIDE);
    ApplyHeadDir(MoveDir::DOWN, ATTACKING_DOWNSIDE);
    ApplyHeadDir(MoveDir::LEFT, ATTACKING_LEFTSIDE);
    ApplyHeadDir(MoveDir::RIGHT, ATTACKING_RIGHTSIDE);
}

bool Player::ClosedEye()
{
    return headInfo.image->GetCurrFrameX() == 1 || headInfo.image->GetCurrFrameX() == 3 || headInfo.image->GetCurrFrameX() == 5 || headInfo.image->GetCurrFrameX() == 7;
}

void Player::DevideHeadDir(int pointY, int section, int dir1, int dir2)
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
}

void Player::Move()
{
    if (playerState != ObjectStates::IDLE)
    {
        ChangeAnimation();
    }
}

void Player::TakeAction()
{
    // 이동키 땠을 때
    if (Input::GetButtonUp('W') || Input::GetButtonUp('S') || Input::GetButtonUp('D') || Input::GetButtonUp('A'))
    {
        playerState = ObjectStates::IDLE;
        bodyInfo.moveDir = MoveDir::DOWN;
        headInfo.moveDir = MoveDir::DOWN;
        bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        bodyInfo.image->SetCurrFrameY(BODY_DEFAULT_DIR);
        
        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 공격키 땠을 때
    if (Input::GetButtonUp(VK_LBUTTON))
    {
        headInfo.moveDir = MoveDir::DOWN;
        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // 이동키
    if (Input::GetButton('W'))                               // 상
    {
        playerState = ObjectStates::WALK;
        bodyInfo.moveDir = MoveDir::UP;
        headInfo.moveDir = MoveDir::UP;
        bodyInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
    }
    else if (Input::GetButton('S'))                          // 하
    {
        playerState = ObjectStates::WALK;
        bodyInfo.moveDir = MoveDir::DOWN;
        headInfo.moveDir = MoveDir::DOWN;
        bodyInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
    }
    if (Input::GetButton('D'))                               // 우
    {
        playerState = ObjectStates::WALK;
        bodyInfo.moveDir = MoveDir::RIGHT;
        headInfo.moveDir = MoveDir::RIGHT;
        bodyInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
    }
    else if (Input::GetButton('A'))                           // 좌
    {
        playerState = ObjectStates::WALK;
        bodyInfo.moveDir = MoveDir::LEFT;
        headInfo.moveDir = MoveDir::LEFT;
        bodyInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
        headInfo.pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
    }
    // 공격키
    if (Input::GetButton(VK_LBUTTON) && !isFire)
    {
        //playerState = ObjectStates::ATTACK;
        FireWeapon(g_ptMouse.x, g_ptMouse.y);
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

float Player::CalculateSlope(RECT rc)
{
    return (FLOAT)((rc.bottom - rc.top)) / (FLOAT)((rc.right - rc.left));
}
