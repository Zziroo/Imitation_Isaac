#pragma once

#include "GameObject.h"

class Weapon;
class Player;
class WeaponManager : public GameObject
{
private:
	vector<Weapon*> vecWeapon;

	Player*			owner = nullptr;

	int				maxWeaponCount = WEAPON_MAX_COUNT;	// 최대 무기 수량

public:
	virtual void	Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	void			WeaponFire();

	inline void		SetOwner(Player* owner) { this->owner = owner;}

	virtual ~WeaponManager() = default;
};

