#pragma once

#include "Scene.h"

class Image;
class TitleScene : public Scene
{
private:
	Image*		titleImg = nullptr;
	POINTFLOAT	pos = { WIN_SIZE_X * 0.5f, WIN_SIZE_Y * 0.5f };
	int			elapsedScene = 0;

protected:

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void ChangeTitleImage();

	virtual ~TitleScene() = default;
};

