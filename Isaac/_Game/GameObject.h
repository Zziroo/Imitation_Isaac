#pragma once

class GameObject
{
protected:
	TILE_INFO*								tile = nullptr;								// Ÿ���� ����
	POINTFLOAT								pos = {};									// ��ġ
	RECT									shape = {};									// ���

	bool									debugMode = false;							// ������

	float									objectSize = 0.0f;							// ũ��
	float									moveSpeed = 0.0f;							// �ӵ�
	
	int										elapsedAnimeCount = 0;						// �ִϸ��̼� ����

public:
	virtual void							Init();
	virtual void							Release();
	virtual void							Update();
	virtual void							Render(HDC hdc);
	virtual void							OnDebug(HDC hdc);

	inline float							GetMoveSpeed() { return moveSpeed; }
	inline POINTFLOAT						GetPos() { return pos; }

	inline void								SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline void								SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void								SetTileInfo(TILE_INFO* tile) { this->tile = tile; }


	virtual ~GameObject() = default;
};

