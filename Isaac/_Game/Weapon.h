#pragma once

#include "GameObject.h"

class Image;
class Weapon : public GameObject
{
private:
	Image*	tear = nullptr;

	MoveDir	weaponDir = MoveDir::DOWN;	// ������ ����

	bool	isFire = false;				// �߻� �ƴ���

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void InitializeWeapon();

	inline void SetIsFire(bool isFire) { this->isFire = isFire; }
	inline void SetMoveDir(MoveDir weaponDir) { this->weaponDir = weaponDir; }

	inline bool GetIsFire() { return this->isFire; }
	inline MoveDir GetMoveDir() { return this->weaponDir; }

	virtual ~Weapon() = default;
};

