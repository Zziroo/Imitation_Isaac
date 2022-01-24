#pragma once

#include "GameObject.h"

class Image;
class NextStageDoor : public GameObject
{
private:
	Image*				img = nullptr;

	bool				openNextStageDoor = false;

public:
	virtual void		Init() override;
	virtual void		Release() override;
	virtual void		Update() override;
	virtual void		Render(HDC hdc) override;
	virtual void		OnDebug(HDC hdc) override;

	void				OpenNextStageDoorAnimation();

	bool				GetOpenNextStageDoor() { return this->openNextStageDoor; }

	void				SetOpenNextStageDoor(bool open) { this->openNextStageDoor = open; }

	virtual ~NextStageDoor() = default;
};

