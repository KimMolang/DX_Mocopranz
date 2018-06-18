#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"

#include "ResourceMgr.h"

#include "SceneNull.h"

BEGIN(Engine)
IMPLEMENT_SINGLETON(SceneMgr)


SceneMgr::SceneMgr()
	//, m_bSceneLoadingEnd(false)

	: m_pRenderer(nullptr)
{
	m_pScene = new SceneNull();
}


SceneMgr::~SceneMgr()
{
	Release();
}

HRESULT SceneMgr::SetScene(Scene* _pScene)
{
	if (m_pScene)
		::Safe_Delete(m_pScene);

	m_pScene = (_pScene == nullptr) ? new SceneNull() : _pScene;
	m_pScene->Init();


	return S_OK;
}
//// 해당 함수를 부르면 m_eCurScene 값을 셋팅하고
//// 로딩을 시작한다.
//HRESULT SceneMgr::SetScene(const ESceneID& _eSceneID)
//{
//	if (m_pScene)
//		::Safe_Delete(m_pScene);
//
//
//	ResourceMgr::GetInstance()->Release_Dynamic();
//	m_bSceneLoadingEnd = false;
//
//	m_eCurScene = _eSceneID;
//	//m_pRenderer->SetScene(m_pScene);
//
//	//m_pScene = CLoading::Create(m_pDevice);
//	CHECK_NULLPTR_RETURN(m_pScene, E_FAIL);
//
//
//	return S_OK;
//}
//

// (고민)
// 결국 이건 templet<class T> 로 하면 해결될 것인데
// enum 값 처리를 어떻게 하냐임
// 유니티에서는 0, 1, 2 값과 string 값으로 씬을 구별하던데
// 흠

//// 로딩이 끝나면 아래 함수가 불리고 m_pScene 에 씬을 할당한다.
//HRESULT SceneMgr::SetSceneAftherLoading()
//{
//	if (m_pScene)
//		::Safe_Delete(m_pScene);
//
//	switch (m_eCurScene)
//	{
//	case SCENE_ID_TITLE:	m_pScene = new SceneNull();		break;
//	//case SCENE_ID_LOBBY:	m_pScene = CLobby::Create(m_pDevice);	break;
//	//case SCENE_ID_ROOM:		m_pScene = CRoom::Create(m_pDevice);	break;
//	//case SCENE_ID_INMAP:	m_pScene = CInMap::Create(m_pDevice);	break;
//	default:				m_pScene = new SceneNull();		break;
//	}
//
//	CHECK_NULLPTR_RETURN(m_pScene, E_FAIL);
//	//m_pRenderer->SetScene(m_pScene);
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
	m_pScene->Update();
}

void SceneMgr::Render()
{
	if (m_pRenderer != nullptr)
		m_pRenderer->Render(m_pScene);
}

void SceneMgr::Release()
{
	::Safe_Delete(m_pScene);
	::Safe_Delete(m_pRenderer);
}


END