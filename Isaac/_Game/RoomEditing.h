#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
private:
	MapEditing*							stage = nullptr;
	RoomTypes							roomType = RoomTypes::NONE;

	vector<vector<RoomTypes>>			roomInfo;				// Map�� ������ Room Type�� ����
	vector<vector<bool>>				isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���� ����
	vector<vector<string>>				stageIndex;				// Stage�� Map ������ �������� ���� ����

	int									_stageSize = 0;
	int									_startPoint = 0;
	int									stageColumn = 0;		// �����Ϸ��� ��
	int									stageRow = 0;			// �����Ϸ��� ��

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

