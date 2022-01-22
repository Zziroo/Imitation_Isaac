#pragma once

#include "GameObject.h"

class Image;
class Tear;
class PlayerTear : public GameObject
{
private:
	Image*			tearImg = nullptr;

	vector<Tear*>	vecTear;

	bool			attackBossMonster = false;

	int				maxTearCount = MAX_COUNT;

public:
	virtual void	Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	void			CollideWithBossMonster();
	void			CollideWithNormalMonster();
	void			CollideWithObstacle();
	void			ExtinctWeapon();
	void			Fire();

	bool			GetAttackedBossMonster() { return attackBossMonster; }

	void			SetAttackedBossMonster(bool attack) { this->attackBossMonster = attack; }

	virtual ~PlayerTear() noexcept;
};

