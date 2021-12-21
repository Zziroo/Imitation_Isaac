#pragma once

#include "Monster.h"

enum class NormalMonsterTypes { FLY, ATTACKFLY, POOTER, NONE };

class Image;
class NormalMonster : public Monster
{
private:
	typedef struct NormalMonsterInfo
	{
		Image*				img = nullptr;
		ObjectDir			moveDir = ObjectDir::NONE;
		NormalMonsterTypes	type = NormalMonsterTypes::NONE;
	} NORMAL_MONSTER_INFO;

private:
	NORMAL_MONSTER_INFO		monsterInfo;

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					DeginateNorMalMonsterShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);

	NormalMonsterTypes		GetNormalMonsterType() { return this->monsterInfo.type; }

	void					SetNormalMonsterPos(POINTFLOAT pos) { this->pos = pos; }
	void					SetNormalMonsterPosX(float pos) { this->pos.x = pos; }
	void					SetNormalMonsterPosY(float pos) { this->pos.y = pos; }
	void					SetNormalMonsterType(NormalMonsterTypes type) { this->monsterInfo.type = type; }

	virtual ~NormalMonster() = default;
};

