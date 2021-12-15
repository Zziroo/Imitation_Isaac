#include "MainConfig.h"
#include "Minimap.h"

#include "Image.h"

void Minimap::Init()
{
	// Minimap ���
	minimapBackGround[0] = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/MinimapBackGround00.bmp");
	minimapBackGround[1] = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/MinimapBackGround01.bmp");
	// Minimap ����� Position
	pos = { 1120, 110 };
	// Minimap Site���� ù��° ����� Position
	minimapSitePos = { pos.x - (startPointRow * 25), pos.y - (startPointColumn * 22) };
	// RoomInfo�� �޾Ƽ� MinimapInfo ����
	minimap.resize(stageSize);
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		minimap[i].resize(stageSize);
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// �̴ϸ��� ���� Position
			minimap[i][j].pos.x = (j * 25) + minimapSitePos.x;
			minimap[i][j].pos.y = (i * 22) + minimapSitePos.y;
			// RoomType �޾ƿ���
			minimap[i][j].roomType = roomInfo[0][i][j];			// �ñ�? => Player.cpp���� tile���� �޾ƿö��� �ٸ���.
			// RoomTypes::NONE�� �ƴ϶��(map�� �����Ѵٸ�) Image �߰�
			if (minimap[i][j].roomType != RoomTypes::NONE)
			{
				minimap[i][j].minimapImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/AroundedSite.bmp");
			}
			// roomType�� �´� Icon Image�߰�
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
	// ���� ��ġ�� Map�� Image
	currSiteImg = GET_SINGLETON_IMAGE->FindImage("Image/Minimap/LocatedSite.bmp");
	// StartPoint �� �ֺ� ������ Ž���Ͽ� Minimap�� ǥ���ϱ� ���� bool��
	ExploreSurroundingMap(startPointRow, startPointColumn);
	// Ư�� ���� �湮�ϸ� Minimap�� Icon ǥ���ϱ� ���� bool��
	VisitedMapIcon(startPointRow, startPointColumn);
}

void Minimap::Release()
{
}

void Minimap::Update()
{
	// Map �̵� �� Minimap �̵�
	MoveMinimap();
	// CurrPoint�� �ֺ� ������ Ž���Ͽ� Minimap�� ǥ��
	ExploreSurroundingMap(currRow, currColumn);
	// Ư�� ���� �湮�ϸ� Minimap�� Icon ǥ���ϱ� ���� bool��
	VisitedMapIcon(currRow, currColumn);
}

void Minimap::Render(HDC hdc)
{
	// MinimapBackGround Render
	minimapBackGround[0]->Render(hdc, pos.x, pos.y);
	minimapBackGround[1]->TransparentRender(hdc, pos.x, pos.y, minimapBackGround[1]->GetCurrFrameX(), minimapBackGround[1]->GetCurrFrameY(), 75.0f);

	// ��ü Minimap ������ �ɾ� Render
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// ��ü Minimap�� Ž���� Map�̸� Render
			if (minimap[i][j].exploreSurroundingMap && minimap[i][j].minimapImg != nullptr)
			{
				int renderPosX = (INT)minimap[i][j].pos.x;
				int renderPosY = (INT)minimap[i][j].pos.y;
				minimap[i][j].minimapImg->Render(hdc, renderPosX, renderPosY);
			}
		}
	}
	
	// ���� ��ġ�� ���� Minimap�� Render
	currSiteImg->Render(hdc, pos.x, pos.y);

	// ��ü Minimap ������ �ɾ� Render
	for (size_t i = 0; i < minimap.size(); ++i)
	{
		for (size_t j = 0; j < minimap[i].size(); ++j)
		{
			// ��ü Minimap�� �湮�� Map�̰� Ư�� map�̸� Icon Render
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
	// StartPoint�� Minimap Image�� Render ��Ű�� ����  bool�� true
	minimap[row][column].exploreSurroundingMap = true;
	int NextUpRow = row - 1;
	int NextDownRow = row + 1;
	int NextLeftColumn = column - 1;
	int NextRightColumn = column + 1;
	// StartPoint�� ���� Minimap Image�� Render ��Ű�� ����  bool�� true
	if (NextUpRow >= 0)
	{
		minimap[NextUpRow][column].exploreSurroundingMap = true;
	}
	// StartPoint�� �Ʒ��� Minimap Image�� Render ��Ű�� ����  bool�� true
	if (NextDownRow < stageSize)
	{
		minimap[NextDownRow][column].exploreSurroundingMap = true;
	}
	// StartPoint�� ���� Minimap Image�� Render ��Ű�� ����  bool�� true
	if (NextLeftColumn >= 0)
	{
		minimap[row][NextLeftColumn].exploreSurroundingMap = true;
	}
	// StartPoint�� ������ Minimap Image�� Render ��Ű�� ����  bool�� true
	if (NextRightColumn < stageSize)
	{
		minimap[row][NextRightColumn].exploreSurroundingMap = true;
	}
}

void Minimap::MoveMinimap()
{
	// ��

	// ��

	// ��

	// ��


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
