#pragma once

#include "UI.h"

class Image;
class BossMonsterHP : public UI
{
private:
	Image*			img[2] = { nullptr };

	POINTFLOAT		bossPos[2] = {};

	bool			isGameClear = false;

	float			bossMonsterHP = 100.0f;
	float			playerAttackValue = 0.0f;

public:
	virtual void	Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;
	virtual void	OnDebug(HDC hdc) override;

	void			DamagedByPlayerTear();
	void			GameClear();

	float			GetBossMonsterHP() { return this->bossMonsterHP; }
	bool			GetIsGameClear() { return isGameClear; }

	void			SetPlayerAttackValue(float attackValue) { this->playerAttackValue = attackValue; }

	virtual ~BossMonsterHP() = default;
};
