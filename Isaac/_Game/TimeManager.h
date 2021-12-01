#pragma once

class Timer;
class TimeManager : public Singleton<TimeManager>
{
private:
	Timer*	timer = nullptr;
	char	szText[256] = {};

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetDeltaTime();

	virtual ~TimeManager() = default;
};

