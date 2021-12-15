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
		bool						exploreSurroundingMap = false;			// 주변 탐색이 됐는지 확인 => if(true) minimapImg Render;
		bool						isVisitedMap = false;					// 방문 했는지 확인 => if(true) minimapIcon Render;
	};

private:
	Image*							currSiteImg = nullptr;					// 현재 위치한 Map의 이미지
	Image*							minimapBackGround[2] = { nullptr };		// 미니맵 배경

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
	void							VisitedMapIcon(int row, int column);

	inline void						SetCurrCloumn(int column) { this->currColumn = column; }
	inline void						SetCurrRow(int row) { this->currRow = row; }
	inline void						SetRoomInfo(vector<vector<RoomTypes>>* roomType) { this->roomInfo = roomType; }
	inline void						SetStageSize(int size) { this->stageSize = size; }
	inline void						SetStartPointRow(int row) { this->startPointRow = row; }
	inline void						SetStartPointColumn(int column) { this->startPointColumn = column; }

	virtual ~Minimap() = default;
};
