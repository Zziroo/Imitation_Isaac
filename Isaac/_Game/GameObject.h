#pragma once

class GameObject
{
private:

protected:
	POINTFLOAT pos = { 0 };			//위치
	RECT shape = { 0 };				//모양
	float bodySize = 0.0f;			//크기
	float moveSpeed = 0.0f;			//속도
	int elapsedAnime = 0;			//애니메이션 지연

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

