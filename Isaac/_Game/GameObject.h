#pragma once

class BossMonster;
class BossMonsterHP;
class NormalMonster;
class Obstacle;
class Player;
class PlayerTear;
class GameObject
{
protected:
	BossMonster*								bossMonster = nullptr;
	BossMonsterHP*								bossMonsterHP = nullptr;
	Player*										player = nullptr;
	TILE_INFO*									tile = nullptr;								// Ÿ���� ����

	vector<vector<vector<NormalMonster*>>>*		normalMonster = nullptr;					// Normal Monster ����
	vector<vector<vector<Obstacle*>>>*			obstacle = nullptr;							// ��ֹ� ����

	POINTFLOAT									pos = {};									// ��ġ
	RECT										shape = {};									// ���
	RECT										colliderRect = {};

	bool										debugMode = false;							// ������

	float										objectSize = 0.0f;							// ũ��
	float										moveSpeed = 0.0f;							// �ӵ�

	int											bossColumn = 0;
	int											bossRow = 0;
	int											currColumn = 0;								// ���� ���� column
	int											currRow = 0;								// ���� ���� row
	int											elapsedAnimeCount = 0;						// �ִϸ��̼� ����

public:
	virtual void								Init();
	virtual void								Release();
	virtual void								Update();
	virtual void								Render(HDC hdc);
	virtual void								OnDebug(HDC hdc);

	float										GetMoveSpeed() { return this->moveSpeed; }
	float										GetObjectSize() { return this->objectSize; }
	POINTFLOAT									GetPos() { return this->pos; }
	RECT										GetShape() { return this->shape; }
	
	void										SetBossColumn(int column) { this->bossColumn = column; }
	void										SetBossMonster(BossMonster* bossMonster) { this->bossMonster = bossMonster; }
	void										SetBossMonsterHP(BossMonsterHP* bossMonsterHP) { this->bossMonsterHP = bossMonsterHP; }
	void										SetBossRow(int row) { this->bossRow = row; }
	void										SetCurrCloumn(int column) { this->currColumn = column; }
	void										SetCurrRow(int row) { this->currRow = row; }
	void										SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	void										SetNormalMonsterInfo(vector<vector<vector<NormalMonster*>>>* normalMonster) { this->normalMonster = normalMonster; }
	void										SetObjectSize(float size) { this->objectSize = size; }
	void										SetObstacleInfo(vector<vector<vector<Obstacle*>>>* obstacle) { this->obstacle = obstacle; }
	void										SetPlayer(Player* player) { this->player = player; }
	void										SetPos(POINTFLOAT pos) { this->pos = pos; }
	void										SetTileInfo(TILE_INFO* tile) { this->tile = tile; }


	virtual ~GameObject() = default;
};

