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
	// (����) ������ġó�� �߿��� �͸� ���� �ε��ϰ� �����ְ�
	// �� �߿��� �� ������ �ε��ϸ鼭 �ε��� �Ϸ�Ǹ� �����ϰ� ����� ����!


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