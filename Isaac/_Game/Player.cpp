#include "MainConfig.h"
#include "Player.h"

#include "Image.h"
#include "Obstacle.h"

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

    // Hurt ������ �� �ִϸ��̼� ��ȭ
    ChageAnimationHurt();

    // ���� ����
    Invisibility();

    // ���� delay
    WeaponDelay();
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

        // ����
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

void Player::ChageAnimationHurt()
{
    if (otherStateImg != nullptr)
    {
        if (playerState == PlayerStates::HURT)
        {
            otherStateImg->SetCurrFrameX(HURT_IMAGE);
            ++elapsedAnimeCount;

            if (elapsedAnimeCount > 10)
            {
                otherStateImg->SetCurrFrameX(otherStateImg->GetMaxFrameX());
                ++hurtDurationTime;
                elapsedAnimeCount = 0;
            }
            if (hurtDurationTime > 5)
            {
                playerState = PlayerStates::IDLE;
                hurtDurationTime = 0;
            }
        }
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
}

bool Player::ClosedEye()
{
    return headInfo.image->GetCurrFrameX() == 1 || headInfo.image->GetCurrFrameX() == 3 || headInfo.image->GetCurrFrameX() == 5 || headInfo.image->GetCurrFrameX() == 7;
}

void Player::CollideWithDoor(POINTFLOAT bodyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape)
{
#pragma region DoorStates::OPENED
    // ���� ���� �ε����� �� �ݴ������� �̵��ϱ�
    // ���� ���� ���� �κа� ��ġ��
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][UPPER_DOOR].shape))
    {
        // ���� ���� ����������
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
        }
    }
    // �Ʒ��� ���� ���� �κа� ��ġ��
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape))
    {
        // �Ʒ��� ���� ����������
        if (doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::OPENED && doorInfo[0][currRow][currColumn][LOWER_DOOR].img != nullptr)
        {
            enterNextDoor[LOWER_DOOR] = true;
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
    // ���� ���� �Ӹ� �κ� �Ǵ� ���� �κа� ��ġ��
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape))
    {
        // ���� ���� ����������
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
        }
    }
    // ������ ���� �Ӹ� �κ� �Ǵ� ���� �κа� ��ġ��
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape))
    {
        // ������ ���� ����������
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
        }
    }
#pragma endregion

#pragma region DoorStates::CLOSED/LOCKED
    // ���� ��(��� ��)�� �ε����� �� �̵��ϱ� �ʰ� �ϱ�
    // ���� ���� ���� �κ��� ��ġ��
    if (IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][UPPER_DOOR].shape))
    {
        // ���� ���� �������� ������
        if (doorInfo[0][currRow][currColumn][UPPER_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][UPPER_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // �Ʒ��� ���� �Ӹ� �κ��̳� ���� �κ��� ��ġ��
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LOWER_DOOR].shape))
    {
        // �Ʒ��� ���� �������� ������
        if (doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][LOWER_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // ���� ���� �Ӹ� �κ��̳� ���� �κ��� ��ġ��
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][LEFT_DOOR].shape))
    {
        // ���� ���� �������� ������
        if (doorInfo[0][currRow][currColumn][LEFT_DOOR].doorState == DoorStates::CLOSED || doorInfo[0][currRow][currColumn][LEFT_DOOR].doorState == DoorStates::LOCKED)
        {
            bodyInfo.pos = bodyPos;
            bodyInfo.shape = bodyShape;
            headInfo.pos = headPos;
            headInfo.shape = headShape;
        }
    }
    // ������ ���� �Ӹ� �κ��̳� ���� �κ��� ��ġ��
    if (IntersectRect(&colliderRect, &headInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape) || IntersectRect(&colliderRect, &bodyInfo.shape, &doorInfo[0][currRow][currColumn][RIGHT_DOOR].shape))
    {
        // ������ ���� �������� ������
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

void Player::DamagedByDoor(int doorDir, RECT playerShape)
{
    if (isinvincible == false && doorInfo[0][currRow][currColumn][doorDir].img == GET_SINGLETON_IMAGE->FindImage("Image/Door/Curse_Room_Door.bmp"))
    {
        if (IntersectRect(&colliderRect, &playerShape, &doorInfo[0][currRow][currColumn][doorDir].shape))
        {
            playerState = PlayerStates::HURT;
        }
    }
}

void Player::DamagedBySlider()
{
    for (int i = 0; i < obstacleFileInfo[currRow][currColumn].count; ++i)
    {
        RECT obstacleShape = {
            obstacle[0][currRow][currColumn][i]->GetObstacleShape().left - ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetObstacleShape().top - ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetObstacleShape().right + ADJUST_SIZE_10,
            obstacle[0][currRow][currColumn][i]->GetObstacleShape().bottom + ADJUST_SIZE_10
        };
        if (isinvincible == false && obstacle[0][currRow][currColumn][i]->GetObstacleType() == ObstacleTypes::SLIDER && obstacle[0][currRow][currColumn][i]->GetObstacleDamaged())
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                playerState = PlayerStates::HURT;                                       // ���� ���� �ʿ�! ! => �÷��̾� �ε� �Ÿ�.
            }
        }
    }
}

void Player::DamagedByThorn()
{
    for (int i = 0; i < obstacleFileInfo[currRow][currColumn].count; ++i)
    {
        RECT obstacleShape = obstacle[0][currRow][currColumn][i]->GetObstacleShape();
        if (isinvincible == false && obstacle[0][currRow][currColumn][i]->GetObstacleType() == ObstacleTypes::THORN)
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                playerState = PlayerStates::HURT;
            }
        }
    }
}

void Player::DamagedPlayer()
{
    DamagedByDoor(UPPER_DOOR, headInfo.shape);
    DamagedByDoor(LOWER_DOOR, bodyInfo.shape);
    DamagedByDoor(LEFT_DOOR, headInfo.shape);
    DamagedByDoor(RIGHT_DOOR, headInfo.shape);

    DamagedBySlider();
    DamagedByThorn();
}

void Player::DevideHeadDir(int pointY, float section, int dir1, int dir2)
{
    if (pointY >= section)
    {
        headInfo.image->SetCurrFrameX(dir1);      // �� , ��
    }
    else
    {
        headInfo.image->SetCurrFrameX(dir2);      // �� , ��
    }

    ChangeHeadDir();
}

void Player::FireWeapon(int x, int y)
{
    float slope = CalculateSlope(headInfo.shape);
    float section01 = (FLOAT)(slope * x) + (headInfo.shape.bottom - (FLOAT)(headInfo.shape.right * slope));
    float section02 = (FLOAT)((-slope) * x) + (headInfo.shape.top + (FLOAT)(headInfo.shape.right * slope));

    // section01 ���� Ŭ �� (��, ��)
    if (y >= section01)
    {
        DevideHeadDir(y, section02, ATTACKING_DOWNSIDE, ATTACKING_LEFTSIDE);
    }
    // section01 ���� ���� �� (��, ��)
    else
    {
        DevideHeadDir(y, section02, ATTACKING_RIGHTSIDE, ATTACKING_UPSIDE);
    }

    isFire = true;
}

void Player::Invisibility()
{
    if (hurtDurationTime != 0)
    {
        isinvincible = true;
    }
    else
    {
        isinvincible = false;
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
    // �� Ÿ�ϰ� �ε����� �� �̵����� �ʰ� �ϱ�
    CollideWithTilemap(buffPos, buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region DoorCollider
    // ������ �浹 ó��
    CollideWithDoor(buffBodyPos, buffBodyShape, buffHeadPos, buffHeadShape);
    #pragma endregion

    #pragma region Obstacle
    // Obstacle���� �浹 ó��
    for (int i = 0; i < obstacleFileInfo[currRow][currColumn].count; ++i)
    {
        RECT obstacleShape = obstacle[0][currRow][currColumn][i]->GetObstacleShape();
        // Obstacle�� Bonfire�� ��
        if (obstacle[0][currRow][currColumn][i]->GetObstacleType() == ObstacleTypes::BONFIRE && obstacle[0][currRow][currColumn][i]->GetObstacleDamaged())
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                pos.x = buffPos.x;
                pos.y = buffPos.y;
                bodyInfo.pos = buffBodyPos;
                bodyInfo.shape = buffBodyShape;
                headInfo.pos = buffHeadPos;
                headInfo.shape = buffHeadShape;

                playerState = PlayerStates::HURT;
            }
        }
        // Ư�� Obstacle�� �ƴ� ��
        if (obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::BONFIRE && obstacle[0][currRow][currColumn][i]->GetObstacleType() != ObstacleTypes::THORN)
        {
            if (IntersectRect(&colliderRect, &bodyInfo.shape, &obstacleShape))
            {
                bodyInfo.pos = buffBodyPos;
                bodyInfo.shape = buffBodyShape;
                headInfo.pos = buffHeadPos;
                headInfo.shape = buffHeadShape;
            }
        }
    }
    #pragma endregion
}

void Player::TakeAction()
{
    // �̵�Ű ���� ��
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
    // ����Ű ���� ��
    if (Input::GetButtonUp(VK_LBUTTON))
    {
        headInfo.moveDir = ObjectDir::DOWN;
        headInfo.image->SetCurrFrameX(HEAD_LOOK_DOWN);
    }
    // �̵�Ű
    // ��
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
    // ��
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
    // ��
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
    // ��
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

    // ����Ű
    if (Input::GetButton(VK_LBUTTON) && !isFire)
    {
        if (playerState != PlayerStates::HURT)
        {
            playerState = PlayerStates::ATTACK;
            FireWeapon(g_ptMouse.x, g_ptMouse.y);
        }
    }
}

void Player::WeaponDelay()
{
    if (isFire)
    {
        ++fireDelay;
        if (fireDelay > 45)
        {
            isFire = false;
            fireDelay = 0;
        }
    }
}
