#pragma once

#include "GameObject.h"

class Monster : public GameObject
{
private:

protected:

public:
	virtual void Init() override;
	virtual HRESULT FindIamge() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual ~Monster() = default;
};

