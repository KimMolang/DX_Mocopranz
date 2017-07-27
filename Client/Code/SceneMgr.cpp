#include "stdafx.h"
#include "SceneMgr.h"

#include "Device.h"
#include "Renderer.h"

#include "Loading.h"
//#include "Title.h"
//#include "Lobby.h"
//#include "Room.h"
#include "InMap.h"
//
//#include "ResourceMgr.h"

IMPLEMENT_SINGLETON(CSceneMgr)


CSceneMgr::CSceneMgr()
: m_pDevice(nullptr)

, m_eCurScene(SCENE_ID_NONE)
, m_pScene(nullptr)
, m_bSceneLoadingEnd(false)

, m_pRenderer(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SetScene(SceneID _eSceneID)
{
	if (m_pScene)
		::Safe_Delete(m_pScene);

//// 	switch (_eSceneID)
//// 	{
//// 	case SCENE_ID_TITLE:	m_pScene = CTitle::Create(m_pDevice);	break;
//// 	case SCENE_ID_LOBBY:	m_pScene = CLobby::Create(m_pDevice);	break;
//// 	case SCENE_ID_ROOM:		m_pScene = CRoom::Create(m_pDevice);	break;
//// 	case SCENE_ID_INMAP:	m_pScene = CInMap::Create(m_pDevice);	break;
//// 	default:				m_pScene = nullptr;						break;
//// 	}

	//CResourceMgr::GetInstance()->Release_Dynamic();
	m_bSceneLoadingEnd = false;

	m_eCurScene = _eSceneID;
	m_pRenderer->SetScene(m_pScene);

	m_pScene = CLoading::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pScene, E_FAIL);


	return S_OK;
}

HRESULT CSceneMgr::SetSceneAftherLoading()
{
	if (m_pScene)
		::Safe_Delete(m_pScene);

	switch (m_eCurScene)
	{
	//case SCENE_ID_TITLE:	m_pScene = CTitle::Create(m_pDevice);	break;
	//case SCENE_ID_LOBBY:	m_pScene = CLobby::Create(m_pDevice);	break;
	//case SCENE_ID_ROOM:		m_pScene = CRoom::Create(m_pDevice);	break;
	case SCENE_ID_INMAP:	m_pScene = CInMap::Create(m_pDevice);	break;
	default:				m_pScene = nullptr;						break;
	}

	NULL_CHECK_RETURN(m_pScene, E_FAIL);
	m_pRenderer->SetScene(m_pScene);

	return S_OK;
}

HRESULT CSceneMgr::Init(CDevice* _pDevice)
{
	m_pDevice = _pDevice;
	m_pRenderer = CRenderer::Create(m_pDevice);

	return S_OK;
}

void CSceneMgr::Update()
{
	if (m_pScene != nullptr)
		m_pScene->Update();
}

void CSceneMgr::Render()
{
	if (m_pRenderer != nullptr)
		m_pRenderer->Render();
}

void CSceneMgr::Release()
{
	::Safe_Delete(m_pScene);
	::Safe_Delete(m_pRenderer);
}
