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
		Image*		button = nullptr;
		POINTFLOAT	pos = {};
		RECT		shape = {};
	};

private:
	ButtonInfo			exitBtn = {};		// Exit
	ButtonInfo			saveBtn = {};		// Save
	ButtonInfo			loadBtn = {};		// Load
	Button_State		buttonState = Button_State::NONE;

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
	void SetFunction(FuncPtr pFunc, ButtonFunction* btnFunc, ArgumentFuncPtr* argFunc = nullptr) { this->pFunc = pFunc; this->btnFunc = btnFunc; this->argFunc = argFunc; }

	virtual ~Button() = default;
};
