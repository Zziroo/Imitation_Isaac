#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
	enum class RoomType { BOSS, COURSE, ITEM, NORMAL, PRIVATE, SATAN, START, NONE };

private:
	MapEditing*					stage01;
	RoomType					roomType = RoomType::NONE;

	vector<vector<bool>>		isTransitMap;			// ���� �����ߴ��� Ȯ���ϱ� ���� ���� ����
	vector<vector<string>>		stage01Index;			// Stage01�� Map ������ �������� ���� ����
	vector<vector<RoomType>>	roomInfo;				// Map�� ������ Room Type�� ����

	int							_stageSize = 0;
	int							_startPoint = 0;
	int							stageColumn = 0;		// �����Ϸ��� ��
	int							stageRow = 0;			// �����Ϸ��� ��

public:
	virtual void				Init() override;
	virtual void				Release() override;

	void						NamingRoom(int row, int column);
	void						DeclareRoomName(vector<vector<string>> stageIndex, vector<vector<RoomType>> _roomInfo, int row, int column);

	virtual	~RoomEditing() = default;
};

