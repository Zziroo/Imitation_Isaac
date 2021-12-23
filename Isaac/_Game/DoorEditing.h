#pragma once

#include "GameObject.h"

class Image;
class RoomEditing;
class DoorEditing : public GameObject
{
private:
	RoomEditing*								roomIndex = nullptr;

	vector<vector<RoomTypes>>					roomInfo;				// �����Ҵ��� �������� ����(RoomTypes)�� ��� ���� ����
	vector<vector<array<DOOR_INFO, 4>>>			door;					// ��ȸ�ϸ鼭 �� Room���� ��, ��, ��, ���� RoomTyeps�� �ν��ϰ� imga�� �����ϴ� ���� ����
	vector<vector<bool>>						isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���� ����
	vector<vector<string>>						stage01Index;			// Stage01�� Map ������ �������� ���� ����

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
	void										FixBossDoor();
	void										FixCurseDoor();
	void										FixItemDoor();
	void										FixPrivateDoor();
	void										FixSatanDoor();
	void										FixStartDoor();
	void										Init(int stageNum = 0);
	void										OpenTheDoor();
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

