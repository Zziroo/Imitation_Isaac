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
	if (GET_SINGLETON_KEY->IsOnceKeyDown(VK_RBUTTON))
	{
		debugMode = !debugMode;
	}	
}

void GameObject::Render(HDC hdc)
{
	if (debugMode)
	{
		OnDebug(hdc);
	}
}

void GameObject::OnDebug(HDC hdc)
{
}
