#pragma once

class GameObject
{
protected:
	TILE_INFO*			tile = nullptr;								// 타일의 정보
	POINTFLOAT			pos = { 0 };								// 위치
	RECT				shape = { 0 };								// 모양
	float				objectSize = 0.0f;							// 크기
	float				moveSpeed = 0.0f;							// 속도
	int					elapsedAnime = 0;							// 애니메이션 지연

	bool				debugMode = false;							// 디버깅용

	enum class			ObjectDir { UP, DOWN, LEFT, RIGHT, NONE };	// 이동 방향

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

