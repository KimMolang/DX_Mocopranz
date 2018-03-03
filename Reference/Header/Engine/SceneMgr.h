#pragma once

BEGIN(Engine)


class Scene;
class Renderer;
class ENGINE_DLL SceneMgr
{
	DECLARE_SINGLETON(SceneMgr)

private:
	SceneMgr();
	~SceneMgr();

private:
	Scene*			m_pScene;
	//bool			m_bSceneLoadingEnd;
	// (수정) 오버워치처럼 중요한 것만 먼저 로딩하고 보여주고
	// 덜 중요한 건 꾸준히 로딩하면서 로딩이 완료되면 렌더하게 만들고 싶음!


	Renderer*		m_pRenderer;

public:
	//HRESULT		SetScene(const ESceneID& _eSceneID);
	HRESULT		SetScene(Scene* _pScene);
	//HRESULT		SetSceneAftherLoading();

	//ESceneID	GetCurScene() { return m_eCurScene; }
	//bool		GetSceneLoadingEnd() { return m_bSceneLoadingEnd; }
	//void		SetSceneLoadingEnd(bool _bEnd) { m_bSceneLoadingEnd = _bEnd; }

public:
	HRESULT		Init();
	void		Update();
	void		Render();
	void		Release();
};



END