#pragma once

#include "Monster.h"

class Image;
class NormalMonster : public Monster
{
private:
	typedef struct NormalMonsterInfo
	{
		Image*				img = nullptr;
		MonsterStates		state = MonsterStates::IDLE;
		NormalMonsterTypes	type = NormalMonsterTypes::NONE;
		ObjectDir			moveDir = ObjectDir::NONE;

		POINTFLOAT			pos = {};
		RECT				shape = {};

		int					elapsedAnimeCount = 0;
		float				moveSpeed = 0.0f;
		float				objectSize = 0.0f;
	} NORMAL_MONSTER_INFO;

private:
	NORMAL_MONSTER_INFO		monsterInfo;

	POINTFLOAT				targetPos = {};

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					AdvanceAnimation(int elapsedCount = 0);
	void					ChangeAnimation();
	void					Move();
	void					DesignateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);

	POINTFLOAT				GetNormalMonsterPos() { return this->monsterInfo.pos; }
	float					GetNormalMonsterPosX() { return this->monsterInfo.pos.x; }
	float					GetNormalMonsterPosY() { return this->monsterInfo.pos.y; }
	RECT					GetNormalMonsterShape() { return this->monsterInfo.shape; }
	NormalMonsterTypes		GetNormalMonsterType() { return this->monsterInfo.type; }

	void					SetNormalMonsterPos(POINTFLOAT pos) { this->monsterInfo.pos = pos; }
	void					SetNormalMonsterPosX(float pos) { this->monsterInfo.pos.x = pos; }
	void					SetNormalMonsterPosY(float pos) { this->monsterInfo.pos.y = pos; }
	void					SetNormalMonsterType(NormalMonsterTypes type) { this->monsterInfo.type = type; }
	void					SetTargetPos(POINTFLOAT pos) { this->targetPos = pos; }

	virtual ~NormalMonster() = default;
};

