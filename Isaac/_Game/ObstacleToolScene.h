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
	vector<Obstacle*>					loadObstacle;
	vector<SAMPLE_INFO>					sampleObstacleInfo;				// SampleObstacleInfo
	vector<STORE_SAMPLE_INFO>			tempStoreObstacleInfo;			// 임시로 ObstacleInfo를 저장해두는 공간 => Save Button 클릭 시 storeObstacle에 전부 저장
	vector<vector<STORE_SAMPLE_INFO>>	storeObstacle;					// Obstacle의 pos와 type을 저장하는 공간 => vector<> : Roomtype, vector<vector<> : Obstacle의 pos와 type을  안에 저장>

	bool								clickedSampleObstacle = false;
	bool								debugMode = false;

	char								text[64] = {};

	int									resizeNum = 4;					// 초기 Obstacle* 크기
	int									roomTypeIndex = 3;				// 필요한 RoomTypes 만큼 vector<vector<STORE_SAMPLE_INFO>> 크기 설정 => 현재 CURSE, ITEM, NORMAL
	int									saveIndex[3] = {};
	int									storeIndex = 0;					// MainBoard에 보여주며 저장하는 Index

public:
	virtual HRESULT						Init() override;
	virtual void						Release() override;
	virtual void						Update() override;
	virtual void						Render(HDC hdc) override;

	void								ClickedObstacle();
	void								DrawObstacle();
	void								DrawSampleRect(int index, float sizeX, float sizeY);
	void								EstablishSampleType();
	void								InitializeStoreSpace();
	void								Save(int roomType, int saveIndex, int obstacleCount);
	void								StoreObstacle();
	void								StoreCurseRoomObstacle(int totalSize);
	void								StoreItemRoomObstacle(int totalSize);
	void								StoreNormalRoomObstacle(int totalSize);

	void								Load(int roomType, int loadIndex);

	virtual ~ObstacleToolScene() = default;
};

