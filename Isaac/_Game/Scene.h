#pragma once

class Scene
{
private:

protected:

public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual ~Scene() = default;
};

