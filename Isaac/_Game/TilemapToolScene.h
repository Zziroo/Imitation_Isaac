#pragma once

#include "Scene.h"

class TilemapToolScene : public Scene
{
private:

protected:

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual ~TilemapToolScene() = default;
};

