#pragma once

#include "Input.h"

class GameObject
{
private:

protected:
	POINTFLOAT			pos = { 0 };						// ��ġ
	RECT				shape = { 0 };						// ���
	float				objectSize = 0.0f;					// ũ��
	float				moveSpeed = 0.0f;					// �ӵ�
	int					elapsedAnime = 0;					// �ִϸ��̼� ����

	bool				debugMode = false;					// ������

	enum class			MoveDir { UP, DOWN, LEFT, RIGHT };	// �̵� ����

public:
	virtual void		Init();
	virtual void		Release();
	virtual void		Update();
	virtual void		Render(HDC hdc);
	virtual void		OnDebug(HDC hdc);

	inline void			GetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline void			SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline float		GetMoveSpeed() { return moveSpeed; }
	inline POINTFLOAT	GetPos() { return pos; }

	virtual ~GameObject() = default;
};

