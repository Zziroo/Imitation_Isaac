#pragma once

#include "Scene.h"

class Image;
class Player;
class InGameScene : public Scene
{
private:
	Image*	sampleImg = nullptr;
	Player*	playerIsaac = nullptr;

protected:

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual ~InGameScene() = default;
};

