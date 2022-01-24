#pragma once

#include "Monster.h"

class AStar;
class Image;
class BossMonster : public Monster
{
private:
	typedef struct BossMonsterInfo
	{
		Image*								img = nullptr;
		BossMonsterTypes					type = BossMonsterTypes::NONE;
		MonsterStates						state = MonsterStates::IDLE;
		ObjectDir							moveDir = ObjectDir::NONE;

		bool								isAlive = true;
	} BOSS_MONSTER_INFO;

	typedef struct InitializeNormalMonsterInfo
	{
		POINTFLOAT							pos = {};
		NormalMonsterTypes					type = NormalMonsterTypes::NONE;
	} INITIALIZE_NORMAL_MONSTER_INFO;

private:
	AStar*									aStar = nullptr;

	stack<Pos>								pathWay;

	BOSS_MONSTER_INFO						monsterInfo;

	vector<INITIALIZE_NORMAL_MONSTER_INFO>	normalMonsterInfo;

	POINTFLOAT								normalMonsterSpawnPos[8] = {};

#ifdef _DEBUG
	RECT									spawnShape[8] = {};
#endif

	bool									isSpawnNormalMonster = false;

	float									elapsedChangeMonsterState = 0.0f;
	float									elapsedCreatenormalMonsterAnimation = 0.0f;

public:
	virtual void							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;
	virtual void							OnDebug(HDC hdc) override;
	
	void									ApproachTargetPoint();
	void									ChangeBossMonsterState();
	void									DesignateBossMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);
	void									DesignateNormalMonsterInfo();
	void									DesignateNormalMonsterSpawnPositionInfo();
	void									DesignateNormalMonsterTypeInfo();
	void									DesignateMonsterSpawnPosition();
	void									InitializeBossMonsterAnimation();
	void									InitializeNormalMonsterInfo();
	void									Move();
	void									ProgressNormalMonsterSpawnAnimation();

	RECT									GetBossMonsterShape() { return this->shape; }
	MonsterStates							GetBossMonsterState() { return this->monsterInfo.state; }
	bool									GetIsAlive() { return this->monsterInfo.isAlive; }
	vector<INITIALIZE_NORMAL_MONSTER_INFO>	GetInitializeNormalMonsterInfo() { return this->normalMonsterInfo; }

	void									SetBossMonsterAStar(AStar* aStar) { this->aStar = aStar; }
	void									SetBossMonsterPathWay(stack<Pos> way) { this->pathWay = way; }
	void									SetBossmonsterState(MonsterStates state) { this->monsterInfo.state = state; }
	void									SetIsAlive(bool isAlive) { this->monsterInfo.isAlive = isAlive; }

	virtual ~BossMonster() = default;
};

