#pragma once

#include "GameObject.h"

class Image;
class Player : public GameObject
{
private:
	struct PlayerBodyInfo
	{
		POINTFLOAT	pos = {
			(FLOAT)PLAYER_BODY_POS_X,									// Pos.x
			(FLOAT)PLAYER_BODY_POS_Y									// Pos.Y
		};
		float		size = PLAYER_BODYSIZE;
		RECT		shape = {
			(LONG)(pos.x - (size * DEVIDE_HALF) - ADJUST_SIZE_14),		// Left
			(LONG)(pos.y - (size * DEVIDE_HALF)),						// Top
			(LONG)(pos.x + (size * DEVIDE_HALF) + ADJUST_SIZE_14),		// Right
			(LONG)(pos.y + (size * DEVIDE_HALF))						// Bottom
		};
		Image*		image = nullptr;
		MoveDir		moveDir = MoveDir::DOWN;							// �̵� ����
	} bodyInfo;
	struct PlayerHeadInfo
	{
		POINTFLOAT	pos = {
			(FLOAT)PLAYER_HEAD_POS_X,									// Pos.x
			(FLOAT)PLAYER_HEAD_POS_Y									// Pos.Y
		};
		float		size = PLAYER_HEADSIZE;
		RECT		shape = {
			(LONG)(pos.x - (size * DEVIDE_HALF) - ADJUST_SIZE_05),		// Left
			(LONG)(pos.y - (size * DEVIDE_HALF)),						// Top
			(LONG)(pos.x + (size * DEVIDE_HALF) + ADJUST_SIZE_05),		// Right
			(LONG)(pos.y + (size * DEVIDE_HALF))						// Bottom
		};
		Image*		image = nullptr;
		MoveDir		moveDir = MoveDir::DOWN;							// �̵� ����
	} headInfo;

private:
	Image*			otherStateImg = nullptr;

	ObjectStates	playerState = ObjectStates::IDLE;					// ����

	bool			isFire = false;										// ���� �߻�
	char			text[64] = {};										// MousePointer

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	void ApplyFrame(MoveDir moveDir, int bodyFrameY, int headFrameX);
	void ChangeAnimation();												// �ִϸ��̼� ��ȭ
	void FireWeapon(int x, int y);										// weapon �߻�
	void TakeAction();													// �Է�Ű

	inline void SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	inline POINTFLOAT GetPlayerHeadPos() { return this->headInfo.pos; }

	virtual ~Player() = default;
};

