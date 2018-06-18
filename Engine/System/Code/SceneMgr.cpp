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
//// �ش� �Լ��� �θ��� m_eCurScene ���� �����ϰ�
//// �ε��� �����Ѵ�.
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

// (���)
// �ᱹ �̰� templet<class T> �� �ϸ� �ذ�� ���ε�
// enum �� ó���� ��� �ϳ���
// ����Ƽ������ 0, 1, 2 ���� string ������ ���� �����ϴ���
// ��

//// �ε��� ������ �Ʒ� �Լ��� �Ҹ��� m_pScene �� ���� �Ҵ��Ѵ�.
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