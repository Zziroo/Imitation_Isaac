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
		int			blinkEye = 0;										// �� ������
	} headInfo;

private:
	Image*			otherStateImg = nullptr;

	ObjectStates	playerState = ObjectStates::IDLE;					// ����

	int				loadWeapon = TAKE_LOAD_WEAPON_TIME;					// ���� ������ �ɸ��� �ð�
	int				takeLoadWeapon = LOADING_CONPLETE_TIME;				// ���� ���� �Ϸ�
	bool			isFire = false;										// ���� �߻�
	char			text[64] = {};										// MousePointer

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	void ApplyAttackFrame(int attackFrame, int usuallyFrame);
	void ApplyBodyFrame(MoveDir moveDir, int bodyFrameY);				// Body ������ ��ȭ
	void ApplyHeadFrame(MoveDir moveDir, int headFrameX);				// Head ������ ��ȭ
	void ApplyHeadDir(MoveDir moveDir, int attckFrame);					// Head ���� ��ȭ
	void BlinkEye();													// �� ������
	void ChangeAnimation();												// �ִϸ��̼� ��ȭ
	void ChangeAttackFrame();
	void ChangeBodyFrame();												
	void ChangeHeadFrame();												
	void ChangeHeadDir();												
	bool ClosedEye();													// ���� ���� ����
	void DevideHeadDir(int pointY, int section, int dir1, int dir2);	// �Է��� ��ġ �ٶ󺸱�
	void FireWeapon(int x, int y);										// weapon �߻�
	void Move();														// ������
	void TakeAction();													// �Է�Ű

	float CalculateSlope(RECT rc);										// ����

	inline void SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	inline POINTFLOAT GetPlayerHeadPos() { return this->headInfo.pos; }

	virtual ~Player() = default;
};

