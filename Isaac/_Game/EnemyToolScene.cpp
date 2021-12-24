#include "stdafx.h"
#include "EnemyToolScene.h"

#include "Button.h"
#include "Image.h"
#include "NormalMonster.h"

HRESULT EnemyToolScene::Init()
{
	SetWindowSize(TILEMAP_SIZE_X, TILEMAP_SIZE_Y);
	// Main BackGround
	backGroundImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround01.bmp");
	// 그릴 영역 BackGround
	indicativeAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/SampleImage.bmp");
	// Sample BackGround Image
	sampleBackGroundImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround04.bmp");
	// Sample Normal Monster
	sampleNormalMonsterImg = GET_SINGLETON_IMAGE->FindImage("Image/Monster/NormalMonster.bmp");

	// Sample Normal Monster
	sampleNormalMonsterInfo.resize(3);
	// Normal Monster Type 설정
	EstablishSampleType();
	// 위치 설정
	for (int c = 0; c < 3; ++c)
	{
		sampleNormalMonsterInfo[c].pos = { 886.0f + (64.0f * c), 300.0f };
	}
	// 선택하기 위한 RECT 설정
	DrawSampleRect(0, 38.0f, 20.0f);	// Fly
	DrawSampleRect(1, 38.0f, 20.0f);	// AttackFly
	DrawSampleRect(2, 38.0f, 38.0f);	// Pooter

	// Normal Monster를 받아오기 위한 벡터 초기화
	normalMonster.resize(resizeNum);
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		normalMonster[i] = new NormalMonster;
	}

	// NormalMonster의 정보를 임시 저장할 공간 초기화
	tempStoreNormalMonsterInfo.resize(resizeNum);

	// Button
	button = new Button;
	button->Init();

	return S_OK;
}

void EnemyToolScene::Release()
{
	SAFE_RELEASE(button);

	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		SAFE_RELEASE(normalMonster[i]);
	}

	for (size_t i = 0; i < loadNormalMonster.size(); ++i)
	{
		SAFE_RELEASE(loadNormalMonster[i]);
	}
}

void EnemyToolScene::Update()
{
	// Debug
	if (Input::GetButtonDown('M'))
	{
		debugMode = !debugMode;
	}

	// NormalMonsterImg를 클릭
	ClickedNormalMonster();

	// NormalMonster 그리기
	DrawNormalMonster();

	// NormalMonster Update
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		if (normalMonster[i]->GetNormalMonsterType() != NormalMonsterTypes::NONE)
		{
			normalMonster[i]->Update();
		}
	}

#ifdef _DEBUG
	// 클릭 해제
	if (Input::GetButtonDown('X'))
	{
		clickedSampleNormalMonster = false;
	}
#endif

	// NormalMonster 저장
	StoreNormalMonster();

	// Load
	if (button->GetPressLoadButton() && button->GetSelectEnemyBtnButton() == false)
	{
		button->SetPressLoadButton(false);
		int loadIndex = saveIndex - 1;
		Load(loadIndex, (INT)storeNormalMonster.size());
	}

	// LoadNormalMonster
	for (size_t i = 0; i < loadNormalMonster.size(); ++i)
	{
		if (loadNormalMonster[i]->GetNormalMonsterType() != NormalMonsterTypes::NONE)
		{
			loadNormalMonster[i]->Update();								// 문제 발생! ! => 왜 4의 배수로 몬스터가 있으면 멈춰 있는지 모르겠습니다.
		}
	}

	// Button
	button->Update();

	// SampleTile Button을 누르면 TilemapToolScene으로 이동
	if (button->GetSelectSampleTileButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("TilemapTool");
	}
	// Obstacle Button을 누르면 ObstacleToolScene으로 이동
	else if (button->GetSelectObstacleButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("ObstacleTool");
	}
}

void EnemyToolScene::Render(HDC hdc)
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

	// NormalMonster Render
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		if (normalMonster[i]->GetNormalMonsterType() != NormalMonsterTypes::NONE)
		{
			normalMonster[i]->Render(hdc);
		}
	}

	// LoadNormalMonster Render
	for (size_t i = 0; i < loadNormalMonster.size(); ++i)
	{
		if (loadNormalMonster[i]->GetNormalMonsterType() != NormalMonsterTypes::NONE)
		{
			loadNormalMonster[i]->Render(hdc);
		}
	}

	// Enemy Button을 클릭했을 때
	if (button->GetSelectEnemyBtnButton())
	{
		// Sample BackGround Image
		sampleBackGroundImg->Render(hdc, 1100, 510);
		// Sample Normal Monster Image
		sampleNormalMonsterImg->Render(hdc, 950, 300);
		// Rectangle
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		for (int i = 0; i < 3; ++i)
		{
			Rectangle(hdc, sampleNormalMonsterInfo[i].shape.left, sampleNormalMonsterInfo[i].shape.top, sampleNormalMonsterInfo[i].shape.right, sampleNormalMonsterInfo[i].shape.bottom);
		}
		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);
	}

	// Normal Monster를 클릭했을 때 이미지만 띄어주기
	if (clickedSampleNormalMonster)
	{
		normalMonsterImg->Render(hdc, _ptMouse.x, _ptMouse.y, normalMonsterImg->GetCurrFrameX(), normalMonsterImg->GetCurrFrameY());
	}

	// MousePointer
	wsprintf(text, "Mouse.PosX : %d", _ptMouse.x);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 120, text, (INT)(strlen(text)));
	wsprintf(text, "Mouse.PosY : %d", _ptMouse.y);
	TextOut(hdc, (TILEMAP_SIZE_X - 250), 140, text, (INT)(strlen(text)));

	// Button
	button->Render(hdc);
}

void EnemyToolScene::ClickedNormalMonster()
{
	if (button->GetSelectEnemyBtnButton())
	{
		//loadNormalMonster 초기화
		if (loadNormalMonster.empty() == false)
		{
			for (size_t i = 0; i < loadNormalMonster.size(); ++i)
			{
				SAFE_RELEASE(loadNormalMonster[i]);
			}
			loadNormalMonster.clear();
		}

		if (PtInRect(&sampleNormalMonsterInfo[0].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleNormalMonster = true;
				normalMonsterImg = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp");
			}
		}
		if (PtInRect(&sampleNormalMonsterInfo[1].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleNormalMonster = true;
				normalMonsterImg = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Attack_Fly.bmp");
			}
		}
		if (PtInRect(&sampleNormalMonsterInfo[2].shape, _ptMouse))
		{
			if (Input::GetButtonDown(VK_LBUTTON))
			{
				clickedSampleNormalMonster = true;
				normalMonsterImg = GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp");
			}
		}
	}
}

void EnemyToolScene::DrawNormalMonster()
{
	// 우클릭 시 NormalMonster의 pos, type이 저장되며 화면에 보여줌
	if (button->GetSelectEnemyBtnButton() == false && clickedSampleNormalMonster)
	{
		if (Input::GetButtonDown(VK_RBUTTON))
		{
			long posX = _ptMouse.x;
			long posY = _ptMouse.y;

			if (normalMonsterImg == GET_SINGLETON_IMAGE->FindImage("Image/Monster/Fly.bmp"))
			{
				normalMonster[storeIndex]->SetNormalMonsterType(sampleNormalMonsterInfo[0].sampleType);
				tempStoreNormalMonsterInfo[storeIndex].sampleType = sampleNormalMonsterInfo[0].sampleType;
			}
			if (normalMonsterImg == GET_SINGLETON_IMAGE->FindImage("Image/Monster/Attack_Fly.bmp"))
			{
				normalMonster[storeIndex]->SetNormalMonsterType(sampleNormalMonsterInfo[1].sampleType);
				tempStoreNormalMonsterInfo[storeIndex].sampleType = sampleNormalMonsterInfo[1].sampleType;
			}
			if (normalMonsterImg == GET_SINGLETON_IMAGE->FindImage("Image/Monster/Pooter_Idle.bmp"))
			{
				normalMonster[storeIndex]->SetNormalMonsterType(sampleNormalMonsterInfo[2].sampleType);
				tempStoreNormalMonsterInfo[storeIndex].sampleType = sampleNormalMonsterInfo[2].sampleType;
			}

			normalMonster[storeIndex]->SetNormalMonsterPosX((FLOAT)posX);
			normalMonster[storeIndex]->SetNormalMonsterPosY((FLOAT)posY);
			normalMonster[storeIndex]->Init();

			tempStoreNormalMonsterInfo[storeIndex].pos = { (FLOAT)posX, (FLOAT)posY };

			++storeIndex;

			// 저장용량이 다 차면 용량을 두 배로 늘려준다.
			if (storeIndex >= resizeNum)
			{
				int originSize = resizeNum;
				resizeNum *= 2;
				// NormalMonster* 크기 증가
				normalMonster.resize(resizeNum);
				// NormalMonster* 동적 할당
				for (size_t i = originSize; i < normalMonster.size(); ++i)
				{
					normalMonster[i] = new NormalMonster;
				}

				// tempStoreObstacle 크기 증가
				tempStoreNormalMonsterInfo.resize(resizeNum);
			}

			// clickedSampleNormalMonster = false; => 계속 찍어낼 수 있는지
		}
	}
}

void EnemyToolScene::DrawSampleRect(int index, float sizeX, float sizeY)
{
	float posX = sampleNormalMonsterInfo[index].pos.x;
	float posY = sampleNormalMonsterInfo[index].pos.y;

	sampleNormalMonsterInfo[index].shape.left = (LONG)(posX - (sizeX * DEVIDE_HALF));
	sampleNormalMonsterInfo[index].shape.top = (LONG)(posY - (sizeY * DEVIDE_HALF));
	sampleNormalMonsterInfo[index].shape.right = (LONG)(posX + (sizeX * DEVIDE_HALF));
	sampleNormalMonsterInfo[index].shape.bottom = (LONG)(posY + (sizeY * DEVIDE_HALF));
}

void EnemyToolScene::EstablishSampleType()
{
	sampleNormalMonsterInfo[0].sampleType = NormalMonsterTypes::FLY;
	sampleNormalMonsterInfo[1].sampleType = NormalMonsterTypes::ATTACKFLY;
	sampleNormalMonsterInfo[2].sampleType = NormalMonsterTypes::POOTER;
}

void EnemyToolScene::InitializeStoreSpace()
{
	resizeNum = 4;
	// tempStoreObstacleInfo clear
	tempStoreNormalMonsterInfo.clear();
	tempStoreNormalMonsterInfo.resize(resizeNum);
	storeIndex = 0;
	// 화면에 보여지는 Obstacle clear()
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		SAFE_RELEASE(normalMonster[i]);
	}
	normalMonster.clear();
	normalMonster.resize(resizeNum);
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		normalMonster[i] = new NormalMonster;
	}
}

void EnemyToolScene::Load(int loadIndex, int normalMonsterCount)
{
	char loadFileName[MAX_PATH];

	sprintf_s(loadFileName, "Save/MONSTER%02d_%02d.monster", loadIndex, normalMonsterCount);

	HANDLE hFile = CreateFile(loadFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD normalMonsterLoadFileInfo = sizeof(storeNormalMonsterInfo) * normalMonsterCount;

	DWORD readByte = 0;

	for (size_t i = 0; i < normalMonsterCount; ++i)
	{
		if (ReadFile(hFile, &storeNormalMonster[i], sizeof(storeNormalMonsterInfo), &readByte, NULL) == false)
		{
			MessageBox(_hWnd, "Normal Monster 데이터 로드에 실패! !", "에러", MB_OK);
		}
	}

	if (loadNormalMonster.size() == 0)
	{
		loadNormalMonster.resize(normalMonsterCount);
		for (size_t i = 0; i < loadNormalMonster.size(); ++i)
		{
			loadNormalMonster[i] = new NormalMonster;
			loadNormalMonster[i]->SetNormalMonsterPos(storeNormalMonster[i].pos);
			loadNormalMonster[i]->SetNormalMonsterType(storeNormalMonster[i].sampleType);
			loadNormalMonster[i]->Init();
		}
	}

	CloseHandle(hFile);
}

void EnemyToolScene::Save(int saveIndex, int normalMonsterCount)
{
	char saveFileName[MAX_PATH];

	sprintf_s(saveFileName, "Save/MONSTER%02d_%02d.monster", saveIndex, normalMonsterCount);

	HANDLE hFile = CreateFile(saveFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD byteSize = sizeof(storeNormalMonsterInfo) * normalMonsterCount;

	DWORD writtenByte = 0;

	for (size_t i = 0; i < normalMonsterCount; ++i)
	{
		if (WriteFile(hFile, &storeNormalMonster[i], sizeof(storeNormalMonsterInfo), &writtenByte, NULL) == false)
		{
			MessageBox(_hWnd, "Normal Monster 데이터 저장에 실패! !", "에러", MB_OK);
		}
	}

	CloseHandle(hFile);
}

void EnemyToolScene::StoreNormalMonster()
{
	// Save Button 클릭 시 storeNormalMonster에 저장 후 파일 생성
	if (button->GetSelectEnemyBtnButton() == false && clickedSampleNormalMonster == false)
	{
		if (button->GetPressSaveButton())
		{
			button->SetPressSaveButton(false);
			// 임시 저장 장소에 얼마나 저장됐는지의 변수
			int index = 0;
			for (size_t i = 0; i < tempStoreNormalMonsterInfo.size(); ++i)
			{
				if (tempStoreNormalMonsterInfo[i].sampleType != NormalMonsterTypes::NONE)
				{
					++index;
				}
			}

			// index만큼 초기화 시키고
			storeNormalMonster.resize(index);
			for (size_t i = 0; i < storeNormalMonster.size(); ++i)
			{
				storeNormalMonster[i].pos = tempStoreNormalMonsterInfo[i].pos;
				storeNormalMonster[i].sampleType = tempStoreNormalMonsterInfo[i].sampleType;
			}

			// 파일로 저장
			Save(saveIndex, index);
			++saveIndex;

			InitializeStoreSpace();
		}
	}
}
