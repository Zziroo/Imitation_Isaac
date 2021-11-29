#include "MainConfig.h"
#include "TimeManager.h"
#include "Timer.h"

void TimeManager::Init()
{
	timer = new Timer;
	timer->Init();
}

void TimeManager::Release()
{
	SAFE_DELETE(timer);
}

void TimeManager::Update()
{
	timer->Tick();
}

void TimeManager::Render(HDC hdc)
{
	wsprintf(szText, "FPS : %d", timer->GetFPS());
	TextOut(hdc, WIN_SIZE_X - 100, 0, szText, (INT)strlen(szText));
}


float TimeManager::GetDeltaTime()
{
	if (timer) { return timer->GetDeltaTime(); }
	return 0.0f;
}
