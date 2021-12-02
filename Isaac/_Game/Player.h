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
		MoveDir		moveDir = MoveDir::DOWN;							// 이동 방향
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
		MoveDir		moveDir = MoveDir::DOWN;							// 이동 방향
		int			blinkEye = 0;										// 눈 깜빡임
	} headInfo;

private:
	Image*			otherStateImg = nullptr;

	ObjectStates	playerState = ObjectStates::IDLE;					// 상태

	int				loadWeapon = TAKE_LOAD_WEAPON_TIME;					// 무기 장전에 걸리는 시간
	int				takeLoadWeapon = LOADING_CONPLETE_TIME;				// 무기 장전 완료
	bool			isFire = false;										// 무기 발사
	char			text[64] = {};										// MousePointer

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	void ApplyAttackFrame(int attackFrame, int usuallyFrame);
	void ApplyBodyFrame(MoveDir moveDir, int bodyFrameY);				// Body 프레임 변화
	void ApplyHeadFrame(MoveDir moveDir, int headFrameX);				// Head 프레임 변화
	void ApplyHeadDir(MoveDir moveDir, int attckFrame);					// Head 방향 변화
	void BlinkEye();													// 눈 깜빡임
	void ChangeAnimation();												// 애니메이션 변화
	void ChangeAttackFrame();
	void ChangeBodyFrame();												
	void ChangeHeadFrame();												
	void ChangeHeadDir();												
	bool ClosedEye();													// 눈이 감긴 상태
	void DevideHeadDir(int pointY, int section, int dir1, int dir2);	// 입력한 위치 바라보기
	void FireWeapon(int x, int y);										// weapon 발사
	void Move();														// 움직임
	void TakeAction();													// 입력키

	float CalculateSlope(RECT rc);										// 기울기

	inline void SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	inline POINTFLOAT GetPlayerHeadPos() { return this->headInfo.pos; }

	virtual ~Player() = default;
};

