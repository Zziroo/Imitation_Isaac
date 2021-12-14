#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
private:
	MapEditing*							stage01 = nullptr;
	RoomTypes							roomType = RoomTypes::NONE;

	vector<vector<RoomTypes>>			roomInfo;				// Map의 정보로 Room Type을 지정
	vector<vector<bool>>				isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중 벡터
	vector<vector<string>>				stage01Index;			// Stage01의 Map 정보를 가져오는 이중 벡터

	int									_stageSize = 0;
	int									_startPoint = 0;
	int									stageColumn = 0;		// 진행하려는 행
	int									stageRow = 0;			// 진행하려는 열

public:
	virtual void						Init() override;
	virtual void						Release() override;

	void								DeclareRoomName(int row, int column);
	void								DeginateBossRoom();
	void								DeginateItemRoom(int row, int column);
	void								NamingRoom(int row, int column);

	inline vector<vector<string>>		GetStage() { return this->stage01Index; }
	inline vector<vector<RoomTypes>>	GetRoomType() { return this->roomInfo; }
	inline int							GetStageSize() { return this->_stageSize; }
	inline int							GetStartPoint() { return this->_startPoint; }

	virtual	~RoomEditing() = default;
};

