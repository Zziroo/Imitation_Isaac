#pragma once

#include "GameObject.h"

class Image;
class WeaponManager;
class Player : public GameObject
{
private:
	struct PlayerInfo
	{
		// Body
		POINTFLOAT		bodyPos = {
			(FLOAT)PLAYER_BODY_POS_X,										// Pos.x
			(FLOAT)PLAYER_BODY_POS_Y										// Pos.Y
		};
		float			bodySize = PLAYER_BODYSIZE;
		RECT			bodyShape = {
			(LONG)(bodyPos.x - (bodySize * DEVIDE_HALF) - ADJUST_SIZE_14),	// Left
			(LONG)(bodyPos.y - (bodySize * DEVIDE_HALF)),					// Top
			(LONG)(bodyPos.x + (bodySize * DEVIDE_HALF) + ADJUST_SIZE_14),	// Right
			(LONG)(bodyPos.y + (bodySize * DEVIDE_HALF))					// Bottom
		};
		// Head
		POINTFLOAT		headPos = { 
			(FLOAT)PLAYER_HEAD_POS_X,										// Pos.x
			(FLOAT)PLAYER_HEAD_POS_Y										// Pos.Y
		};
		float			headSize = PLAYER_HEADSIZE;
		RECT			headShape = {
			(LONG)(headPos.x - (headSize * DEVIDE_HALF) - ADJUST_SIZE_05),	// Left
			(LONG)(headPos.y - (headSize * DEVIDE_HALF)),					// Top
			(LONG)(headPos.x + (headSize * DEVIDE_HALF) + ADJUST_SIZE_05),	// Right
			(LONG)(headPos.y + (headSize * DEVIDE_HALF))					// Bottom
		};

	} player;

private:
	Image*			headImg = nullptr;
	Image*			bodyImg = nullptr;
	Image*			otherStateImg = nullptr;

	ObjectStates	playerState = ObjectStates::IDLE;		// ����
	MoveDir			playerDir = MoveDir::DOWN;				// �̵� ����

	int				takeLoadWeapon = TAKE_WEAPONLOADTIME;	// ���� �ɸ��� �ð�
	int				loadWeapon = takeLoadWeapon;			// ���� ����
	bool			isFire = false;							// ���� �߻�
	char			text[64] = {};							// MousePointer

	WeaponManager*	weaponTear = nullptr;

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void TakeAction();										// �Է�Ű
	void ChangeAnimation();									// �ִϸ��̼� ��ȭ
	void FireWeapon(int x, int y);							// weapon �߻�

	inline void SetPlayerHeadPos(POINTFLOAT pos) { this->player.headPos = pos; }
	inline POINTFLOAT GetPlayerHeadPos() { return this->player.headPos; }

	virtual ~Player() = default;
};

