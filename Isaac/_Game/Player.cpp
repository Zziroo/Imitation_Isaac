#include "MainConfig.h"
#include "Player.h"

#include "Image.h"

void Player::Init()
{
    Player::FindIamge();

    pos.x = (FLOAT)(PLAYER_HEAD_POS_X);
    pos.y = (FLOAT)((PLAYER_HEAD_POS_Y + PLAYER_BODY_POS_Y - 30) * 0.5f);

    moveSpeed = 100.0f;

    elapsedAnime = 0;
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
}

void Player::Update()
{
    Player::PressInputKey();
}

void Player::Render(HDC hdc)
{
    // playerRectangle
    Rectangle(hdc, (INT)(player.bodyShape.left), (INT)(player.bodyShape.top), (INT)(player.bodyShape.right), (INT)(player.bodyShape.bottom));
    Ellipse(hdc, (INT)(player.headShape.left), (INT)(player.headShape.top), (INT)(player.headShape.right), (INT)(player.headShape.bottom));

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
}

void Player::PressInputKey()
{
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

    if (GETSINGLETON_KEY->IsOnceKeyUp('W') || GETSINGLETON_KEY->IsOnceKeyUp('S') || GETSINGLETON_KEY->IsOnceKeyUp('D') || GETSINGLETON_KEY->IsOnceKeyUp('A'))
    {
        playerState = ObjectStates::IDLE;
        bodyImg->SetCurrFrameX(0);
        bodyImg->SetCurrFrameY(0);

        headImg->SetCurrFrameX(0);
    }
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
    if (playerDir == MoveDir::LEFT)
    {
        bodyImg->SetCurrFrameY(2);
        headImg->SetCurrFrameX(6);
    }
    if (playerDir == MoveDir::RIGHT)
    {
        bodyImg->SetCurrFrameY(1);
        headImg->SetCurrFrameX(2);
    }

    bodyImg->SetCurrFrameX(bodyImg->GetCurrFrameX() + 1);
    if (bodyImg->GetCurrFrameX() >= MAX_BODY_FRAME) { bodyImg->SetCurrFrameX(0); }
}
