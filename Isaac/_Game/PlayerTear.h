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
	bool			attackNormalMonster = false;

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
	bool			GetAttackedNormalMonster() { return attackNormalMonster; }

	void			SetAttackedBossMonster(bool attack) { this->attackBossMonster = attack; }
	void			SetAttackedNormalMonster(bool attack) { this->attackNormalMonster = attack; }

	virtual ~PlayerTear() noexcept;
};

