#pragma once

#include "GameObject.h"

enum class DoorStates { OPENED, CLOSED, LOCKED, NONE };

class Image;
class RoomEditing;
class DoorEditing : public GameObject
{
private:
	typedef struct tagDoorInfo
	{
		Image*							img = nullptr;
		DoorStates						doorState = DoorStates::NONE;
		ObjectDir						doorDir = ObjectDir::NONE;
		POINTFLOAT						pos = {};
		RECT							shape = {};
	} DOOR_INFO;

private:
	RoomEditing*						roomIndex = nullptr;

	vector<vector<bool>>				isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���� ����
	vector<vector<string>>				stage01Index;			// Stage01�� Map ������ �������� ���� ����
	vector<vector<RoomTypes>>			roomInfo;				// �����Ҵ��� �������� ����(RoomTypes)�� ��� ���� ����
	vector<vector<array<DOOR_INFO, 4>>>	door;					// ��ȸ�ϸ鼭 �� Room���� ��, ��, ��, ���� RoomTyeps�� �ν��ϰ� imga�� �����ϴ� ���� ����

	int									_stageSize = 0;
	int									_startPoint = 0;
	int									currLocateRow = 0;
	int									currLocateColumn = 0;

public:
	virtual void						Init() override;
	virtual void						Release() override;
	virtual void						Update() override;
	virtual void						Render(HDC hdc) override;
	virtual void						OnDebug(HDC hdc) override;

	void								FixBossDoor();
	void								FixCurseDoor();
	void								FixItemDoor();
	void								FixSatanDoor();
	void								IdentifyRoomType(int row, int column, int index);
	void								StoreRoomType(int row, int column);

	inline vector<vector<string>>		GetStage() { return this->stage01Index; }
	inline vector<vector<RoomTypes>>	GetRoomType() { return this->roomInfo; }
	inline int							GetStageSize() { return this->_stageSize; }
	inline int							GetStartPoint() { return this->_startPoint; }

	virtual ~DoorEditing() = default;
};

