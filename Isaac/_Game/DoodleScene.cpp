#include "MainConfig.h"
#include "DoodleScene.h"

#include "Image.h"
#include "Obstacle.h"

HRESULT DoodleScene::Init()
{
	sampleObstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/SampleImage.bmp");
	for (int i = 0; i < 9; ++i)
	{
		obstacle[i] = new Obstacle;
	}
	obstacle[0]->SetObstacleType(ObstacleTypes::BONFIRE);
	obstacle[1]->SetObstacleType(ObstacleTypes::BRICK);
	obstacle[2]->SetObstacleType(ObstacleTypes::DDONG);
	obstacle[3]->SetObstacleType(ObstacleTypes::ITEMSTAND);
	obstacle[4]->SetObstacleType(ObstacleTypes::JAR);
	obstacle[5]->SetObstacleType(ObstacleTypes::SLIDER);
	obstacle[6]->SetObstacleType(ObstacleTypes::SPIDERWEB);
	obstacle[7]->SetObstacleType(ObstacleTypes::STONE);
	obstacle[8]->SetObstacleType(ObstacleTypes::THORN);
	for (int i = 0; i < 9; ++i)
	{
		obstacle[i]->SetObstaclePosX(250.0f + (i * 100));
		obstacle[i]->SetObstaclePosY(400.0f);
		obstacle[i]->Init();
	}

	samplePlayerImg = GET_SINGLETON_IMAGE->FindImage("Image/Character/ItemPickUp.bmp");

	return S_OK;
}

void DoodleScene::Release()
{
	for (int i = 0; i < 9; ++i)
	{
		SAFE_RELEASE(obstacle[i]);
	}
}

void DoodleScene::Update()
{
	for (int i = 0; i < 9; ++i)
	{
		obstacle[i]->Update();
	}

	Move();
}

void DoodleScene::Render(HDC hdc)
{
	sampleObstacleImg->Render(hdc);

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	for (int i = 0; i < 9; ++i)
	{
		obstacle[i]->Render(hdc);
	}
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	samplePlayerImg->Render(hdc, pos.x, pos.y);

	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
}

void DoodleScene::Move()
{
	if (Input::GetButton('D'))
	{
		pos.x += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
	}
	if (Input::GetButton('A'))
	{
		pos.x -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
	}
	if (Input::GetButton('W'))
	{
		pos.y -= moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
	}
	else if (Input::GetButton('S'))
	{
		pos.y += moveSpeed * GET_SINGLETON_TIME->GetDeltaTime();
	}

	shape.left = (LONG)(pos.x - (size * DEVIDE_HALF));
	shape.top = (LONG)(pos.y - (size * DEVIDE_HALF) - 10);
	shape.right = (LONG)(pos.x + (size * DEVIDE_HALF));
	shape.bottom = (LONG)(pos.y + (size * DEVIDE_HALF) + 10);
}
