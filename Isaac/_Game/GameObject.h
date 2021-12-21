#pragma once

class GameObject
{
protected:
	TILE_INFO*								tile = nullptr;								// 타일의 정보
	POINTFLOAT								pos = {};									// 위치
	RECT									shape = {};									// 모양

	bool									debugMode = false;							// 디버깅용

	float									objectSize = 0.0f;							// 크기
	float									moveSpeed = 0.0f;							// 속도
	
	int										elapsedAnimeCount = 0;						// 애니메이션 지연

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

