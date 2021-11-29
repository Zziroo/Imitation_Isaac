#pragma once

template <typename T>
class Singleton
{
private:

protected:
	static T* instance;

	Singleton() {};
	virtual ~Singleton() = default;

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetSingleton()
{
	if (!instance) { instance = new T; }

	return instance;
}

template<typename T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance) 
	{
		delete instance;
		instance = nullptr;
	}
}
