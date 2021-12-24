#include "stdafx.h"
#include "GameObject.h"

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update()
{
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
