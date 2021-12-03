#pragma once

#include "GameObject.h"

class ButtonFunction;
typedef void (ButtonFunction::* FuncPtr)(ArgumentFuncPtr*);

enum class Button_State { NONE, UP, DOWN };

class Image;
class Button : public GameObject
{
private:
	struct ButtonInfo
	{
		Image*			image = nullptr;
		POINTFLOAT		pos = {};
		RECT			shape = {};
		Button_State	buttonState = Button_State::NONE;
	};

private:
	ButtonInfo			enemyBtn = {};			// Enemy
	ButtonInfo			exitBtn = {};			// Exit
	ButtonInfo			loadBtn = {};			// Load
	ButtonInfo			objectBtn = {};			// Object
	ButtonInfo			revertBtn = {};			// Revert
	ButtonInfo			saveBtn = {};			// Save
	ButtonInfo			sampleTileBtn = {};		// SampleTile

	Image*				letter_Enemy;				// Enemy
	Image*				letter_Exit;				// Exit
	Image*				letter_Object;				// Object
	Image*				letter_Tile;				// letter_Tile

	FuncPtr				pFunc = nullptr;
	ButtonFunction*		btnFunc = nullptr;
	ArgumentFuncPtr*	argFunc = nullptr;

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

	virtual ~Button() = default;
};

