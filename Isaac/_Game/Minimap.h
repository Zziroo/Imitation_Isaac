#pragma once

#include "GameObject.h"

class Image;
class Minimap :public GameObject
{
private:
	struct MinimapInfo
	{
		Image*						minimapImg = nullptr;
		Image*						minimapIconImg = nullptr;
		POINTFLOAT					pos = {};
		RoomTypes					roomType = RoomTypes::NONE;
		bool						exploreSurroundingMap = false;			// �ֺ� Ž���� �ƴ��� Ȯ�� => if(true) minimapImg Render;
		bool						isVisitedMap = false;					// �湮 �ߴ��� Ȯ�� => if(true) minimapIcon Render;
	};

private:
	Image*							currSiteImg = nullptr;					// ���� ��ġ�� Map�� �̹���
	Image*							minimapBackGround[2] = { nullptr };		// �̴ϸ� ���

	POINTFLOAT						minimapSitePos = {};

	vector<vector<MinimapInfo>>		minimap;
	vector<vector<RoomTypes>>*		roomInfo = nullptr;

	int								currColumn = 0;
	int								currRow = 0;
	int								stageSize = 0;
	int								startPointColumn = 0;
	int								startPointRow = 0;

public:
	virtual void					Init() override;
	virtual void					Release() override;
	virtual void					Update() override;
	virtual void					Render(HDC hdc) override;

	void							ExploreSurroundingMap(int row, int column);
	void							MoveMinimap();
	void							VisitedMapIcon(int row, int column);

	void							SetCurrCloumn(int column) { this->currColumn = column; }
	void							SetCurrRow(int row) { this->currRow = row; }
	void							SetRoomInfo(vector<vector<RoomTypes>>* roomType) { this->roomInfo = roomType; }
	void							SetStageSize(int size) { this->stageSize = size; }
	void							SetStartPointRow(int row) { this->startPointRow = row; }
	void							SetStartPointColumn(int column) { this->startPointColumn = column; }

	virtual ~Minimap() = default;
};
