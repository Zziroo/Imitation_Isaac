#pragma once

class GameObject
{
private:

protected:
	POINTFLOAT	pos = { 0 };						// ��ġ
	RECT		shape = { 0 };						// ���
	float		objectSize = 0.0f;					// ũ��
	float		moveSpeed = 0.0f;					// �ӵ�
	int			elapsedAnime = 0;					// �ִϸ��̼� ����

	bool		debugMode = false;					// ������

	enum class	MoveDir { UP, DOWN, LEFT, RIGHT };	// �̵� ����

public:
	virtual void Init() = 0;
	virtual HRESULT FindIamge() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	void OnDebuging() { if (GETSINGLETON_KEY->IsStayKeyDown(VK_LCONTROL) && GETSINGLETON_KEY->IsOnceKeyDown('E')) { debugMode = !debugMode; } }

	inline void GetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }

	inline float GetMoveSpeed() { return moveSpeed; }
	inline POINTFLOAT GetPos() { return pos; }

	virtual ~GameObject() = default;
};

