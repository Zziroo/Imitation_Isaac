#pragma once

#include "GameObject.h"

class Image;
class Obstacle : public GameObject
{
private:
	typedef struct ObstacleInfo
	{
		Image*				img = nullptr;
		ObstacleTypes		type = ObstacleTypes::NONE;

		bool				doDamage = false;
		bool				isExistItem = false;
		bool				isSlowed = false;
	} OBSTACLE_INFO;

private:
	OBSTACLE_INFO			obstacleInfo;

	float					resistSpeed = 0.0f;

public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					SubstituteObstacleShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);

	inline float			GetObjecMoveSpeed() {};		// 오브젝트들의 이동 속도를 느리게 하기 위해 받아와야할 값
	inline ObstacleTypes	GetObstacleType() { return this->obstacleInfo.type; }

	inline void				SetObstaclePos(POINTFLOAT pos) { this->pos = pos; }
	inline void				SetObstaclePosX(float pos) { this->pos.x = pos; }
	inline void				SetObstaclePosY(float pos) { this->pos.y = pos; }
	inline void				SetObstacleType(ObstacleTypes type) { this->obstacleInfo.type = type ; }

	virtual ~Obstacle() = default;
};

