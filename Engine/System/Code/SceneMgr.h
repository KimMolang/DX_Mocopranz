#pragma once

BEGIN(Engine)


class Scene;
class SceneLoading;
class Renderer;
class ENGINE_DLL SceneMgr
{
	DECLARE_SINGLETON(SceneMgr)

private:
	SceneMgr();
	~SceneMgr();


public:
	// (Skip)
	//HRESULT SetScene(const int _iSceneIndex);
	//HRESULT SetScene(const std::wstring& _strSceneName);

	HRESULT		SetScene(Scene* _pCurScene);
	HRESULT		SetScene(SceneLoading* _pCurSceneLoading, Scene* _pNextSceneAfterLoading);

	void		UpdateSceneAfterLoadingEnd();


public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();


public :
	//HRESULT	AddSceneInfo();
	//HRESULT RemoveSceneInfo();
	// (Skip)
	// 유니티 라면 무조건 new Scene 를 하고 (씬 클래스 따로 없이)
	// 따로 연결되어 있는 오브젝트, 리소스 리스트를 할당해 줄 듯
	// 하지만 이걸 비슷하게 하려면 사전작업이 많이 필요하니 우선 패스.

private :
	void ReleaseCurScene();


private:
	Scene*				m_pCurScene;

	SceneLoading*		m_pCurSceneLoading;
	Scene*				m_pNextSceneAfterLoading;

	// (Skip)
	//std::vector<???>	m_vSceneArray;

	Renderer*		m_pRenderer;
};


END