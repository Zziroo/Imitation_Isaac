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

		int					elapsedAnimeCount = 0;
	} OBSTACLE_INFO;

private:
	OBSTACLE_INFO			obstacleInfo;
	int						frameX = 0;
	int						frameY = 0;

	float					resistSpeed = 0.0f;

private:
	void					setNextFrameHelper(int& frame, int maxFrame);
public:
	virtual void			Init() override;
	virtual void			Release() override;
	virtual void			Update() override;
	virtual void			Render(HDC hdc) override;
	virtual void			OnDebug(HDC hdc) override;

	void					ChangeObstacleAnimation();
	void					DesignateObstacleShape(POINTFLOAT pos, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);
	void					DesignateObstacleShape(float posX, float posY, float size, float adjustSizeLeft = 0.0f, float adjustSizeTop = 0.0f, float adjustSizeRight = 0.0f, float adjustSizeBottom = 0.0f);
	void					SwitchDamageToPlayer();

	void					SetNextFrameX();
	void					SetNextFrameY();

	bool					IsMaxFrameX() const;
	bool					IsMaxFrameY() const;

	bool					GetObstacleDamaged() { return this->obstacleInfo.doDamage; }
	Image*					GetObstacleImage() { return this->obstacleInfo.img; }
	ObstacleTypes			GetObstacleType() { return this->obstacleInfo.type; }

	void					SetObstacleDamaged(bool doDamage) { this->obstacleInfo.doDamage = doDamage; }
	void					SetObstaclePos(POINTFLOAT pos) { this->pos = pos; }
	void					SetObstaclePosX(float pos) { this->pos.x = pos; }
	void					SetObstaclePosY(float pos) { this->pos.y = pos; }
	void					SetObstacleType(ObstacleTypes type) { this->obstacleInfo.type = type ; }
	void					SetFrameX(int frame) { frameX = frame; }
	void					SetFrameY(int frame) { frameY = frame; }

	virtual ~Obstacle() = default;
};

