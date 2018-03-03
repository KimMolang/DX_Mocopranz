#pragma once

//#include "Loading.h"
//#include "Title.h"
//#include "Lobby.h"
//#include "Room.h"
//#include "InMap.h"

BEGIN(Engine)


class Scene;
class Renderer;
class ENGINE_DLL SceneMgr
{
	DECLARE_SINGLETON(SceneMgr)

private:
	SceneMgr();
	~SceneMgr();

public:
	//enum ESceneID
	//{
	//	SCENE_ID_NONE,

	//	SCENE_ID_TITLE,
	//	//SCENE_ID_LOBBY,
	//	//SCENE_ID_ROOM,
	//	//SCENE_ID_INMAP
	//};

private:
	//ESceneID		m_eCurScene;
	Scene*			m_pScene;
	//bool			m_bSceneLoadingEnd;


	Renderer*		m_pRenderer;

public:
	//HRESULT		SetScene(const ESceneID& _eSceneID);
	HRESULT		SetScene(Scene* _pScene);
	HRESULT		SetSceneAftherLoading();

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