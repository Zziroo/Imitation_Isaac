#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
private:
	MapEditing*							stage = nullptr;
	RoomTypes							roomType = RoomTypes::NONE;

	vector<vector<RoomTypes>>			roomInfo;				// Map의 정보로 Room Type을 지정
	vector<vector<bool>>				isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중 벡터
	vector<vector<string>>				stageIndex;				// Stage의 Map 정보를 가져오는 이중 벡터

	int									_stageSize = 0;
	int									_startPoint = 0;
	int									stageColumn = 0;		// 진행하려는 행
	int									stageRow = 0;			// 진행하려는 열

public:
	virtual void						Release() override;

	void								DeclareRoomName(int row, int column);
	void								DesignateBossRoom();
	void								DesignateItemRoom(int row, int column);
	void								GenerateRandomItemRoom();
	void								NamingRoom(int row, int column);
	void								Init(int stageNum = 0);

	vector<vector<string>>				GetStage() { return this->stageIndex; }
	vector<vector<RoomTypes>>			GetRoomType() { return this->roomInfo; }
	int									GetStageSize() { return this->_stageSize; }
	int									GetStartPoint() { return this->_startPoint; }

	virtual	~RoomEditing() = default;
};

