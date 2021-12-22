#pragma once

#include "GameObject.h"

enum class MonsterStates { IDLE, ATTACK, DEAD, NONE };

class Monster : public GameObject
{
private:

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	virtual ~Monster() = default;
};

