#pragma once

#include "Monster.h"

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
	BOSS_MONSTER_INFO		monsterInfo;

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;
	
	void					DesignateBossMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);

	virtual ~BossMonster() = default;
};

