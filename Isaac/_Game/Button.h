#pragma once

#include "GameObject.h"

class ButtonFunction;
typedef void (ButtonFunction::* FuncPtr)(ArgumentFuncPtr*);

enum class ButtonState { NONE, UP, DOWN };

class Image;
class Button : public GameObject
{
private:
	struct ButtonInfo
	{
		Image*			image = nullptr;
		POINTFLOAT		pos = {};
		RECT			shape = {};
		ButtonState		buttonState = ButtonState::NONE;
	};

private:
	ButtonInfo			enemyBtn = {};					// Enemy
	ButtonInfo			exitBtn = {};					// Exit
	ButtonInfo			loadBtn = {};					// Load
	ButtonInfo			objectBtn = {};					// Object
	ButtonInfo			revertBtn = {};					// Revert
	ButtonInfo			saveBtn = {};					// Save
	ButtonInfo			sampleTileBtn = {};				// SampleTile

	ButtonInfo			basementTileBtn = {};			// Tile/BASEMENT
	ButtonInfo			caveTileBtn = {};				// Tile/CAVE
	ButtonInfo			cellarTileBtn = {};				// Tile/CELLAR
	ButtonInfo			depthTileBtn = {};				// Tile/DEPTH
	ButtonInfo			shopTileBtn = {};				// Tile/SHOP

	ButtonInfo			closeBtn = {};					// Close
	ButtonInfo			nextBtn = {};					// Next
	ButtonInfo			prevBtn = {};					// Prev

	Image*				letter_Basement = nullptr;		// Basement
	Image*				letter_Cave = nullptr;			// Cave
	Image*				letter_Cellar = nullptr;		// Cellar
	Image*				letter_Depth = nullptr;			// Depth
	Image*				letter_Enemy = nullptr;			// Enemy
	Image*				letter_Exit = nullptr;			// Exit
	Image*				letter_Object = nullptr;		// Object
	Image*				letter_Shop = nullptr;			// Shop
	Image*				letter_Tile = nullptr;			// letter_Tile

	FuncPtr				pFunc = nullptr;
	ButtonFunction*		btnFunc = nullptr;
	ArgumentFuncPtr*	argFunc = nullptr;

	bool				selectSampleTile = false;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDebug(HDC hdc) override;

	void DeclareButtonInfo(ButtonInfo* btnInfo, int width, int height);
	void ClikedButton(ButtonInfo btnInfo, HDC hdc);
	void RenderUpButtonImage(ButtonInfo btnInfo, HDC hdc);
	void RenderDownButtonImage(ButtonInfo btnInfo, HDC hdc);

	void SetFunction(FuncPtr pFunc, ButtonFunction* btnFunc, ArgumentFuncPtr* argFunc = nullptr) { this->pFunc = pFunc; this->btnFunc = btnFunc; this->argFunc = argFunc; }

	inline bool GetSelectSampleTile() { return this->selectSampleTile; }

	virtual ~Button() = default;
};

