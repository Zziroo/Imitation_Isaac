#pragma once

#include "Weapon.h"

enum class FireMethods { GUIEDED, NORMAL, ROTATE, SPRINKLE, NONE };

class Image;
class Tear : public Weapon
{
private:
	Image*				tearImg = nullptr;

	ObjectDir			tearDir = ObjectDir::NONE;		// 무기의 방향

	bool				isFire = false;					// 발사 됐는지

public:
	virtual void		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		OnDebug(HDC hdc) override;

	void				Fire(FireMethods method);
	void				GiveDirectionNormalTear();
	void				InitializeSize();
	void				InitializeWeapon();

	bool				GetIsFire() { return this->isFire; }
	ObjectDir			GetMoveDir() { return this->tearDir; }

	void				SetIsFire(bool isFire) { this->isFire = isFire; }
	void				SetMoveDir(ObjectDir tearDir) { this->tearDir = tearDir; }
	void				SetTearImage(Image* img) { this->tearImg = img; }

	virtual ~Tear() = default;
};

