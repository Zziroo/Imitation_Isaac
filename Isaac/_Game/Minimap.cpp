#include "MainConfig.h"
#include "Minimap.h"

#include "Image.h"

void Minimap::Init()
{
	// Minimap 배경
	minimapBackGround[0] = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/MinimapBackGround00.bmp");
	minimapBackGround[1] = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/MinimapBackGround01.bmp");
	// Minimap 배경의 Position
	pos = { 1120, 110 };
	// Minimap Site들의 첫번째 요소의 Position
	minimapSitePos = { pos.x - (startPointRow * 25), pos.y - (startPointColumn * 22) };
	// RoomInfo를 받아서 MinimapInfo 갱신
	minimap.resize(stageSize);
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		minimap[i].resize(stageSize);
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// 미니맵이 나올 Position
			minimap[i][j].pos.x = (j * 25) + minimapSitePos.x;
			minimap[i][j].pos.y = (i * 22) + minimapSitePos.y;
			// RoomType 받아오기
			minimap[i][j].roomType = roomInfo[0][i][j];			// 궁금? => Player.cpp에서 tile값을 받아올때랑 다르다.
			// RoomTypes::NONE이 아니라면(map이 존재한다면) Image 추가
			if (minimap[i][j].roomType != RoomTypes::NONE)
			{
				minimap[i][j].minimapImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/AroundedSite.bmp");
			}
			// roomType에 맞는 Icon Image추가
			switch (minimap[i][j].roomType)
			{
			case RoomTypes::BOSS:
				minimap[i][j].minimapIconImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/BossIcon.bmp");
				break;
			case RoomTypes::CURSE:
				minimap[i][j].minimapIconImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/CurseIcon.bmp");
				break;
			case RoomTypes::ITEM:
				minimap[i][j].minimapIconImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/ItemIcon.bmp");
				break;
			case RoomTypes::PRIVATE:
				minimap[i][j].minimapIconImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/PrivateIcon.bmp");
				break;
			case RoomTypes::SATAN:
				minimap[i][j].minimapIconImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/SatanIcon.bmp");
				break;
			default:
				break;
			}
			// debuging
			minimap[i][j].exploreSurroundingMap = true;
			minimap[i][j].isVisitedMap = true;
		}
	}
	// 현재 위치한 Map의 Image
	currSiteImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/LocatedSite.bmp");
	// StartPoint 와 주변 지역을 탐색하여 Minimap에 표시하기 위한 bool값
	ExploreSurroundingMap(startPointRow, startPointColumn);
	// 특정 방을 방문하면 Minimap에 Icon 표시하기 위한 bool값
	VisitedMapIcon(startPointRow, startPointColumn);
}

void Minimap::Release()
{
}

void Minimap::Update()
{
	// Map 이동 시 Minimap 이동
	MoveMinimap();
	// CurrPoint와 주변 지역을 탐색하여 Minimap에 표시
	ExploreSurroundingMap(currRow, currColumn);
	// 특정 방을 방문하면 Minimap에 Icon 표시하기 위한 bool값
	VisitedMapIcon(currRow, currColumn);
}

void Minimap::Render(HDC hdc)
{
	// MinimapBackGround Render
	minimapBackGround[0]->Render(hdc, pos.x, pos.y);
	minimapBackGround[1]->TransparentRender(hdc, pos.x, pos.y, minimapBackGround[1]->GetCurrFrameX(), minimapBackGround[1]->GetCurrFrameY(), 75.0f);

	// 전체 Minimap 조건을 걸어 Render
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// 전체 Minimap중 탐색된 Map이면 Render
			if (minimap[i][j].exploreSurroundingMap && minimap[i][j].minimapImg != nullptr)
			{
				int renderPosX = (INT)minimap[i][j].pos.x;
				int renderPosY = (INT)minimap[i][j].pos.y;
				minimap[i][j].minimapImg->Render(hdc, renderPosX, renderPosY);
			}
		}
	}
	
	// 현재 위치의 맵을 Minimap에 Render
	currSiteImg->Render(hdc, pos.x, pos.y);

	// 전체 Minimap 조건을 걸어 Render
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// 전체 Minimap중 방문한 Map이고 특정 map이면 Icon Render
			if (minimap[i][j].isVisitedMap && minimap[i][j].minimapIconImg != nullptr)
			{
				int renderPosX = (INT)minimap[i][j].pos.x;
				int renderPosY = (INT)minimap[i][j].pos.y;
				minimap[i][j].minimapIconImg->Render(hdc, renderPosX, renderPosY);
			}
		}
	}
}

void Minimap::ExploreSurroundingMap(int row, int column)
{
	// StartPoint의 Minimap Image를 Render 시키기 위해  bool값 true
	minimap[row][column].exploreSurroundingMap = true;
	int NextUpRow = row - 1;
	int NextDownRow = row + 1;
	int NextLeftColumn = column - 1;
	int NextRightColumn = column + 1;
	// StartPoint의 위쪽 Minimap Image를 Render 시키기 위해  bool값 true
	if (NextUpRow >= 0)
	{
		minimap[NextUpRow][column].exploreSurroundingMap = true;
	}
	// StartPoint의 아래쪽 Minimap Image를 Render 시키기 위해  bool값 true
	if (NextDownRow < stageSize)
	{
		minimap[NextDownRow][column].exploreSurroundingMap = true;
	}
	// StartPoint의 왼쪽 Minimap Image를 Render 시키기 위해  bool값 true
	if (NextLeftColumn >= 0)
	{
		minimap[row][NextLeftColumn].exploreSurroundingMap = true;
	}
	// StartPoint의 오른쪽 Minimap Image를 Render 시키기 위해  bool값 true
	if (NextRightColumn < stageSize)
	{
		minimap[row][NextRightColumn].exploreSurroundingMap = true;
	}
}

void Minimap::MoveMinimap()
{
	// 상

	// 하

	// 좌

	// 우


	for (size_t i = 0; i < minimap.size(); ++i)
	{
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
		}
	}
}

void Minimap::VisitedMapIcon(int row, int column)
{
	minimap[row][column].isVisitedMap = true;
}
