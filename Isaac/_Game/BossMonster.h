#pragma once

#include "Monster.h"

class AStar;
class Image;
class BossMonster : public Monster
{
private:
	typedef struct BossMonsterInfo
	{
		Image*				img = nullptr;
		BossMonsterTypes	type = BossMonsterTypes::NONE;
		MonsterStates		state = MonsterStates::IDLE;
		ObjectDir			moveDir = ObjectDir::NONE;
	} BOSS_MONSTER_INFO;

private:
	AStar*					aStar = nullptr;

	stack<Pos>				pathWay;

	BOSS_MONSTER_INFO		monsterInfo;

	POINTFLOAT				normalMonsterSpawnPos[8] = {};

#ifdef _DEBUG
	RECT					spawnShape[8] = {};
#endif

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;
	
	void					DesignateBossMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);

	RECT GetBossMonsterShape() { return this->shape; }
	MonsterStates			GetBossMonsterState() { return this->monsterInfo.state; }

	void					SetBossMonsterAStar(AStar* aStar) { this->aStar = aStar; }
	void					SetBossMonsterPathWay(stack<Pos> way) { this->pathWay = way; }
	void					SetBossmonsterState(MonsterStates state) { this->monsterInfo.state = state; }

	virtual ~BossMonster() = default;
};

