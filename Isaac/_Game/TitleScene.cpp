#include "stdafx.h"
#include "TitleScene.h"

#include "Image.h"

HRESULT TitleScene::Init()
{
	titleImg = GET_SINGLETON_IMAGE->FindImage("Image/BackGround/Title.bmp");

	return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	// InGame Scene 전환
	if (Input::GetButtonDown(VK_SPACE))
	{
		GET_SINGLETON_SCENE->ChangeScene("Stage01");
		return;
	}

	TitleScene::ChangeTitleImage();
}

void TitleScene::Render(HDC hdc)
{
	if (titleImg) { titleImg->Render(hdc, (INT)pos.x, (INT)pos.y, titleImg->GetCurrFrameX(), titleImg->GetCurrFrameY()); }
}

// 이미지 변화
void TitleScene::ChangeTitleImage()
{
	++elapsedScene;
	if (elapsedScene >= 20)
	{
		titleImg->SetCurrFrameY(titleImg->GetCurrFrameY() + 1);
		if (titleImg->GetCurrFrameY() >= 8) { titleImg->SetCurrFrameY(0); }

		elapsedScene = 0;
	}
}
