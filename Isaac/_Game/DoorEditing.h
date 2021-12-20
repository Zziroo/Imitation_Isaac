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

	int											_stageSize = 0;
	int											_startPoint = 0;
	int											currLocatedRow = 0;
	int											currLocatedColumn = 0;

public:
	virtual void								Release() override;
	virtual void								Update() override;
	virtual void								Render(HDC hdc) override;
	virtual void								OnDebug(HDC hdc) override;

	void										FixBossDoor();
	void										FixCurseDoor();
	void										FixItemDoor();
	void										FixPrivateDoor();
	void										FixSatanDoor();
	void										FixStartDoor();
	void										Init(int stageNum = 0);
	void										StoreRoomType(int row, int column);

	int											GetLocatedRow() { return this->currLocatedRow; }
	int											GetLocatedColumn() { return this->currLocatedColumn; }
	vector<vector<array<DOOR_INFO, 4>>>			GetDoorInfo() { return this->door; }
	vector<vector<RoomTypes>>					GetRoomType() { return this->roomInfo; }
	vector<vector<string>>						GetStage() { return this->stage01Index; }
	int											GetStageSize() { return this->_stageSize; }
	int											GetStartPoint() { return this->_startPoint; }

	void										SetLocatedRow(int row) { this->currLocatedRow = row; }
	void										SetLocatedColumn(int column) { this->currLocatedColumn = column; }

	virtual ~DoorEditing() = default;
};

