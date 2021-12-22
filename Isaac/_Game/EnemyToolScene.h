#pragma once

#include "Scene.h"


class Button;
class Image;
class NormalMonster;
class EnemyToolScene : public Scene
{
private:
	typedef struct normalMonsterSampleInfo
	{
		NormalMonsterTypes					sampleType = NormalMonsterTypes::NONE;
		POINTFLOAT							pos = {};
		RECT								shape = {};
	} SAMPLE_NORMAL_MONSTER_INFO;

private:
	Button*									button = nullptr;

	Image*									backGroundImg = nullptr;
	Image*									indicativeAreaImg = nullptr;
	Image*									normalMonsterImg = nullptr;
	Image*									sampleBackGroundImg = nullptr;
	Image*									sampleNormalMonsterImg = nullptr;

	RECT									colliderRect = {};

	vector<NormalMonster*>					normalMonster;
	vector<NormalMonster*>					loadNormalMonster;
	vector<SAMPLE_NORMAL_MONSTER_INFO>		sampleNormalMonsterInfo;
	vector<STORE_NORMAL_MONSTER_INFO>		storeNormalMonster;						// NormalMonster의 pos type을 저장하는 공간
	vector<STORE_NORMAL_MONSTER_INFO>		tempStoreNormalMonsterInfo;				// 임시로 NormalMonsterInfo를 저장해두는 공간

	bool									clickedSampleNormalMonster = false;
	bool									debugMode = false;

	char									text[64] = {};

	int										resizeNum = 4;							// 초기 NormalMonster* 크기
	int										saveIndex = 20;
	int										storeIndex = 0;							// MainBoard에 보여주며 저장하는 Index

public:
	virtual HRESULT							Init() override;
	virtual void							Release() override;
	virtual void							Update() override;
	virtual void							Render(HDC hdc) override;

	void									ClickedNormalMonster();
	void									DrawNormalMonster();
	void									DrawSampleRect(int index, float sizeX, float sizeY);
	void									EstablishSampleType();
	void									InitializeStoreSpace();
	void									Load(int loadIndex, int normalMonsterCount);
	void									Save(int saveIndex, int normalMonsterCount);
	void									StoreNormalMonster();

	virtual ~EnemyToolScene() = default;
};

