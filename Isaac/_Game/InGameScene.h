#pragma once

#include "Scene.h"

class Image;
class Player;
class WeaponManager;
class InGameScene : public Scene
{
private:
	Image*			sampleImg = nullptr;
	Player*			playerIsaac = nullptr;
	WeaponManager*	playerWeapon = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	virtual ~InGameScene() = default;
};

