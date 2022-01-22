#pragma once

#include "UI.h"

class Image;
class PlayerHP : public UI
{
private:
	struct PlayerHPInfo
	{
		POINTFLOAT			pos = {};
		Image*				img = nullptr;

		int					frameX = 0;
		int					frameY = 0;
	};

private:
	vector<PlayerHPInfo>	playerHPInfo;

	POINTFLOAT				startPos = { 64, 64 };

	int						playerHP = 0;
	int						playerHPImageCount = 0;			// playerHP를 보고 playerHPInfo 초기화 할 변수

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					Hurt();

	void					SetPlayerHP(int HP) { this->playerHP = HP; }

	virtual ~PlayerHP() = default;
};

