#pragma once

#include "GameObject.h"

class Image;
class Weapon : public GameObject
{
private:
	Image*	tear = nullptr;

	MoveDir	weaponDir = MoveDir::DOWN;	// 무기의 방향

	bool	isFire = false;				// 발사 됐는지

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	void InitializeWeapon();

	inline void SetIsFire(bool isFire) { this->isFire = isFire; }
	inline void SetMoveDir(MoveDir weaponDir) { this->weaponDir = weaponDir; }

	inline bool GetIsFire() { return this->isFire; }
	inline MoveDir GetMoveDir() { return this->weaponDir; }

	virtual ~Weapon() = default;
};

