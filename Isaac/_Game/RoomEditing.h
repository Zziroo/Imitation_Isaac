#pragma once

#include "GameObject.h"

class MapEditing;
class RoomEditing : public GameObject
{
private:


public:
	virtual void		Init() override;

	virtual	~RoomEditing() = default;
};

