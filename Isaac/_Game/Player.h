#pragma once

#include "GameObject.h"

class Image;
class WeaponManager;
class Player : public GameObject
{
private:
	struct PlayerBodyInfo
	{
		POINTFLOAT		pos = {
			(FLOAT)PLAYER_BODY_POS_X,									// Pos.x
			(FLOAT)PLAYER_BODY_POS_Y									// Pos.Y
		};
		float			size = PLAYER_BODYSIZE;
		RECT			shape = {
			(LONG)(pos.x - (size * DEVIDE_HALF) - ADJUST_SIZE_14),		// Left
			(LONG)(pos.y - (size * DEVIDE_HALF)),						// Top
			(LONG)(pos.x + (size * DEVIDE_HALF) + ADJUST_SIZE_14),		// Right
			(LONG)(pos.y + (size * DEVIDE_HALF))						// Bottom
		};
		Image*			image = nullptr;
		ObjectDir		moveDir = ObjectDir::DOWN;						// �̵� ����
	} bodyInfo;
	struct PlayerHeadInfo
	{
		POINTFLOAT		pos = {
			(FLOAT)PLAYER_HEAD_POS_X,									// Pos.x
			(FLOAT)PLAYER_HEAD_POS_Y									// Pos.Y
		};
		float			size = PLAYER_HEADSIZE;
		RECT			shape = {
			(LONG)(pos.x - (size * DEVIDE_HALF) - ADJUST_SIZE_05),		// Left
			(LONG)(pos.y - (size * DEVIDE_HALF)),						// Top
			(LONG)(pos.x + (size * DEVIDE_HALF) + ADJUST_SIZE_05),		// Right
			(LONG)(pos.y + (size * DEVIDE_HALF))						// Bottom
		};
		Image*			image = nullptr;
		ObjectDir		moveDir = ObjectDir::DOWN;						// �̵� ����
		int				blinkEye = 0;									// �� ������
	} headInfo;

private:
	Image*				otherStateImg = nullptr;
	WeaponManager*		weaponTear = nullptr;

	PlayerStates		playerState = PlayerStates::IDLE;				// ����
	RECT				colliderRect = {};								// ���� �浹 ó����

	bool				isFire = false;									// ���� �߻�
	int					fireDelay = 0;									// ���� �߻� ����

	char				text[64] = {};

public:
	virtual void		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		OnDebug(HDC hdc) override;

	void				ApplyAttackFrame(int attackFrame, int usuallyFrame);
	void				ApplyBodyFrame(ObjectDir moveDir, int bodyFrameY);				// Body ������ ��ȭ
	void				ApplyHeadFrame(ObjectDir moveDir, int headFrameX);				// Head ������ ��ȭ
	void				ApplyHeadDir(ObjectDir moveDir, int attckFrame);					// Head ���� ��ȭ
	void				BlinkEye();														// �� ������
	void				ChangeAnimation();												// �ִϸ��̼� ��ȭ
	void				ChangeAttackFrame();
	void				ChangeBodyFrame();												
	void				ChangeHeadFrame();												
	void				ChangeHeadDir();												
	bool				ClosedEye();													// ���� ���� ����
	void				DevideHeadDir(int pointY, float section, int dir1, int dir2);	// �Է��� ��ġ �ٶ󺸱�
	void				FireWeapon(int x, int y);										// weapon �߻�
	void				Move();															// ������
	void				TakeAction();													// �Է�Ű

	float				CalculateSlope(RECT rc);										// ����

	inline void			SetIsFire(bool isFire) { this->isFire = isFire; }
	inline void			SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	inline void			SetPlayerHeadMoveDir(ObjectDir moveDir) { this->headInfo.moveDir = moveDir; }

	inline bool			GetIsFire() { return this->isFire; }
	inline POINTFLOAT	GetPlayerHeadPos() { return this->headInfo.pos; }
	inline ObjectDir	GetPlayerHeadMoveDir() { return this->headInfo.moveDir; }

	virtual ~Player() = default;
};

