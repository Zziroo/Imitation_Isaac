#pragma once

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, Scene*>	mapScenes;
	map<string, Scene*>	mapLoadingScenes;

public:
	static Scene*	currScene;			// ���� ��� ���� ��
	static Scene*	readyScene;			// �غ� ���� ��
	static Scene*	loadingScene;		// �ε� ��

	void			Init();
	void			Release();
	void			Update();
	void			Render(HDC hdc);

	void			AddScene(string key, Scene* scene);
	void			AddLoadingScene(string key, Scene* scene);

	HRESULT			ChangeScene(string sceneName);
	HRESULT			ChangeScene(string sceneName, string loadingSceneName);

	virtual	~SceneManager() = default;
};

