#pragma once

#include "Weapon.h"

class GameObject;
class Image;
class Tear : public Weapon
{
private:
	GameObject*			owner = nullptr;
	Image*				tear = nullptr;

	ObjectDir			tearDir = ObjectDir::NONE;		// 무기의 방향

	bool				isFire = false;					// 발사 됐는지

public:
	virtual void		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		OnDebug(HDC hdc) override;

	void				Init(GameObject* owner);
	void				InitializeWeapon();

	bool				GetIsFire() { return this->isFire; }
	ObjectDir			GetMoveDir() { return this->tearDir; }

	void				SetIsFire(bool isFire) { this->isFire = isFire; }
	void				SetMoveDir(ObjectDir tearDir) { this->tearDir = tearDir; }
	void				SetOwner(GameObject* owner) { this->owner = owner; }

	virtual ~Tear() = default;
};

