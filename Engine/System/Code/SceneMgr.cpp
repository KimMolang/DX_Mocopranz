#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"

#include "ResourceMgr.h"

//#include "SceneNull.h"
#include "SceneLoading.h"

BEGIN(Engine)
IMPLEMENT_SINGLETON(SceneMgr)


SceneMgr::SceneMgr()
	: m_pCurScene(nullptr)

	, m_pCurSceneLoading(nullptr)
	, m_pNextSceneAfterLoading(nullptr)

	, m_pRenderer(nullptr)
{
	//m_pCurScene = new SceneNull();
}


SceneMgr::~SceneMgr()
{
	Release();
}

HRESULT SceneMgr::SetScene(Scene* _pCurScene)
{
	if (_pCurScene == nullptr)
		return S_FALSE;


	ReleaseCurScene();


	//m_pCurScene = (_pCurScene == nullptr) ? new SceneNull() : _pCurScene;
	m_pCurScene = _pCurScene;
	m_pCurScene->Init();


	return S_OK;
}

HRESULT SceneMgr::SetScene(SceneLoading* _pCurSceneLoading, Scene* _pNextSceneAfterLoading)
{
	if (_pCurSceneLoading == nullptr || _pNextSceneAfterLoading == nullptr)
		return S_FALSE;


	ReleaseCurScene();


	m_pCurSceneLoading			= _pCurSceneLoading;
	m_pNextSceneAfterLoading	= _pNextSceneAfterLoading;

	m_pCurSceneLoading->Init();
	m_pCurSceneLoading->StartLoading();	// StartLoading


	return S_OK;
}

void SceneMgr::UpdateSceneAfterLoadingEnd()
{
	SetScene(m_pNextSceneAfterLoading);
	::Safe_Delete(m_pCurSceneLoading);
}

void SceneMgr::ReleaseCurScene()
{
	::Safe_Delete(m_pCurScene);

	// (Need the Modify)
	ResourceMgr::GetInstance()->Release_Dynamic();
}

//// 로딩이 끝나면 아래 함수가 불리고 m_pCurScene 에 씬을 할당한다.
//HRESULT SceneMgr::SetSceneAftherLoading()
//{
//	if (m_pCurScene)
//		::Safe_Delete(m_pCurScene);
//
//	switch (m_eCurScene)
//	{
//	case SCENE_ID_TITLE:	m_pCurScene = new SceneNull();		break;
//	//case SCENE_ID_LOBBY:	m_pCurScene = CLobby::Create(m_pDevice);	break;
//	//case SCENE_ID_ROOM:		m_pCurScene = CRoom::Create(m_pDevice);	break;
//	//case SCENE_ID_INMAP:	m_pCurScene = CInMap::Create(m_pDevice);	break;
//	default:				m_pCurScene = new SceneNull();		break;
//	}
//
//	CHECK_NULLPTR_RETURN(m_pCurScene, E_FAIL);
//	//m_pRenderer->SetScene(m_pCurScene);
//
//	return S_OK;
//}

HRESULT SceneMgr::Init()
{
	m_pRenderer = new Renderer();
	m_pRenderer->Init();

	return S_OK;
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
}

void SceneMgr::Render()
{
	if (m_pRenderer != nullptr)
		m_pRenderer->Render(m_pCurScene);
}

void SceneMgr::Release()
{
	::Safe_Delete(m_pCurScene);
	::Safe_Delete(m_pRenderer);
}


END