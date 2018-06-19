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
	// ����Ƽ ��� ������ new Scene �� �ϰ� (�� Ŭ���� ���� ����)
	// ���� ����Ǿ� �ִ� ������Ʈ, ���ҽ� ����Ʈ�� �Ҵ��� �� ��
	// ������ �̰� ����ϰ� �Ϸ��� �����۾��� ���� �ʿ��ϴ� �켱 �н�.

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