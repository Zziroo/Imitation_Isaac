#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
private:
	MapEditing*							stage01 = nullptr;
	RoomTypes							roomType = RoomTypes::NONE;

	vector<vector<RoomTypes>>			roomInfo;				// Map�� ������ Room Type�� ����
	vector<vector<bool>>				isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���� ����
	vector<vector<string>>				stage01Index;			// Stage01�� Map ������ �������� ���� ����

	int									_stageSize = 0;
	int									_startPoint = 0;
	int									stageColumn = 0;		// �����Ϸ��� ��
	int									stageRow = 0;			// �����Ϸ��� ��

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

