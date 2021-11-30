#pragma once

#include <vector>
#include "GameObject.h"

class Weapon;
class WeaponManager : public GameObject
{
private:
	vector<Weapon*> vecWeapon;

	int maxWeaponCount = 100;		// 최대 무기 수량

protected:

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void WeaponFire(POINTFLOAT pos, MoveDir moveDir);

	virtual ~WeaponManager() = default;
};

