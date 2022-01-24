#include "stdafx.h"
#include "NextStageDoor.h"

#include "Image.h"

void NextStageDoor::Init()
{
	img = GET_SINGLETON_IMAGE->FindImage("Image/Door/Next_Stage_Door.bmp");

	pos = { WIN_SIZE_X * DEVIDE_HALF, 250.0f };

	objectSize = 96.0f;

	shape = {
		(LONG)(pos.x - (objectSize * DEVIDE_HALF)),
		(LONG)(pos.y - (objectSize * DEVIDE_HALF)),
		(LONG)(pos.x + (objectSize * DEVIDE_HALF)),
		(LONG)(pos.y + (objectSize * DEVIDE_HALF))
	};
}

void NextStageDoor::Release()
{
}

void NextStageDoor::Update()
{
#ifdef _DEBUG
	GameObject::Update();
#endif

	OpenNextStageDoorAnimation();
}

void NextStageDoor::Render(HDC hdc)
{
	img->Render(hdc, (INT)pos.x, (INT)pos.y, img->GetCurrFrameX(), img->GetCurrFrameY());

	// Debug
	GameObject::Render(hdc);
}

void NextStageDoor::OnDebug(HDC hdc)
{
	if (debugMode)
	{
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void NextStageDoor::OpenNextStageDoorAnimation()
{
	++elapsedAnimeCount;
	if (elapsedAnimeCount > 5)
	{
		img->SetCurrFrameX(1);
	}
}
