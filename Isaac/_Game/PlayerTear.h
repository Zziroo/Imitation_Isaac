#pragma once

#include "GameObject.h"

#define MAX_COUNT 50

class Image;
class Player;
class Tear;
class PlayerTear : public GameObject
{
private:
	Image*			tearImg = nullptr;
	Player*			owner = nullptr;

	vector<Tear*>	vecTear;

	int				maxTearCount = MAX_COUNT;

public:
	virtual void	Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	void			CollideWithNormalMonster();
	void			CollideWithObstacle();
	void			Fire();

	void			SetOwner(Player* owner) { this->owner = owner; }

	virtual ~PlayerTear() noexcept;
};

