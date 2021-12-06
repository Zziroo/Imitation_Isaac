#include "MainConfig.h"
#include "GameObject.h"

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update()
{
	Input::Update();

	if (Input::GetButtonDown('P'))
	{
		debugMode = !debugMode;
	}	
}

void GameObject::Render(HDC hdc)
{
	OnDebug(hdc);
}

void GameObject::OnDebug(HDC hdc)
{
}
