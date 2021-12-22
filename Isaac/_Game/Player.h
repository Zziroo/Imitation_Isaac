#pragma once

#include "GameObject.h"

class Image;
class Obstacle;
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

	vector<vector<array<DOOR_INFO, 4>>>*	doorInfo = nullptr;																			// 문의 정보
	vector<vector<vector<Obstacle*>>>*		obstacle = nullptr; 
	vector<vector<FILE_INFO>>				obstacleFileInfo;

	PlayerStates							playerState = PlayerStates::IDLE;															// 상태
	RECT									colliderRect = {};																			// 충돌 처리용

	array<bool, 4>							enterNextDoor = { false };
	bool									isFire = false;																				// 무기 발사

	char									text[64] = {};

	int										stageSize = 0;																				// Stage Size
	int										currColumn = 0;
	int										currRow = 0;
	int										fireDelay = 0;																				// 무기 발사 지연

public:
	virtual void							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;
	virtual void							OnDebug(HDC hdc) override;

	void									ApplyAttackFrame(int attackFrame, int usuallyFrame);
	void									ApplyBodyFrame(ObjectDir moveDir, int bodyFrameY);											// Body 프레임 변화
	void									ApplyHeadFrame(ObjectDir moveDir, int headFrameX);											// Head 프레임 변화
	void									ApplyHeadDir(ObjectDir moveDir, int attckFrame);											// Head 방향 변화
	void									BlinkEye();																					// 눈 깜빡임
	float									CalculateSlope(RECT rc);																	// 기울기
	void									ChangeAnimation();																			// 애니메이션 변화
	void									ChangeAttackFrame();
	void									ChangeBodyFrame();
	void									ChangeHeadFrame();
	void									ChangeHeadDir();
	bool									ClosedEye();																				// 눈이 감긴 상태
	void									CollideWithDoor(POINTFLOAT bosyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape);
	void									CollideWithTilemap(POINTFLOAT bosyPos, RECT bodyShape, POINTFLOAT headPos, RECT headShape);
	void									DevideHeadDir(int pointY, float section, int dir1, int dir2);								// 입력한 위치 바라보기
	void									FireWeapon(int x, int y);																	// weapon 발사
	void									Move();																						// 움직임
	void									TakeAction();																				// 입력키
	void									WeaponDelay();

	array<bool, 4>							GetEnterNextDoor() { return this->enterNextDoor; }
	bool									GetIsFire() { return this->isFire; }
	POINTFLOAT								GetPlayerBodyPos() { return this->bodyInfo.pos; }
	RECT									GetPlayerBodyShape() { return this->bodyInfo.shape; }
	POINTFLOAT								GetPlayerHeadPos() { return this->headInfo.pos; }
	RECT									GetPlayerHeadShape() { return this->headInfo.shape; }
	ObjectDir								GetPlayerHeadMoveDir() { return this->headInfo.moveDir; }

	void									SetCurrCloumn(int column) { this->currColumn = column; }
	void									SetCurrRow(int row) { this->currRow = row; }
	void									SetEnterNextUpDoor(bool enterNextDoor) { this->enterNextDoor[0] = enterNextDoor; }
	void									SetEnterNextDownDoor(bool enterNextDoor) { this->enterNextDoor[1] = enterNextDoor; }
	void									SetEnterNextLeftDoor(bool enterNextDoor) { this->enterNextDoor[2] = enterNextDoor; }
	void									SetEnterNextRightDoor(bool enterNextDoor) { this->enterNextDoor[3] = enterNextDoor; }
	void									SetDoorInfo(vector<vector<array<DOOR_INFO, 4 >>>* doorInfo) { this->doorInfo = doorInfo; }
	void									SetIsFire(bool isFire) { this->isFire = isFire; }
	void									SetObstacleInfo(vector<vector<vector<Obstacle*>>>* obstacle) { this->obstacle = obstacle; }
	void									SetObstacleCountInfo(vector<vector<FILE_INFO>> obstacleFileInfo) { this->obstacleFileInfo = obstacleFileInfo; }
	void									SetPlayerBodyPos(POINTFLOAT pos) { this->bodyInfo.pos = pos; }
	void									SetPlayerBodyShape(RECT rc) { this->bodyInfo.shape = rc; }
	void									SetPlayerHeadPos(POINTFLOAT pos) { this->headInfo.pos = pos; }
	void									SetPlayerHeadShape(RECT rc) { this->headInfo.shape = rc; }
	void									SetPlayerHeadMoveDir(ObjectDir moveDir) { this->headInfo.moveDir = moveDir; }
	void									SetStageSize(int stageSize) { this->stageSize = stageSize; }

	virtual ~Player() = default;
};

