#include "stdafx.h"
#include "Obstacle.h"

#include "Image.h"
#include "PlayerTear.h"

void Obstacle::setNextFrameHelper(int& frame, int maxFrame)
{
	++frame;

	if (frame > maxFrame)
	{
		frame = maxFrame;
	}
}

void Obstacle::Init()
{
	switch (obstacleInfo.type)
	{
	case ObstacleTypes::BONFIRE:							// 이미지의 프레임 X값 : 애니메이션 / 이미지의 프레임 Y값 : 데미지를 입고(충돌) 불이 꺼지는 과정
		obstacleInfo.type = ObstacleTypes::BONFIRE;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Bonfire.bmp");
		objectSize = 68.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, 0.0f, -5.0f, 0.0f, -10.0f);
		obstacleInfo.doDamage = true;
		break;
	case ObstacleTypes::BRICK:
		obstacleInfo.type = ObstacleTypes::BRICK;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Brick.bmp");
		objectSize = 80.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, -10.0f, 0.0f, -10.0f, -35.0f);
		break;
	case ObstacleTypes::DDONG:								// 이미지의 프레임 X값 : 애니메이션
		obstacleInfo.type = ObstacleTypes::DDONG;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/DDong.bmp");
		objectSize = 70.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, -10.0f, 0.0f, -10.0f, 0.0f);
		break;
	case ObstacleTypes::ITEMSTAND:
		obstacleInfo.type = ObstacleTypes::ITEMSTAND;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/ItemStand.bmp");
		objectSize = 82.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, -10.0f, -10.5f, -10.0f, -45.5f);
		obstacleInfo.isExistItem = true;
		break;
	case ObstacleTypes::JAR:
		obstacleInfo.type = ObstacleTypes::JAR;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Jar.bmp");
		objectSize = 84.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, -10.0f, -5.5f, -10.0f, -10.0f);
		break;
	case ObstacleTypes::SLIDER:								// 이미지의 프레임 X값 : 공격 전환(충돌 시 데미지 줌)
		obstacleInfo.type = ObstacleTypes::SLIDER;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Slider.bmp");
		objectSize = 60.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize, 5.0f, 5.0f, 0.0f, -5.0f);
		obstacleInfo.doDamage = false;
		break;
	case ObstacleTypes::SPIDERWEB:
		obstacleInfo.type = ObstacleTypes::SPIDERWEB;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/SpiderWeb.bmp");
		objectSize = 75.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize);
		obstacleInfo.isSlowed = true;
		break;
	case ObstacleTypes::STONE:
		obstacleInfo.type = ObstacleTypes::STONE;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Stone.bmp");
		objectSize = 70.0f;	
		DesignateObstacleShape(pos.x, pos.y, objectSize, -10.0f, 0.0f, -10.0f, -35.0f);
		break;
	case ObstacleTypes::THORN:
		obstacleInfo.type = ObstacleTypes::THORN;
		obstacleInfo.img = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Thorn.bmp");
		objectSize = 80.0f;
		DesignateObstacleShape(pos.x, pos.y, objectSize);
		obstacleInfo.doDamage = true;
		break;
	default:
		break;
	}
}

void Obstacle::Release()
{
}

void Obstacle::Update()
{
	// 애니메이션 변화
	ChangeObstacleAnimation();

	// doDamage 변화
	SwitchDamageToPlayer();

	// Debug
	GameObject::Update();
}

void Obstacle::Render(HDC hdc)
{
	obstacleInfo.img->Render(hdc, (INT)pos.x, (INT)pos.y, frameX, frameY);

	// Debug
	GameObject::Render(hdc);
}

void Obstacle::OnDebug(HDC hdc)
{
#ifdef _DEBUG
	if (debugMode)
	{
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
#endif
}

void Obstacle::ChangeObstacleAnimation()
{
	// Bonfire
	if (obstacleInfo.type == ObstacleTypes::BONFIRE)
	{
		++obstacleInfo.elapsedAnimeCount;
		if (obstacleInfo.elapsedAnimeCount > 11)
		{
			++frameX;
			if (IsMaxFrameX())
			{
				frameX = 0;
			}
			obstacleInfo.elapsedAnimeCount = 0;
		}
	}

	// Slider
	if (obstacleInfo.type == ObstacleTypes::SLIDER)
	{
		++obstacleInfo.elapsedAnimeCount;
		if (obstacleInfo.elapsedAnimeCount > 40)
		{
			frameX = 1;
		}
		if (obstacleInfo.elapsedAnimeCount > 100)
		{
			frameX = 0;
			obstacleInfo.elapsedAnimeCount = 0;
		}
	}
}

void Obstacle::DesignateObstacleShape(POINTFLOAT pos, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	DesignateObstacleShape(pos.x, pos.y, objectSize, adjustSizeLeft, adjustSizeTop, adjustSizeRight, adjustSizeBottom);
}

void Obstacle::DesignateObstacleShape(float posX, float posY, float size, float adjustSizeLeft, float adjustSizeTop, float adjustSizeRight, float adjustSizeBottom)
{
	shape.left = (LONG)(posX - (size * DEVIDE_HALF) - adjustSizeLeft);
	shape.top = (LONG)(posY - (size * DEVIDE_HALF) - adjustSizeTop);
	shape.right = (LONG)(posX + (size * DEVIDE_HALF) + adjustSizeRight);
	shape.bottom = (LONG)(posY + (size * DEVIDE_HALF) + adjustSizeBottom);
}

void Obstacle::SwitchDamageToPlayer()
{
	// Bonfire doDamage 변화
	if (obstacleInfo.type == ObstacleTypes::BONFIRE)
	{
		if (obstacleInfo.img->GetCurrFrameY() == obstacleInfo.img->GetMaxFrameY())
		{
			obstacleInfo.doDamage = false;
		}
	}

	// Slider doDamage 변화
	if (obstacleInfo.type == ObstacleTypes::SLIDER)
	{
		if (obstacleInfo.img->GetCurrFrameX() == 0)
		{
			obstacleInfo.doDamage = false;
		}
		if (obstacleInfo.img->GetCurrFrameX() == 1)
		{
			obstacleInfo.doDamage = true;
		}
	}

}

void Obstacle::SetNextFrameX()
{
	setNextFrameHelper(frameX, obstacleInfo.img->GetMaxFrameX());
}

void Obstacle::SetNextFrameY()
{
	setNextFrameHelper(frameY, obstacleInfo.img->GetMaxFrameY());
}

bool Obstacle::IsMaxFrameX() const
{
	return frameX == obstacleInfo.img->GetMaxFrameX();
}

bool Obstacle::IsMaxFrameY() const
{
	return frameY == obstacleInfo.img->GetMaxFrameY();
}
