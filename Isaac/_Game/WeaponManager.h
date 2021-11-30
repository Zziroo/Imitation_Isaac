#pragma once

#include <vector>
#include "GameObject.h"

class Weapon;
class Player;
class WeaponManager : public GameObject
{
private:
	vector<Weapon*> vecWeapon;

	Player* owner = nullptr;

	int maxWeaponCount = 100;		// 최대 무기 수량

protected:

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void WeaponFire(MoveDir moveDir);

	inline void SetOwner(Player* owner) { this->owner = owner;}

	virtual ~WeaponManager() = default;
};

