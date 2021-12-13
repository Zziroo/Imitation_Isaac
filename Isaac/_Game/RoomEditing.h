#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
	enum class RoomType { BOSS, COURSE, ITEM, NORMAL, PRIVATE, SATAN, START, NONE };

private:
	MapEditing*					stage01;
	RoomType					roomType = RoomType::NONE;

	vector<vector<bool>>		isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중 벡터
	vector<vector<string>>		stage01Index;			// Stage01의 Map 정보를 가져오는 이중 벡터
	vector<vector<RoomType>>	roomInfo;				// Map의 정보로 Room Type을 지정

	int							_stageSize = 0;
	int							_startPoint = 0;
	int							stageColumn = 0;		// 진행하려는 행
	int							stageRow = 0;			// 진행하려는 열

public:
	virtual void				Init() override;
	virtual void				Release() override;

	void						NamingRoom(int row, int column);
	void						DeclareRoomName(vector<vector<string>> stageIndex, vector<vector<RoomType>> _roomInfo, int row, int column);

	virtual	~RoomEditing() = default;
};

