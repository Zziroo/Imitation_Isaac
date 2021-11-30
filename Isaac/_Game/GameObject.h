#pragma once

class GameObject
{
private:

protected:
	POINTFLOAT	pos = { 0 };						//	��ġ
	RECT		shape = { 0 };						//	���
	float		objectSize = 0.0f;					//	ũ��
	float		moveSpeed = 0.0f;					//	�ӵ�
	int			elapsedAnime = 0;					//	�ִϸ��̼� ����

	enum class	MoveDir { UP, DOWN, LEFT, RIGHT };	// �̵� ����

public:
	virtual void Init() = 0;
	virtual HRESULT FindIamge() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	inline POINTFLOAT GetPos() { return pos; }
	inline void SetPosX(float posX) { this->pos.x = posX; }
	inline void SetPosY(float posY) { this->pos.y = posY; }
	inline float GetMoveSpeed() { return moveSpeed; }

	virtual ~GameObject() = default;
};

