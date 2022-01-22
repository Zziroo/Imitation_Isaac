#pragma once

#include "UI.h"

class Image;
class BossMonsterHP : public UI
{
private:
	Image*			img = nullptr;

public:
	virtual void	Init() override;
	virtual void	Release() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;
	virtual void	OnDebug(HDC hdc) override;

	virtual ~BossMonsterHP() = default;
};

