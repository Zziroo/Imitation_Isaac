#include "MainConfig.h"
#include "ObstacleToolScene.h"

#include "Button.h"
#include "Image.h"
#include "Obstacle.h"

HRESULT ObstacleToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);
	// Main BackGround
	backGroundImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround01.bmp");
	// 그릴 영역 BackGround
	indicativeAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/SampleImage.bmp");
	// Sample BackGround Image
	sampleBackGroundImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround04.bmp");
	// Sample Obstacle
	sampleObstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Obstacle.bmp");

	// Sample Obstacle
	// 초기화
	sampleObstacle.resize(9);
	// Obstacle Type 설정
	EstablishSampleType();
	// 위치 설정
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int index = (r * 3) + c;
			sampleObstacle[index].pos = { 939.0f + (161.0f * c), 349.0f + (161.0f * r) };
		}
	}
	// 선택하기 위한 RECT 설정
	DrawSampleRect(0, 82.0f, 63.0f);		// Item Stand
	DrawSampleRect(1, 84.0f, 84.0f);		// DDong
	DrawSampleRect(2, 80.0f, 80.0f);		// Brick
	DrawSampleRect(3, 75.0f, 78.0f);		// Spider Web
	DrawSampleRect(4, 80.0f, 80.0f);		// Thorn
	DrawSampleRect(5, 84.0f, 81.0f);		// Jar
	DrawSampleRect(6, 101.0f, 107.0f);		// Stone
	DrawSampleRect(7, 84.0f, 129.0f);		// BonFire
	DrawSampleRect(8, 139.0f, 139.0f);		// Slider

	// Obstacle을 받아오기 위한 벡터 초기화
	obstacle.resize(resizeNum);
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		obstacle[i] = new Obstacle;
	}

	// Button
	button = new Button;
	button->Init();

	return S_OK;
}

void ObstacleToolScene::Release()
{
	SAFE_RELEASE(button);
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		SAFE_RELEASE(obstacle[i]);
	}
}

void ObstacleToolScene::Update()
{
	// Debug
	if (Input::GetButtonDown('M'))
	{
		debugMode = !debugMode;
	}

	// SampleObstacleImg를 클릭
	ClickedObstacle();

	// 우클릭 시 장애물의 pos, type이 저장되며 화면에 보여줌
	if (button->GetSelectObstacleButton() == false && clickedSampleObstacle)
	{
		if (Input::GetButtonDown(VK_RBUTTON))
		{
			long posX = g_ptMouse.x;
			long posY = g_ptMouse.y;

			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/ItemStand.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[0].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/DDong.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[1].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Brick.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[2].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/SpiderWeb.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[3].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Thorn.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[4].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Jar.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[5].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Stone.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[6].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Bonfire.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[7].sampleType);
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Slider.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacle[8].sampleType);
			}

			obstacle[storeIndex]->SetObstaclePosX((FLOAT)posX);
			obstacle[storeIndex]->SetObstaclePosY((FLOAT)posY);
			obstacle[storeIndex]->Init();

			++storeIndex;

			// 저장용량이 다 차면 용량을 두 배로 늘려준다.
			if (storeIndex >= resizeNum)
			{
				int originSize = resizeNum;
				resizeNum *= 2;
				obstacle.resize(resizeNum);
				for (size_t i = originSize; i < obstacle.size(); ++i)
				{
					obstacle[i] = new Obstacle;
				}
			}

			clickedSampleObstacle = false;
		}
	}

	// Obstacle Update
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		if (obstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			obstacle[i]->Update();
		}
	}

	// 클릭 해제
	if (Input::GetButtonDown('X'))
	{
		clickedSampleObstacle = false;
	}

	// Button
	button->Update();

	// SampleTile Button을 누르면 tilemapToolScene으로 이동
	if (button->GetSelectSampleTileButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("TilemapTool");
	}
}

void ObstacleToolScene::Render(HDC hdc)
{
	// BackGround
	backGroundImg->Render(hdc);
	// 그릴 때 도움줄 Image
	indicativeAreaImg->TransparentRender(hdc, WIN_SIZE_X * DEVIDE_HALF, WIN_SIZE_Y * DEVIDE_HALF, indicativeAreaImg->GetCurrFrameX(), indicativeAreaImg->GetCurrFrameY(), 150.0f);
	// 그려져야할 영역을 표시
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	for (int r = 0; r < 14; ++r)
	{
		for (int c = 0; c < 26; ++c)
		{
			Rectangle(hdc, 120 + (c * 40), 120 + (r * 40), 120 + ((c + 1) * 40), 120 + ((r + 1) * 40));
		}
	}
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);
	// Obstacle Button을 클릭했을 때
	if (button->GetSelectObstacleButton())
	{
		// Sample BackGround Image
		sampleBackGroundImg->Render(hdc, 1100, 510);
		// Sample Obstacle Image
		sampleObstacleImg->Render(hdc, 1100, 510);
		// Rectangle
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		for (int i = 0; i < 9; ++i)
		{
			Rectangle(hdc, sampleObstacle[i].shape.left, sampleObstacle[i].shape.top, sampleObstacle[i].shape.right, sampleObstacle[i].shape.bottom);
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}
	// 장애물들을 클릭했을 때 이미지만 띄어주기
	if (clickedSampleObstacle)
	{
		obstacleImg->Render(hdc, g_ptMouse.x, g_ptMouse.y, obstacleImg->GetCurrFrameX(), obstacleImg->GetCurrFrameY());
	}
	// Obstacle Render
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		if (obstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			obstacle[i]->Render(hdc);
		}
	}

	// MousePointer
	wsprintf(text, "Mouse.PosX : %d", g_ptMouse.x);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 120, text, (INT)(strlen(text)));
	wsprintf(text, "Mouse.PosY : %d", g_ptMouse.y);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 140, text, (INT)(strlen(text)));

	// Button
	button->Render(hdc);
}

void ObstacleToolScene::ClickedObstacle()
{
	if (button->GetSelectObstacleButton())
	{
		if (PtInRect(&sampleObstacle[0].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/ItemStand.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[1].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/DDong.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[2].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Brick.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[3].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/SpiderWeb.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[4].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Thorn.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[5].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Jar.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[6].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Stone.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[7].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Bonfire.bmp");
			}
		}
		if (PtInRect(&sampleObstacle[8].shape, g_ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Slider.bmp");
			}
		}
	}
}

void ObstacleToolScene::DrawSampleRect(int index, float sizeX, float sizeY)
{
	float posX = sampleObstacle[index].pos.x;
	float posY = sampleObstacle[index].pos.y;

	sampleObstacle[index].shape.left = posX - (sizeX * DEVIDE_HALF);
	sampleObstacle[index].shape.top = posY - (sizeY * DEVIDE_HALF);
	sampleObstacle[index].shape.right = posX + (sizeX * DEVIDE_HALF);
	sampleObstacle[index].shape.bottom = posY + (sizeY * DEVIDE_HALF);
}

void ObstacleToolScene::EstablishSampleType()
{
	sampleObstacle[0].sampleType = ObstacleTypes::ITEMSTAND;
	sampleObstacle[1].sampleType = ObstacleTypes::DDONG;
	sampleObstacle[2].sampleType = ObstacleTypes::BRICK;
	sampleObstacle[3].sampleType = ObstacleTypes::SPIDERWEB;
	sampleObstacle[4].sampleType = ObstacleTypes::THORN;
	sampleObstacle[5].sampleType = ObstacleTypes::JAR;
	sampleObstacle[6].sampleType = ObstacleTypes::STONE;
	sampleObstacle[7].sampleType = ObstacleTypes::BONFIRE;
	sampleObstacle[8].sampleType = ObstacleTypes::SLIDER;
}
