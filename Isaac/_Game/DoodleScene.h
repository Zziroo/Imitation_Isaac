#pragma once

#include "Scene.h"

class Image;
class NormalMonster;
class Obstacle;
class DoodleScene : public Scene
{
private:
	Image*					sampleObstacleImg = nullptr;
	Image*					samplePlayerImg = nullptr;
	NormalMonster*			normalMonster[3] = { nullptr };
	Obstacle*				obstacle[9] = { nullptr };

	POINTFLOAT				pos = { 640.0f, 250.0f };
	float					size = 70.0f;
	float					moveSpeed = 500.0f;
	RECT					shape = {
		(LONG)(pos.x - (size * DEVIDE_HALF)),
		(LONG)(pos.y - (size * DEVIDE_HALF) - 10),
		(LONG)(pos.x + (size * DEVIDE_HALF)),
		(LONG)(pos.y + (size * DEVIDE_HALF) + 10)
	};

public:
	virtual HRESULT			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;

	void					Move();

	virtual ~DoodleScene() = default;
};

