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
		ObjectDir		moveDir = ObjectDir::DOWN;						// 이동 방향
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
		ObjectDir		moveDir = ObjectDir::DOWN;						// 이동 방향
		int				blinkEye = 0;									// 눈 깜빡임
	} headInfo;

private:
	Image*									otherStateImg = nullptr;
	WeaponManager*							weaponTear = nullptr;

	vector<vector<array<DOOR_INFO, 4 >>>*	doorInfo = nullptr;												// 문의 정보

	PlayerStates							playerState = PlayerStates::IDLE;								// 상태
	RECT									colliderRect = {};												// 충돌 처리용

	array<bool, 4>							enterNextDoor = { false };
	bool									isFire = false;													// 무기 발사

	char									text[64] = {};

	int										_stageSize = 0;													// Stage Size
	int										currColumn = 0;
	int										currRow = 0;
	int										fireDelay = 0;													// 무기 발사 지연

public:
	virtual void							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;
	virtual void							OnDebug(HDC hdc) override;

	void									ApplyAttackFrame(int attackFrame, int usuallyFrame);
	void									ApplyBodyFrame(ObjectDir moveDir, int bodyFrameY);				// Body 프레임 변화
	void									ApplyHeadFrame(ObjectDir moveDir, int headFrameX);				// Head 프레임 변화
	void									ApplyHeadDir(ObjectDir moveDir, int attckFrame);				// Head 방향 변화
	void									BlinkEye();														// 눈 깜빡임
	void									ChangeAnimation();												// 애니메이션 변화
	void									ChangeAttackFrame();
	void									ChangeBodyFrame();												
	void									ChangeHeadFrame();												
	void									ChangeHeadDir();												
	bool									ClosedEye();													// 눈이 감긴 상태
	void									DevideHeadDir(int pointY, float section, int dir1, int dir2);	// 입력한 위치 바라보기
	void									FireWeapon(int x, int y);										// weapon 발사
	void									Move();															// 움직임
	void									TakeAction();													// 입력키

	float									CalculateSlope(RECT rc);										// 기울기

	inline void								SetCurrCloumn(int column) { this->currColumn = column; }
	inline void								SetCurrRow(int row) { this->currRow = row; }
	inline void								SetEnterNextUpDoor(bool enterNextDoor) { this->enterNextDoor[0] = enterNextDoor; }
	inline void								SetEnterNextDownDoor(bool enterNextDoor) { this->enterNextDoor[1] = enterNextDoor; }
	inline void								SetEnterNextLeftDoor(bool enterNextDoor) { this->enterNextDoor[2] = enterNextDoor; }
	inline void								SetEnterNextRightDoor(bool enterNextDoor) { this->enterNextDoor[3] = enterNextDoor; }
	inline void								SetDoorInfo(vector<vector<array<DOOR_INFO, 4 >>>* doorInfo) { this->doorInfo = doorInfo; }
	inline void								SetIsFire(bool isFire) { this->isFire = isFire; }
	inline void								SetPlayerBodyPos(POINTFLOAT pos) { this->bodyInfo.pos = pos; }
	inline void								SetPlayerBodyShape(RECT rc) { this->bodyInfo.shape = rc; }
	inline void								SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	inline void								SetPlayerHeadShape(RECT rc) { this->headInfo.shape = rc; }
	inline void								SetPlayerHeadMoveDir(ObjectDir moveDir) { this->headInfo.moveDir = moveDir; }
	inline void								SetStageSize(int stageSize) { this->_stageSize = stageSize; }

	inline array<bool, 4>					GetEnterNextDoor() { return this->enterNextDoor; }
	inline bool								GetIsFire() { return this->isFire; }
	inline POINTFLOAT						GetPlayerBodyPos() { return this->bodyInfo.pos; }
	inline RECT								GetPlayerBodyShape() { return this->bodyInfo.shape; }
	inline POINTFLOAT						GetPlayerHeadPos() { return this->headInfo.pos; }
	inline RECT								GetPlayerHeadShape() { return this->headInfo.shape; }
	inline ObjectDir						GetPlayerHeadMoveDir() { return this->headInfo.moveDir; }

	virtual ~Player() = default;
};

