#include "stdafx.h"
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
	sampleObstacleInfo.resize(9);
	// Obstacle Type 설정
	EstablishSampleType();
	// 위치 설정
	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 3; ++c)
		{
			int index = (r * 3) + c;
			sampleObstacleInfo[index].pos = { 939.0f + (161.0f * c), 349.0f + (161.0f * r) };
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

	// Obstacle의 정보를 임시 저장할 공간 초기화
	tempStoreObstacleInfo.resize(resizeNum);

	// 저장할 공간 초기화
	storeObstacle.resize(roomTypeIndex);

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

	for (size_t i = 0; i < loadObstacle.size(); ++i)
	{
		SAFE_RELEASE(loadObstacle[i]);
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

	// Obstacle 그리기
	DrawObstacle();

	// Obstacle Update
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		if (obstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			obstacle[i]->Update();
		}
	}

#ifdef _DEBUG
	// 클릭 해제
	if (Input::GetButtonDown('X'))
	{
		clickedSampleObstacle = false;
	}
#endif

	// Obstacle 저장
	StoreObstacle();

	// Load
	if (button->GetPressLoadButton() && button->GetSelectObstacleButton() == false)
	{
		button->SetPressSaveButton(false);
		// Curse
		if (button->GetSelectCurseRoomButton() && saveIndex[0] > 0)
		{
			Load(0, saveIndex[0] - 1);
		}
		// Item
		if (button->GetSelectItemRoomButton() && saveIndex[1] > 0)
		{
			Load(1, saveIndex[1] - 1);
		}
		// Normal
		if (button->GetSelectNormalRoomButton() && saveIndex[2] > 0)
		{
			Load(2, saveIndex[2] - 1);
		}
	}

	// LoadObstacle
	for (size_t i = 0; i < loadObstacle.size(); ++i)
	{
		if (loadObstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			loadObstacle[i]->Update();
		}
	}

	// Button
	button->Update();

	// SampleTile Button을 누르면 TilemapToolScene으로 이동
	if (button->GetSelectSampleTileButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("TilemapTool");
	}
	// Enemy Button을 누르면 EnemyToolScene으로 이동
	else if (button->GetSelectEnemyBtnButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("EnemyTool");
	}
}

void ObstacleToolScene::Render(HDC hdc)
{
	// BackGround
	backGroundImg->Render(hdc);
	// 그릴 때 도움줄 Image
	indicativeAreaImg->TransparentRender(hdc, (INT)(WIN_SIZE_X * DEVIDE_HALF), (INT)(WIN_SIZE_Y * DEVIDE_HALF), indicativeAreaImg->GetCurrFrameX(), indicativeAreaImg->GetCurrFrameY(), 150.0f);
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

	// Obstacle Render
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		if (obstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			obstacle[i]->Render(hdc);
		}
	}

	// LoadObstacle
	for (size_t i = 0; i < loadObstacle.size(); ++i)
	{
		if (loadObstacle[i]->GetObstacleType() != ObstacleTypes::NONE)
		{
			loadObstacle[i]->Render(hdc);
		}
	}

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
			Rectangle(hdc, sampleObstacleInfo[i].shape.left, sampleObstacleInfo[i].shape.top, sampleObstacleInfo[i].shape.right, sampleObstacleInfo[i].shape.bottom);
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}

	// 장애물들을 클릭했을 때 이미지만 띄어주기
	if (clickedSampleObstacle)
	{
		obstacleImg->Render(hdc, _ptMouse.x, _ptMouse.y, obstacleImg->GetCurrFrameX(), obstacleImg->GetCurrFrameY());
	}

	// MousePointer
	wsprintf(text, "Mouse.PosX : %d", _ptMouse.x);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 120, text, (INT)(strlen(text)));
	wsprintf(text, "Mouse.PosY : %d", _ptMouse.y);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 140, text, (INT)(strlen(text)));

	// Button
	button->Render(hdc);
}

void ObstacleToolScene::ClickedObstacle()
{
	if (button->GetSelectObstacleButton())
	{
		// loadObstacle 초기화
		if (loadObstacle.empty() == false)
		{
			for (size_t i = 0; i < loadObstacle.size(); ++i)
			{
				SAFE_RELEASE(loadObstacle[i]);
			}
			loadObstacle.clear();
		}

		if (PtInRect(&sampleObstacleInfo[0].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/ItemStand.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[1].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/DDong.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[2].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Brick.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[3].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/SpiderWeb.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[4].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Thorn.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[5].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Jar.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[6].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Stone.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[7].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Bonfire.bmp");
			}
		}
		if (PtInRect(&sampleObstacleInfo[8].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleObstacle = true;
				obstacleImg = GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Slider.bmp");
			}
		}
	}
}

void ObstacleToolScene::DrawObstacle()
{
	// 우클릭 시 장애물의 pos, type이 저장되며 화면에 보여줌
	if (button->GetSelectObstacleButton() == false && clickedSampleObstacle)
	{
		if (Input::GetButtonDown(VK_RBUTTON))
		{
			long posX = _ptMouse.x;
			long posY = _ptMouse.y;

			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/ItemStand.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[0].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[0].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/DDong.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[1].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[1].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Brick.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[2].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[2].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/SpiderWeb.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[3].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[3].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Thorn.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[4].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[4].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Jar.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[5].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[5].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Stone.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[6].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[6].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Bonfire.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[7].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[7].sampleType;
			}
			if (obstacleImg == GET_SINGLETON_IMAGE->FindImage("Image/Obstacle/Slider.bmp"))
			{
				obstacle[storeIndex]->SetObstacleType(sampleObstacleInfo[8].sampleType);
				tempStoreObstacleInfo[storeIndex].sampleType = sampleObstacleInfo[8].sampleType;
			}

			obstacle[storeIndex]->SetObstaclePosX((FLOAT)posX);
			obstacle[storeIndex]->SetObstaclePosY((FLOAT)posY);
			obstacle[storeIndex]->Init();

			tempStoreObstacleInfo[storeIndex].pos = { (FLOAT)posX, (FLOAT)posY };

			++storeIndex;

			// 저장용량이 다 차면 용량을 두 배로 늘려준다.
			if (storeIndex >= resizeNum)
			{
				int originSize = resizeNum;
				resizeNum *= 2;
				// Obstacle* 크기 증가
				obstacle.resize(resizeNum);
				// Obstacle* 동적 할당
				for (size_t i = originSize; i < obstacle.size(); ++i)
				{
					obstacle[i] = new Obstacle;
				}

				// tempStoreObstacle 크기 증가
				tempStoreObstacleInfo.resize(resizeNum);
			}

			clickedSampleObstacle = false;
		}
	}
}

void ObstacleToolScene::DrawSampleRect(int index, float sizeX, float sizeY)
{
	float posX = sampleObstacleInfo[index].pos.x;
	float posY = sampleObstacleInfo[index].pos.y;

	sampleObstacleInfo[index].shape.left = (LONG)(posX - (sizeX * DEVIDE_HALF));
	sampleObstacleInfo[index].shape.top = (LONG)(posY - (sizeY * DEVIDE_HALF));
	sampleObstacleInfo[index].shape.right = (LONG)(posX + (sizeX * DEVIDE_HALF));
	sampleObstacleInfo[index].shape.bottom = (LONG)(posY + (sizeY * DEVIDE_HALF));
}

void ObstacleToolScene::EstablishSampleType()
{
	sampleObstacleInfo[0].sampleType = ObstacleTypes::ITEMSTAND;
	sampleObstacleInfo[1].sampleType = ObstacleTypes::DDONG;
	sampleObstacleInfo[2].sampleType = ObstacleTypes::BRICK;
	sampleObstacleInfo[3].sampleType = ObstacleTypes::SPIDERWEB;
	sampleObstacleInfo[4].sampleType = ObstacleTypes::THORN;
	sampleObstacleInfo[5].sampleType = ObstacleTypes::JAR;
	sampleObstacleInfo[6].sampleType = ObstacleTypes::STONE;
	sampleObstacleInfo[7].sampleType = ObstacleTypes::BONFIRE;
	sampleObstacleInfo[8].sampleType = ObstacleTypes::SLIDER;
}

void ObstacleToolScene::InitializeStoreSpace()
{
	resizeNum = 4;
	// tempStoreObstacleInfo clear
	tempStoreObstacleInfo.clear();
	tempStoreObstacleInfo.resize(resizeNum);
	storeIndex = 0;
	// 화면에 보여지는 Obstacle clear()
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		SAFE_RELEASE(obstacle[i]);
	}
	obstacle.clear();
	obstacle.resize(resizeNum);
	for (size_t i = 0; i < obstacle.size(); ++i)
	{
		obstacle[i] = new Obstacle;
	}
}

void ObstacleToolScene::Load(int roomType, int loadIndex)
{
	char loadFileName[MAX_PATH];
	char roomTypeName[32];
	int obstacleCount = 0;
	switch (roomType)
	{
	case 0:
		strcpy_s(roomTypeName, "CURSE");
		obstacleCount = (INT)storeObstacle[0].size();
		break;
	case 1:
		strcpy_s(roomTypeName, "ITEM");
		obstacleCount = (INT)storeObstacle[1].size();
		break;
	case 2:
		strcpy_s(roomTypeName, "NORMAL");
		obstacleCount = (INT)storeObstacle[2].size();
		break;
	default:
		break;
	}

	sprintf_s(loadFileName, "Save/%s%02d_%02d.obstacle", roomTypeName, loadIndex, obstacleCount);

	HANDLE hFile = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD obstacleLoadFileInfo = sizeof(storeObstacleInfo) * obstacleCount;

	DWORD readByte = 0;

	for (size_t i = 0; i < obstacleCount; ++i)
	{
		if (ReadFile(hFile, &storeObstacle[roomType][i], sizeof(storeObstacleInfo), &readByte, NULL) == false)
		{
			switch (roomType)
			{
			case 0:
				MessageBox(_hWnd, "storeObstacle[0] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
				break;
			case 1:
				MessageBox(_hWnd, "storeObstacle[1] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
				break;
			case 2:
				MessageBox(_hWnd, "storeObstacle[2] Obstacle 데이터 로드에 실패! !", "에러", MB_OK);
				break;
			default:
				break;
			}
		}
	}

	if (loadObstacle.size() == 0)
	{
		loadObstacle.resize(obstacleCount);
		switch (roomType)
		{
		case 0:
			for (size_t i = 0; i < loadObstacle.size(); ++i)
			{
				loadObstacle[i] = new Obstacle;
				loadObstacle[i]->SetObstaclePos(storeObstacle[0][i].pos);
				loadObstacle[i]->SetObstacleType(storeObstacle[0][i].sampleType);
				loadObstacle[i]->Init();
			}
			break;
		case 1:
			for (size_t i = 0; i < loadObstacle.size(); ++i)
			{
				loadObstacle[i] = new Obstacle;
				loadObstacle[i]->SetObstaclePos(storeObstacle[1][i].pos);
				loadObstacle[i]->SetObstacleType(storeObstacle[1][i].sampleType);
				loadObstacle[i]->Init();
			}
			break;
		case 2:
			for (size_t i = 0; i < loadObstacle.size(); ++i)
			{
				loadObstacle[i] = new Obstacle;
				loadObstacle[i]->SetObstaclePos(storeObstacle[2][i].pos);
				loadObstacle[i]->SetObstacleType(storeObstacle[2][i].sampleType);
				loadObstacle[i]->Init();
			}
			break;
		default:
			break;
		}
	}

	CloseHandle(hFile);
}

void ObstacleToolScene::Save(int roomType, int saveIndex, int obstacleCount)
{
	char saveFileName[MAX_PATH];
	char roomTypeName[32];

	switch (roomType)
	{
	case 0:
		strcpy_s(roomTypeName, "CURSE");
		break;
	case 1:
		strcpy_s(roomTypeName, "ITEM");
		break;
	case 2:
		strcpy_s(roomTypeName, "NORMAL");
		break;
	}

	sprintf_s(saveFileName, "Save/%s%02d_%02d.obstacle", roomTypeName, saveIndex, obstacleCount);

	HANDLE hFile = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD byteSize = sizeof(storeObstacleInfo) * obstacleCount;

	DWORD writtenByte = 0;

	for (size_t i = 0; i < obstacleCount; ++i)
	{
		if (WriteFile(hFile, &storeObstacle[roomType][i], sizeof(storeObstacleInfo), &writtenByte, NULL) == false)
		{
			switch (roomType)
			{
			case 0:
				MessageBox(_hWnd, "storeObstacle[0] Obstacle 데이터 저장에 실패! !", "에러", MB_OK);
				break;
			case 1:
				MessageBox(_hWnd, "storeObstacle[1] Obstacle 데이터 저장에 실패! !", "에러", MB_OK);
				break;
			case 2:
				MessageBox(_hWnd, "storeObstacle[2] Obstacle 데이터 저장에 실패! !", "에러", MB_OK);
				break;
			default:
				break;
			}
		}
	}

	CloseHandle(hFile);
}

void ObstacleToolScene::StoreObstacle()
{
	// Save Button 클릭 시 storeObstacle에 저장 후 파일 생성
	if (button->GetSelectObstacleButton() == false && clickedSampleObstacle == false)		// ObstacleBtn과 저장할 목록이 없고
	{
		if (button->GetPressSaveButton())													// SaveBtn을 눌렀을 때
		{
			button->SetPressSaveButton(false);
			// 임시 저장 장소에 얼마나 저장됐는지의 변수
			int index = 0;
			for (size_t i = 0; i < tempStoreObstacleInfo.size(); ++i)
			{
				if (tempStoreObstacleInfo[i].sampleType != ObstacleTypes::NONE)
				{
					++index;
				}
			}
			// CurseRoom이 눌려져 있다면 storeObstacle[0]에 저장
			if (button->GetSelectCurseRoomButton())
			{
				StoreCurseRoomObstacle(index);
			}
			// ItemRoom이 눌려져 있다면 storeObstacle[1]에 저장
			if (button->GetSelectItemRoomButton())
			{
				StoreItemRoomObstacle(index);
			}
			// NormalRoom이 눌려져 있다면 storeObstacle[2]에 저장
			if (button->GetSelectNormalRoomButton())
			{
				StoreNormalRoomObstacle(index);
			}
		}
	}
}

void ObstacleToolScene::StoreCurseRoomObstacle(int totalSize)
{
	// index만큼 초기화 시키고
	storeObstacle[0].resize(totalSize);
	for (size_t i = 0; i < storeObstacle[0].size(); ++i)
	{
		storeObstacle[0][i].pos = tempStoreObstacleInfo[i].pos;
		storeObstacle[0][i].sampleType = tempStoreObstacleInfo[i].sampleType;
	}

	// 파일로 저장
	Save(0, saveIndex[0], totalSize);
	++saveIndex[0];

	InitializeStoreSpace();
}

void ObstacleToolScene::StoreItemRoomObstacle(int totalSize)
{
	// index만큼 초기화 시키고
	storeObstacle[1].resize(totalSize);
	for (size_t i = 0; i < storeObstacle[1].size(); ++i)
	{
		storeObstacle[1][i].pos = tempStoreObstacleInfo[i].pos;
		storeObstacle[1][i].sampleType = tempStoreObstacleInfo[i].sampleType;
	}
	// 파일로 저장
	Save(1, saveIndex[1], totalSize);
	++saveIndex[1];

	InitializeStoreSpace();
}

void ObstacleToolScene::StoreNormalRoomObstacle(int totalSize)
{
	// index만큼 초기화 시키고
	storeObstacle[2].resize(totalSize);
	for (size_t i = 0; i < storeObstacle[2].size(); ++i)
	{
		storeObstacle[2][i].pos = tempStoreObstacleInfo[i].pos;
		storeObstacle[2][i].sampleType = tempStoreObstacleInfo[i].sampleType;
	}
	// 파일로 저장
	Save(2, saveIndex[2], totalSize);
	++saveIndex[2];

	InitializeStoreSpace();
}