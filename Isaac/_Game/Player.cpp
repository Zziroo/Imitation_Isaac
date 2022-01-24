#include "stdafx.h"
#include "Player.h"

#include "BossMonster.h"
#include "Image.h"
#include "NextStageDoor.h"
#include "NormalMonster.h"
#include "Obstacle.h"
#include "PlayerTear.h"

void Player::Init()
{
    ChangeImagePlayerState();

    pos.x = (FLOAT)(headInfo.pos.x);
    pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);
    moveSpeed = PLAYER_MOVESPEED;
    elapsedAnimeCount = ZERO;
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

    BlinkEye();

    DamagedPlayer();

    ChangeImagePlayerState();

    // Hurt 상태일 때 애니메이션 변화
    ChangeAnimationHurt();

    // 무적 상태
    Invisibility();

    // 죽음
    Dead();

    // 장전 delay
    WeaponDelay();

    // NextStage
    CollideWithNextStageDoor();

    ChangeAnimationJunp();
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
    case PlayerStates::HURT: case PlayerStates::DEAD:
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
        wsprintf(text, "Mouse.PosX : %d", _ptMouse.x);
        TextOut(hdc, (INT)((WIN_SIZE_X * DEVIDE_HALF) + 250), (INT)((WIN_SIZE_Y * DEVIDE_HALF) + 20), text, (INT)(strlen(text)));
        wsprintf(text, "Mouse.PosY : %d", _ptMouse.y);
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

void Player::ApplyAnimationAttack(int attackFrame, int usuallyFrame)
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
    ChangeAnimationAttack();
}

float Player::CalculateSlope(RECT rc)
{
    return (FLOAT)((rc.bottom - rc.top)) / (FLOAT)((rc.right - rc.left));
}

void Player::ChangeAnimationAttack()
{
    ApplyAnimationAttack(ATTACKING_UPSIDE, HEAD_LOOK_UP);
    ApplyAnimationAttack(ATTACKING_DOWNSIDE, HEAD_LOOK_DOWN);
    ApplyAnimationAttack(ATTACKING_LEFTSIDE, HEAD_LOOK_LEFT);
    ApplyAnimationAttack(ATTACKING_RIGHTSIDE, HEAD_LOOK_RIGHT);
}

void Player::ChangeAnimationDead()
{
    ++elapsedAnimeCount;
    if (elapsedAnimeCount > 15)
    {
        otherStateImg->SetCurrFrameX(otherStateImg->GetCurrFrameX() + ADVANCE_FRAME);
        if(otherStateImg->GetCurrFrameX() >= otherStateImg->GetMaxFrameX())
        {
            otherStateImg->SetCurrFrameX(otherStateImg->GetMaxFrameX());
            ++gameOverCount;
            if (gameOverCount > 5)
            {
                isGameOver = true;
            }
        }
        elapsedAnimeCount = ZERO;
    }
}

void Player::ChangeAnimationHurt()
{
    if (otherStateImg != nullptr)
    {
        if (playerState == PlayerStates::HURT)
        {
            otherStateImg->SetCurrFrameX(HURT_IMAGE);
            ++elapsedAnimeCount;

            if (elapsedAnimeCount > 10)
            {
                otherStateImg->SetCurrFrameX(otherStateImg->GetMaxFrameX() + BLINK_IMAGE_FRAME);
                ++hurtDurationTime;
                elapsedAnimeCount = ZERO;
            }
            if (hurtDurationTime > 5)
            {
                otherStateImg->SetCurrFrameX(ZERO);
                playerState = PlayerStates::IDLE;
                hurtDurationTime = ZERO;
            }
        }
    }
}

void Player::ChangeAnimationJunp()
{
    if (otherStateImg != nullptr)
    {
        if (playerState == PlayerStates::JUMP)
        {
            ++elapsedAnimeCount;
            if (elapsedAnimeCount > 10)
            {
                otherStateImg->SetCurrFrameX(otherStateImg->GetCurrFrameX() + ADVANCE_FRAME);

                if (otherStateImg->GetCurrFrameX() >= otherStateImg->GetMaxFrameX())
                {
                    otherStateImg->SetCurrFrameX(otherStateImg->GetMaxFrameX() + ADVANCE_FRAME);
                    isGameClear = true;
                }
                
                elapsedAnimeCount = ZERO;
            }
        }
    }
}

void Player::ChangeAnimationWalk()
{
    ChangeBodyFrame();
    ChangeHeadFrame();

    ++bodyInfo.elapsedAnimeCount;
    if (bodyInfo.elapsedAnimeCount > 5)
    {
        bodyInfo.image->SetCurrFrameX(bodyInfo.image->GetCurrFrameX() + ADVANCE_FRAME);
        if (bodyInfo.image->GetCurrFrameX() >= MAX_BODY_FRAME_X)
        {
            bodyInfo.image->SetCurrFrameX(START_BODY_FRAME_X);
        }

        bodyInfo.elapsedAnimeCount = ZERO;
    }
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
    if (ClosedEye() == false)
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

void Player::ChangeImagePlayerState()
{
    // playerImg
    switch (playerState)
    {
    case PlayerStates::IDLE:    case PlayerStates::WALK:    case PlayerStates::ATTACK:
        bodyInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Player/Body.bmp");
        headInfo.image = GET_SINGLETON_IMAGE->FindImage("Image/Player/Head.bmp");
        break;
    case PlayerStates::HURT: case PlayerStates::DEAD:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Player/Hurt.bmp");
        break;
    case PlayerStates::ITEMPICKUP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Player/ItemPickUp.bmp");
        break;
    case PlayerStates::JUMP:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Player/Jump.bmp");
        break;
    case PlayerStates::STAT:
        otherStateImg = GET_SINGLETON_IMAGE->FindImage("Image/Player/Stat.bmp");
        break;
    default:
        break;
    }
}

bool Player::ClosedEye()
{
    return headInfo.image->GetCurrFrameX() == 1 || headInfo.image->GetCurrFrameX() == 3 || headInfo.image->GetCurrFrameX() == 5 || headInfo.image->GetCurrFrameX() == 7;
}

void Player::CollideWithBossMonster(POINTFLOAT buffPos, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    RECT bossMonsterShape = bossMonster->GetBossMonsterShape();
    if (isInvincible == false && bossMonster->GetBossMonsterState() != MonsterStates::DEAD && ((IntersectRect(&colliderRect, &bodyInfo.shape, &bossMonsterShape)) || (IntersectRect(&colliderRect, &headInfo.shape, &bossMonsterShape))))
    {
        if (playerState != PlayerStates::HURT)
        {
            --playerHP;
        }

        if (playerHP <= 0)
        {
            playerState = PlayerStates::DEAD;
        }
        else
        {
            playerState = PlayerStates::HURT;
        }

        pos.x = buffPos.x;
        pos.y = buffPos.y;
        bodyInfo.pos = bodyPos;
        bodyInfo.shape = bodyShape;
        headInfo.pos = headPos;
        headInfo.shape = headShape;
    }
}

void Player::CollideWithDDong(int obstacleIndex, RECT obstacleShape, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    if (obstacle[0][currRow][currColumn][obstacleIndex]->GetObstacleType() == ObstacleTypes::DDONG)
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
}

void Player::CollideWithDoor(POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
#pragma region DoorStates::OPENED
    // 열린 문과 부딪혔을 때 반대편으로 이동하기
    // 위쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][UPPER_DOOR].shape))
    {
        playerTear->ExtinctWeapon();
        // 위쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][UPPER_DOOR].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][UPPER_DOOR].img != nullptr)
        {
            enterNextDoor[UPPER_DOOR] = true;
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
            pos.x = (FLOAT)(headInfo.pos.x);
            pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);
        }
    }
    // 아래쪽 문이 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape))
    {
        playerTear->ExtinctWeapon();
        // 아래쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][LOWER_DOOR].img != nullptr)
        {
            enterNextDoor[LOWER_DOOR] = true;
            headInfo.pos = { 640.0f, 120.0f };
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
            pos.x = (FLOAT)(headInfo.pos.x);
            pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);
        }
    }
    // 왼쪽 문이 머리 부분 또는 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape))
    {
        playerTear->ExtinctWeapon();
        // 왼쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][LEFT_DOOR].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][LEFT_DOOR].img != nullptr)
        {
            enterNextDoor[LEFT_DOOR] = true;
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
            pos.x = (FLOAT)(headInfo.pos.x);
            pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);
        }
    }
    // 오른쪽 문이 머리 부분 또는 몸통 부분과 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape))
    {
        playerTear->ExtinctWeapon();
        // 오른쪽 문이 열려있으면
        if (doorInfo[0][currRow][currColumn][RIGHT_DOOR].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][RIGHT_DOOR].img != nullptr)
        {
            enterNextDoor[RIGHT_DOOR] = true;
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
            pos.x = (FLOAT)(headInfo.pos.x);
            pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);
        }
    }
#pragma endregion

#pragma region DoorStates::CLOSED/LOCKED
    // 닫힌 문(잠긴 문)과 부딪혔을 때 이동하기 않게 하기
    // 위쪽 문과 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][UPPER_DOOR].shape))
    {
        // 위쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][UPPER_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][UPPER_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // 아래쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape))
    {
        // 아래쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // 왼쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape))
    {
        // 왼쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][LEFT_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][LEFT_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // 오른쪽 문이 머리 부분이나 몸통 부분이 겹치고
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape))
    {
        // 오른쪽 문이 열려있지 않으면
        if (doorInfo[0][currRow][currColumn][RIGHT_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][RIGHT_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
#pragma endregion
}

void Player::CollideWithNextStageDoor()
{
    RECT nextStageDoorShape = nextStageDoor->GetShape();

    if ((currColumn == bossColumn && currRow == bossRow) && nextStageDoor->GetOpenNextStageDoor())
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &nextStageDoorShape) || IntersectRect(&colliderRect, &bodyInfo.shape, &nextStageDoorShape))
        {
            pos = nextStageDoor->GetPos();

            playerState = PlayerStates::JUMP;

            ChangeImagePlayerState();
        }
    }
}

void Player::CollideWithNormalMonster(POINTFLOAT buffPos, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    for (size_t i = 0; i < normalMonster[0][currRow][currColumn].size(); ++i)
    {
        RECT normalMonsterShape = normalMonster[0][currRow][currColumn][i]->GetNormalMonsterShape();
        if (normalMonster[0][currRow][currColumn][i]->GetNormalMonsterType() != NormalMonsterTypes::FLY)
        {
            if (isInvincible == false && (IntersectRect(&colliderRect, &bodyInfo.shape, &normalMonsterShape) || IntersectRect(&colliderRect, &headInfo.shape, &normalMonsterShape)))
            {
                if (playerState != PlayerStates::HURT)
                {
                    --playerHP;
                }

                if (playerHP <= 0)
                {
                    playerState = PlayerStates::DEAD;
                }
                else
                {
                    playerState = PlayerStates::HURT;
                }

                pos.x = buffPos.x;
                pos.y = buffPos.y;
                bodyInfo.pos = bodyPos;
                bodyInfo.shape = bodyShape;
                headInfo.pos = headPos;
                headInfo.shape = headShape;
            }
        }

        if (IntersectRect(&colliderRect, &bodyInfo.shape, &normalMonsterShape) || IntersectRect(&colliderRect, &headInfo.shape, &normalMonsterShape))
        {
            pos.x = buffPos.x;
            pos.y = buffPos.y;
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
}

void Player::CollideWithObstacle(POINTFLOAT buffPos, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    // Obstacle과의 충돌 처리
    for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
    {
        RECT obstacleShape = obstacle[0][currRow][currColumn][i]->GetShape();

        // Obstacle이 Bonfire일 때
        DamagedByBonfire((INT)i, obstacleShape, buffPos, bodyPos, bodyShape, headPos, headShape);

        // Obstacle이 DDong일 때
        CollideWithDDong((INT)i, obstacleShape, bodyPos, bodyShape, headPos, headShape);

        // Obstacle이 Slider일 때
        CollideWithSlider((INT)i, obstacleShape, bodyPos, bodyShape, headPos, headShape);

        // 특정 Obstacle이 아닐 때
        if (obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::BONFIRE && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::DDONG && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::SLIDER && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::THORN)
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape) || IntersectRect(&colliderRect, &headInfo.shape, &obstacleShape))
            {
                bodyInfo.pos = bodyPos;
                bodyInfo.shape = bodyShape;
                headInfo.pos = headPos;
                headInfo.shape = headShape;
            }
        }
    }
}

void Player::CollideWithSlider(int obstacleIndex, RECT obstacleShape, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    if (obstacle[0][currRow][currColumn][obstacleIndex]->GetObstacleType() == ObstacleTypes::SLIDER)
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
}

void Player::CollideWithTilemap(POINTFLOAT buffPos, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    for (int i = 0; i < (TILE_ROW * TILE_COLUMN); ++i)
    {
        if (tile[i].terrain == TileTypes::WALL && IntersectRect(&colliderRect, &bodyInfo.shape, &tile[i].rc))
        {
            pos.x = buffPos.x;
            pos.y = buffPos.y;
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
}

void Player::DamagedByBonfire(int obstacleIndex, RECT obstacleShape, POINTFLOAT buffPos, POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
    if (obstacle[0][currRow][currColumn][obstacleIndex]->GetObstacleType() == ObstacleTypes::BONFIRE && obstacle[0][currRow][currColumn][obstacleIndex]->GetObstacleDamaged())
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape) || IntersectRect(&colliderRect, &headInfo.shape, &obstacleShape))
        {
            if (playerState != PlayerStates::HURT)
            {
                --playerHP;
            }

            if (playerHP <= 0)
            {
                playerState = PlayerStates::DEAD;
            }
            else
            {
                playerState = PlayerStates::HURT;
            }

            pos.x = buffPos.x;
            pos.y = buffPos.y;
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
}

void Player::DamagedByDoor()
{
    if (isInvincible == false && doorInfo[0][currRow][currColumn][UPPER_DOOR].img == GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp"))
    {
        if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][UPPER_DOOR].shape))
        {
            if (playerState != PlayerStates::HURT)
            {
                playerHP -= 2;
            }

            if (playerHP <= 0)
            {
                playerState = PlayerStates::DEAD;
            }
            else
            {
                playerState = PlayerStates::HURT;
            }
        }
    }
    if (isInvincible == false && doorInfo[0][currRow][currColumn][LOWER_DOOR].img == GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp"))
    {
        if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape))
        {
            if (playerState != PlayerStates::HURT)
            {
                playerHP -= 2;
            }

            if (playerHP <= 0)
            {
                playerState = PlayerStates::DEAD;
            }
            else
            {
                playerState = PlayerStates::HURT;
            }
        }
    }
    if (isInvincible == false && doorInfo[0][currRow][currColumn][LEFT_DOOR].img == GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp"))
    {
        if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape))
        {
            if (playerState != PlayerStates::HURT)
            {
                playerHP -= 2;
            }

            if (playerHP <= 0)
            {
                playerState = PlayerStates::DEAD;
            }
            else
            {
                playerState = PlayerStates::HURT;
            }
        }
    }
    if (isInvincible == false && doorInfo[0][currRow][currColumn][RIGHT_DOOR].img == GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp"))
    {
        if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape))
        {
            if (playerState != PlayerStates::HURT)
            {
                playerHP -= 2;
            }

            if (playerHP <= 0)
            {
                playerState = PlayerStates::DEAD;
            }
            else
            {
                playerState = PlayerStates::HURT;
            }
        }
    }
}

void Player::DamagedBySlider()
{
    for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
    {
        RECT obstacleShape = {
            obstacle[0][currRow][currColumn][i]->GetShape().left - ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetShape().top - ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetShape().right + ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetShape().bottom + ADJUST_SIZE_10
        };

        if (isInvincible == false && obstacle[0][currRow][currColumn][i]->GetObstacleType() == ObstacleTypes::SLIDER && obstacle[0][currRow][currColumn][i]->GetObstacleDamaged())
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                if (playerState != PlayerStates::HURT)
                {
                    playerHP -= 2;
                }
                playerState = PlayerStates::HURT;
            }
        }
    }
}

void Player::DamagedByThorn()
{
    for (size_t i = 0; i < obstacle[0][currRow][currColumn].size(); ++i)
    {
        RECT obstacleShape = obstacle[0][currRow][currColumn][i]->GetShape();
        if (isInvincible == false && obstacle[0][currRow][currColumn][i]->GetObstacleType() == ObstacleTypes::THORN)
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                if (playerState != PlayerStates::HURT)
                {
                    --playerHP;
                }

                if (playerHP <= 0)
                {
                    playerState = PlayerStates::DEAD;
                }
                else
                {
                    playerState = PlayerStates::HURT;
                }
            }
        }
    }
}

void Player::DamagedPlayer()
{
    DamagedByDoor();

    DamagedBySlider();
    DamagedByThorn();
}

void Player::Dead()
{
    if (playerState == PlayerStates::DEAD)
    {
        ChangeAnimationDead();
    }
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

    isFireTear = true;
    playerTear->Fire();
}

void Player::Invisibility()
{
    if (hurtDurationTime != 0)
    {
        isInvincible = true;
    }
    else
    {
        isInvincible = false;
    }
}

void Player::Move()
{
    if (playerState != PlayerStates::IDLE)
    {
        ChangeAnimationWalk();
    }

    POINTFLOAT  buffBodyPos = bodyInfo.pos;
    RECT        buffBodyShape = bodyInfo.shape;
    POINTFLOAT  buffHeadPos = headInfo.pos;
    RECT        buffHeadShape = headInfo.shape;
    POINTFLOAT  buffPos = { pos.x, pos.y };

    switch (bodyInfo.moveDir)
    {
    case ObjectDir::UP:
        bodyInfo.pos.y -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::DOWN:
        bodyInfo.pos.y += moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::LEFT:
        bodyInfo.pos.x -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::RIGHT:
        bodyInfo.pos.x += moveSpeed * Timer::GetDeltaTime();
        break;
    default:
        break;
    }

    switch (headInfo.moveDir)
    {
    case ObjectDir::UP:
        headInfo.pos.y -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::DOWN:
        headInfo.pos.y += moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::LEFT:
        headInfo.pos.x -= moveSpeed * Timer::GetDeltaTime();
        break;
    case ObjectDir::RIGHT:
        headInfo.pos.x += moveSpeed * Timer::GetDeltaTime();
        break;
    default:
        break;
    }

    pos.x = (FLOAT)(headInfo.pos.x);
    pos.y = (FLOAT)((headInfo.pos.y + bodyInfo.pos.y - ADJUST_SIZE_30) * DEVIDE_HALF);

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

    #pragma region TilemapCollider
    // 벽 타일과 부딪혔을 때 이동하지 않게 하기
    CollideWithTilemap(buffPos, buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region DoorCollider
    // 문과의 충돌 처리
    CollideWithDoor(buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region ObstacleCollider
    // 장애물과의 충돌 처리
    CollideWithObstacle(buffPos, buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region NormalMonsterCollider
    // Normal Monster와의 충돌 처리
    CollideWithNormalMonster(buffPos, buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region BossMonsterCollider
    if (currColumn == bossColumn && currRow == bossRow)
    {
        CollideWithBossMonster(buffPos, buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    }
    #pragma endregion
}

void Player::TakeAction()
{
    // DEAD 상태일 때 활동 X
    if (playerState == PlayerStates::DEAD)
    {
        return;
    }

    // 이동키 땠을 때
    if (Input::GetButtonUp('W') || Input::GetButtonUp('S') || Input::GetButtonUp('D') || Input::GetButtonUp('A'))
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::IDLE;
        }
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
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::WALK;
        }
        bodyInfo.moveDir = ObjectDir::RIGHT;
        headInfo.moveDir = ObjectDir::RIGHT;
        Move();
    }
    // 좌
    else if (Input::GetButton('A'))
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::WALK;
        }
        bodyInfo.moveDir = ObjectDir::LEFT;
        headInfo.moveDir = ObjectDir::LEFT;
        Move();
    }
    // 상
    if (Input::GetButton('W'))
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::WALK;
        }
        bodyInfo.moveDir = ObjectDir::UP;
        headInfo.moveDir = ObjectDir::UP;
        Move();
    }
    // 하
    else if (Input::GetButton('S'))
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::WALK;
        }
        bodyInfo.moveDir = ObjectDir::DOWN;
        headInfo.moveDir = ObjectDir::DOWN;
        Move();
    }

    // 공격키
    if (Input::GetButton(VK_LBUTTON) && !isFireTear)
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::ATTACK;
            FireWeapon(_ptMouse.x, _ptMouse.y);
        }
    }
}

void Player::WeaponDelay()
{
    if (isFireTear)
    {
        ++fireDelay;
        if (fireDelay > 45)
        {
            isFireTear = false;
            fireDelay = 0;
        }
    }
}
