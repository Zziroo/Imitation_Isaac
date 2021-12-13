#pragma once

class GameObject
{
protected:
	TILE_INFO*			tile = nullptr;								// Ÿ���� ����
	POINTFLOAT			pos = { 0 };								// ��ġ
	RECT				shape = { 0 };								// ���
	float				objectSize = 0.0f;							// ũ��
	float				moveSpeed = 0.0f;							// �ӵ�
	int					elapsedAnime = 0;							// �ִϸ��̼� ����

	bool				debugMode = false;							// ������

	enum class			ObjectDir { UP, DOWN, LEFT, RIGHT, NONE };	// �̵� ����

public:
	virtual void		Init();
	virtual void		Release();
	virtual void		Update();
	virtual void		Render(HDC hdc);
	virtual void		OnDebug(HDC hdc);

	inline void			GetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline void			SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline void			SetTileInfo(TILE_INFO* tile) { this->tile = tile; }

	inline float		GetMoveSpeed() { return moveSpeed; }
	inline POINTFLOAT	GetPos() { return pos; }

	virtual ~GameObject() = default;
};

