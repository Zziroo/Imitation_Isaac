#pragma once

#include "Scene.h"

class Button;
class Image;
class Obstacle;
class ObstacleToolScene : public Scene
{
private:
	typedef struct tagSampleInfo
	{
		ObstacleTypes					sampleType = ObstacleTypes::NONE;
		POINTFLOAT						pos = {};
		RECT							shape = {};
	} SAMPLE_INFO;

	typedef struct tagStoreSampleInfo
	{
		ObstacleTypes					sampleType = ObstacleTypes::NONE;
		POINTFLOAT						pos = {};
	} STORE_SAMPLE_INFO;

private:
	Button*								button = nullptr;

	Image*								backGroundImg = nullptr;
	Image*								indicativeAreaImg = nullptr;
	Image*								obstacleImg = nullptr;
	Image*								sampleBackGroundImg = nullptr;
	Image*								sampleObstacleImg = nullptr;

	RECT								colliderRect = {};

	RoomTypes							roomInfo = RoomTypes::NONE;

	vector<Obstacle*>					obstacle;
	vector<SAMPLE_INFO>					sampleObstacle;
	vector<vector<STORE_SAMPLE_INFO>>	storeObstacle;

	bool								clickedSampleObstacle = false;
	bool								debugMode = false;

	char								text[64] = {};

	int									resizeNum = 4;
	int									storeIndex = 0;

public:
	virtual HRESULT						Init() override;
	virtual void						Release() override;
	virtual void						Update() override;
	virtual void						Render(HDC hdc) override;

	void								ClickedObstacle();
	void								DrawSampleRect(int index, float sizeX, float sizeY);
	void								EstablishSampleType();

	virtual ~ObstacleToolScene() = default;
};

