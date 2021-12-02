#pragma once

#include "Scene.h"

class Button;
class ButtonFunction;
class Image;
class TilemapToolScene : public Scene
{
private:
	Button*			button = nullptr;
	ButtonFunction* quitFunc = nullptr;

	Image*			backGround = nullptr;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual ~TilemapToolScene() = default;
};

