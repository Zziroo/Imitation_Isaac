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

private:
	Button*								button = nullptr;

	Image*								backGroundImg = nullptr;
	Image*								indicativeAreaImg = nullptr;
	Image*								obstacleImg = nullptr;
	Image*								sampleBackGroundImg = nullptr;
	Image*								sampleObstacleImg = nullptr;

	RECT								colliderRect = {};

	vector<Obstacle*>					obstacle;
	vector<Obstacle*>					loadObstacle;
	vector<SAMPLE_INFO>					sampleObstacleInfo;				// SampleObstacleInfo
	vector<STORE_OBSTACLE_INFO>			tempStoreObstacleInfo;			// �ӽ÷� ObstacleInfo�� �����صδ� ���� => Save Button Ŭ�� �� storeObstacle�� ���� ����
	vector<vector<STORE_OBSTACLE_INFO>>	storeObstacle;					// Obstacle�� pos�� type�� �����ϴ� ���� => vector<> : Roomtype, vector<vector<> : Obstacle�� pos�� type��  �ȿ� ����>

	bool								clickedSampleObstacle = false;
	bool								debugMode = false;

	char								text[64] = {};

	int									resizeNum = 4;					// �ʱ� Obstacle* ũ��
	int									roomTypeIndex = 3;				// �ʿ��� RoomTypes ��ŭ vector<vector<STORE_SAMPLE_INFO>> ũ�� ���� => ���� CURSE, ITEM, NORMAL
	int									saveIndex[3] = {};
	int									storeIndex = 0;					// MainBoard�� �����ָ� �����ϴ� Index

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
	void								Load(int roomType, int loadIndex);
	void								Save(int roomType, int saveIndex, int obstacleCount);
	void								StoreObstacle();
	void								StoreCurseRoomObstacle(int totalSize);
	void								StoreItemRoomObstacle(int totalSize);
	void								StoreNormalRoomObstacle(int totalSize);
	
	virtual ~ObstacleToolScene() = default;
};

