#pragma once

#include "GameObject.h"

struct PlayerInfo
{
	// Body
	POINTFLOAT		bodyPos = {
		(FLOAT)PLAYER_BODY_POS_X,						// Pos.x
		(FLOAT)PLAYER_BODY_POS_Y						// Pos.Y
	};
	float			bodySize = 25.0f;
	RECT			bodyShape = {
		(LONG)(bodyPos.x - (bodySize * 0.5f) - 14),		// Left
		(LONG)(bodyPos.y - (bodySize * 0.5f)),			// Top
		(LONG)(bodyPos.x + (bodySize * 0.5f) + 14),		// Right
		(LONG)(bodyPos.y + (bodySize * 0.5f))			// Bottom
	};
	// Head
	POINTFLOAT		headPos = { 
		(FLOAT)PLAYER_HEAD_POS_X,						// Pos.x
		(FLOAT)PLAYER_HEAD_POS_Y						// Pos.Y
	};
	float			headSize = 70.0f;
	RECT			headShape = {
		(LONG)(headPos.x - (headSize * 0.5f) - 5),		// Left
		(LONG)(headPos.y - (headSize * 0.5f)),			// Top
		(LONG)(headPos.x + (headSize * 0.5f) + 5),		// Right
		(LONG)(headPos.y + (headSize * 0.5f))			// Bottom
	};

};

class Image;
class WeaponManager;
class Player : public GameObject
{
private:
	Image*			headImg = nullptr;
	Image*			bodyImg = nullptr;
	Image*			otherStateImg = nullptr;

	PlayerInfo		player;

	ObjectStates	playerState = ObjectStates::IDLE;	// 상태
	MoveDir			playerDir = MoveDir::DOWN;			// 이동 방향

	int				loadWeapon = 0;						// 무기 장전
	int				takeLoadWeapon = 20;				// 장전 걸리는 시간
	char			text[64] = {};						// MousePointer

	WeaponManager*	weaponTear = nullptr;

protected:

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void PressInputKey();			// 입력키
	void ChangeAnimation();			// 애니메이션 변화
	void FireWeapon(int x, int y);	// weapon 발사

	inline void SetPlayerHeadPos(POINTFLOAT pos) { this->player.headPos = pos; }
	inline POINTFLOAT GetPlayerHeadPos() { return this->player.headPos; }

	virtual ~Player() = default;
};

