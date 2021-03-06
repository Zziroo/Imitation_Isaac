#pragma once

#include "GameObject.h"

class Image;
class RoomEditing;
class DoorEditing : public GameObject
{
private:
	RoomEditing*								roomIndex = nullptr;

	vector<vector<RoomTypes>>					roomInfo;				// 동적할당해 가져오는 정보(RoomTypes)를 담는 이중 벡터
	vector<vector<array<DOOR_INFO, 4>>>			door;					// 순회하면서 각 Room들의 상, 하, 좌, 우의 RoomTyeps을 인식하고 imga를 저장하는 이중 벡터
	vector<vector<bool>>						isTransitMap;			// 맵을 경유했는지 확인하기 위한 이중 벡터
	vector<vector<string>>						stage01Index;			// Stage01의 Map 정보를 가져오는 이중 벡터

	int											stageSize = 0;
	int											startPoint = 0;

public:
	virtual void								Release() override;
	virtual void								Update() override;
	virtual void								Render(HDC hdc) override;
	virtual void								OnDebug(HDC hdc) override;

	void										ApplyDoorInfo(int nextRow, int nextColumn, int row, int column, int direction);
	void										ChangeImageDoorState();
	void										ChangeShapeOpenDoor();
	void										FixBossRoomDoor();
	void										FixCurseRoomDoor();
	void										FixItemRoomDoor();
	void										FixPrivateRoomDoor();
	void										FixSatanRoomDoor();
	void										FixStartRoomDoor();
	void										Init(int stageNum = 0);
	void										OpenTheDoor();								// Map에 Monster가 없으면 OpenState
	void										StoreRoomType(int row, int column);

	int											GetLocatedRow() { return this->currRow; }
	int											GetLocatedColumn() { return this->currColumn; }
	vector<vector<array<DOOR_INFO, 4>>>			GetDoorInfo() { return this->door; }
	vector<vector<RoomTypes>>					GetRoomType() { return this->roomInfo; }
	vector<vector<string>>						GetStage() { return this->stage01Index; }
	int											GetStageSize() { return this->stageSize; }
	int											GetStartPoint() { return this->startPoint; }

	virtual ~DoorEditing() = default;
};

