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
	// �׸� ���� BackGround
	indicativeAreaImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/SampleImage.bmp");
	// Sample BackGround Image
	sampleBackGroundImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/BackGround04.bmp");
	// Sample Normal Monster
	sampleNormalMonsterImg = GET_SINGLETON_IMAGE->FindImage("Image/Monster/NormalMonster.bmp");

	// Sample Normal Monster
	sampleNormalMonsterInfo.resize(3);
	// Normal Monster Type ����
	EstablishSampleType();
	// ��ġ ����
	for (int c = 0; c < 3; ++c)
	{
		sampleNormalMonsterInfo[c].pos = { 886.0f + (64.0f * c), 300.0f };
	}
	// �����ϱ� ���� RECT ����
	DrawSampleRect(0, 38.0f, 20.0f);	// Fly
	DrawSampleRect(1, 38.0f, 20.0f);	// AttackFly
	DrawSampleRect(2, 38.0f, 38.0f);	// Pooter

	// Normal Monster�� �޾ƿ��� ���� ���� �ʱ�ȭ
	normalMonster.resize(resizeNum);
	for (size_t i = 0; i < normalMonster.size(); ++i)
	{
		normalMonster[i] = new NormalMonster;
	}

	// NormalMonster�� ������ �ӽ� ������ ���� �ʱ�ȭ
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

	// NormalMonsterImg�� Ŭ��
	ClickedNormalMonster();

	// NormalMonster �׸���
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
	// Ŭ�� ����
	if (Input::GetButtonDown('X'))
	{
		clickedSampleNormalMonster = false;
	}
#endif

	// NormalMonster ����
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
			loadNormalMonster[i]->Update();								// ���� �߻�! ! => �� 4�� ����� ���Ͱ� ������ ���� �ִ��� �𸣰ڽ��ϴ�.
		}
	}

	// Button
	button->Update();

	// SampleTile Button�� ������ TilemapToolScene���� �̵�
	if (button->GetSelectSampleTileButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("TilemapTool");
	}
	// Obstacle Button�� ������ ObstacleToolScene���� �̵�
	else if (button->GetSelectObstacleButton())
	{
		GET_SINGLETON_SCENE->ChangeScene("ObstacleTool");
	}
}

void EnemyToolScene::Render(HDC hdc)
{
	// BackGround
	backGroundImg->Render(hdc);
	// �׸� �� ������ Image
	indicativeAreaImg->TransparentRender(hdc, (INT)(WIN_SIZE_X * DEVIDE_HALF), (INT)(WIN_SIZE_Y * DEVIDE_HALF), indicativeAreaImg->GetCurrFrameX(), indicativeAreaImg->GetCurrFrameY(), 150.0f);
	// �׷������� ������ ǥ��
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

	// Enemy Button�� Ŭ������ ��
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

	// Normal Monster�� Ŭ������ �� �̹����� ����ֱ�
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
		//loadNormalMonster �ʱ�ȭ
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
	// ��Ŭ�� �� NormalMonster�� pos, type�� ����Ǹ� ȭ�鿡 ������
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

			// ����뷮�� �� ���� �뷮�� �� ��� �÷��ش�.
			if (storeIndex >= resizeNum)
			{
				int originSize = resizeNum;
				resizeNum *= 2;
				// NormalMonster* ũ�� ����
				normalMonster.resize(resizeNum);
				// NormalMonster* ���� �Ҵ�
				for (size_t i = originSize; i < normalMonster.size(); ++i)
				{
					normalMonster[i] = new NormalMonster;
				}

				// tempStoreObstacle ũ�� ����
				tempStoreNormalMonsterInfo.resize(resizeNum);
			}

			// clickedSampleNormalMonster = false; => ��� �� �� �ִ���
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
	// ȭ�鿡 �������� Obstacle clear()
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
			MessageBox(_hWnd, "Normal Monster ������ �ε忡 ����! !", "����", MB_OK);
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
			MessageBox(_hWnd, "Normal Monster ������ ���忡 ����! !", "����", MB_OK);
		}
	}

	CloseHandle(hFile);
}

void EnemyToolScene::StoreNormalMonster()
{
	// Save Button Ŭ�� �� storeNormalMonster�� ���� �� ���� ����
	if (button->GetSelectEnemyBtnButton() == false && clickedSampleNormalMonster == false)
	{
		if (button->GetPressSaveButton())
		{
			button->SetPressSaveButton(false);
			// �ӽ� ���� ��ҿ� �󸶳� ����ƴ����� ����
			int index = 0;
			for (size_t i = 0; i < tempStoreNormalMonsterInfo.size(); ++i)
			{
				if (tempStoreNormalMonsterInfo[i].sampleType != NormalMonsterTypes::NONE)
				{
					++index;
				}
			}

			// index��ŭ �ʱ�ȭ ��Ű��
			storeNormalMonster.resize(index);
			for (size_t i = 0; i < storeNormalMonster.size(); ++i)
			{
				storeNormalMonster[i].pos = tempStoreNormalMonsterInfo[i].pos;
				storeNormalMonster[i].sampleType = tempStoreNormalMonsterInfo[i].sampleType;
			}

			// ���Ϸ� ����
			Save(saveIndex, index);
			++saveIndex;

			InitializeStoreSpace();
		}
	}
}
