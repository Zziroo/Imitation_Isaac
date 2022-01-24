#pragma once

#include "Monster.h"

class AStar;
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
	AStar*					aStar = nullptr;

	stack<Pos>				pathWay;

	NORMAL_MONSTER_INFO		monsterInfo;

	POINTFLOAT				targetPos = {};

	int						frameX = 0;
	int						frameY = 0;

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					AdvanceAnimation(int elapsedCount = 0);
	void					ApproachTargetPoint();
	void					ChangeAnimation();
	void					DesignateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);
	void					Move();

	bool					IsMaxFrameY() const;

	Image*					GetNormalMonsterImage() { return this->monsterInfo.img; }
	POINTFLOAT				GetNormalMonsterPos() { return this->monsterInfo.pos; }
	float					GetNormalMonsterPosX() { return this->monsterInfo.pos.x; }
	float					GetNormalMonsterPosY() { return this->monsterInfo.pos.y; }
	RECT					GetNormalMonsterShape() { return this->monsterInfo.shape; }
	NormalMonsterTypes		GetNormalMonsterType() { return this->monsterInfo.type; }

	void					SetNormalMonsterAStar(AStar* aStar) { this->aStar = aStar; }
	void					SetNormalMonsterPathWay(stack<Pos> way) { this->pathWay = way; }
	void					SetNormalMonsterPos(POINTFLOAT pos) { this->monsterInfo.pos = pos; }
	void					SetNormalMonsterPosX(float pos) { this->monsterInfo.pos.x = pos; }
	void					SetNormalMonsterPosY(float pos) { this->monsterInfo.pos.y = pos; }
	void					SetNormalMonsterState(MonsterStates state) { this->monsterInfo.state = state; }
	void					SetNormalMonsterType(NormalMonsterTypes type) { this->monsterInfo.type = type; }

	virtual ~NormalMonster() = default;
};

