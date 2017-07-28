#include "stdafx.h"
#include "InMap.h"

//#include "InMapMgr.h"
//
#include "Layer.h"
//#include "LoadMgr.h"
#include "ResourceMgr.h"
//#include "ColMgr.h"
#include "ObjMgr.h"
//
//#include "Player.h"
//#include "Enemy.h"	// (수정) for Test
//
#include "CameraDynamic.h"
//#include "StaticCamera.h"
#include "SkyBox.h"
//#include "ProgressMgr.h"


CInMap::CInMap(CDevice* _pDevice)
: CScene(_pDevice)
//, m_pInMapMgr(CInMapMgr::GetInstance())
//, m_pProgresMgr(CProgressMgr::GetInstance())
{

}


CInMap::~CInMap()
{
	Release();
}

CInMap* CInMap::Create(CDevice* _pDevice)
{
	CInMap* pScene = new CInMap(_pDevice);

	if (FAILED(pScene->Init()))
		::Safe_Delete(pScene);

	return pScene;
}

HRESULT CInMap::Init()
{
	////m_pInMapMgr->Init();
	////CLoadMgr::GetInstance()->LoadResource(m_pDevice, CSceneMgr::SCENE_ID_INMAP);

	FAILED_CHECK(AddLayer_Environment());
	FAILED_CHECK(AddLayer_GameLogic());
	FAILED_CHECK(AddLayer_UI());
	//CLoadMgr::GetInstance()->LoadMap(
	//	m_pDevice,
	//	MAP_TYPE_THEGOREST,
	//	&(m_pLayer[CLayer::LAYERTYPE_ENVIRONMENT]),
	//	&m_pLayer[CLayer::LAYERTYPE_GAMELOGIC]);
	//CLoadMgr::GetInstance()->LoadUI(
	//	m_pDevice,
	//	CSceneMgr::SCENE_ID_INMAP,
	//	&(m_pLayer[CLayer::LAYERTYPE_UI]));


	//CColMgr* pColMgr = CColMgr::GetInstance();
	//pColMgr->SetMapObjList(CLayer::LAYERTYPE_GAMELOGIC,
	//	m_pLayer[CLayer::LAYERTYPE_GAMELOGIC]->GetMapObjList());

	CObjMgr::GetInstance()->SetLayer(
		m_pLayer[CLayer::LAYERTYPE_ENVIRONMENT],
		m_pLayer[CLayer::LAYERTYPE_GAMELOGIC],
		m_pLayer[CLayer::LAYERTYPE_UI]);


	//m_pInMapMgr->SetPlayerToReady();
	//m_pInMapMgr->CheckEnemyInitAndCreate();

	//m_pProgresMgr->Init();


	return S_OK;
}

void CInMap::Update()
{
	//m_pInMapMgr->Update();
	//m_pProgresMgr->Update();
	CScene::Update_Layer();
}

void CInMap::Render()
{
	CScene::Render_Layer();
}

HRESULT CInMap::AddLayer_Environment()
{
	CLayer*		pLayer = CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);
	

	CObj* pObj = NULL;

	// SkyBox
	pObj = CSkyBox::Create(m_pDevice, L"Texture_SkyBox_00");
	NULL_CHECK_RETURN(pObj, E_FAIL);
	((CBackGround*)pObj)->SetWorldMatrix(
		D3DXVECTOR3(0.f, 250.f, 0.f),
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(1200.f, 500.f, 1200.f)); // (수정) 이거 로컬에서 값 바꾸셈 스케일링 하지 말고
	pLayer->AddObj(L"SkyBox", pObj);


	m_pLayer[CLayer::LAYERTYPE_ENVIRONMENT] = pLayer;

	return S_OK;
}

HRESULT CInMap::AddLayer_GameLogic()
{
	CLayer*		pLayer = CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);


	CObj* pObj = NULL;
	
	//// Player
	//pObj = CPlayer::Create(m_pDevice);
	//NULL_CHECK_RETURN(pObj, E_FAIL);
	//pLayer->AddObj(L"Player", pObj);

	//m_pInMapMgr->SetPlayer((CRider*)pObj);
	//m_pProgresMgr->SetPlayer((CPlayer*)pObj);

	/////*
	////float CPlayer::x = 4.9f;
	////float CPlayer::y = 60.5f;
	////float CPlayer::z = 275.0f;
	////*/

	////pObj = CEnemy::Create(m_pDevice);
	////NULL_CHECK_RETURN(pObj, E_FAIL);
	////pObj->SetPos(D3DXVECTOR3(4.9f, 60.5f, 320.f));
	////pLayer->AddObj(L"Enemy", pObj);
	

	m_pLayer[CLayer::LAYERTYPE_GAMELOGIC] = pLayer;

	return S_OK;
}

HRESULT CInMap::AddLayer_UI()
{
	CLayer*		pLayer = CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	CObj* pObj = NULL;


 	// Camera
 	pObj = CCameraDynamic::Create(m_pDevice);
 	NULL_CHECK_RETURN(pObj, E_FAIL);
 	pLayer->AddObj(L"DynamicCamera", pObj);
 	m_pMainCamera = dynamic_cast<CCamera*>(pObj);
//
//	CUnit* pPlayer = (CUnit*)
//		(m_pLayer[CLayer::LAYERTYPE_GAMELOGIC]->GetObj(L"Player"));
//
//	// Camera
//	pObj = CStaticCamera::Create(m_pDevice);
//	NULL_CHECK_RETURN(pObj, E_FAIL);
//	((CStaticCamera*)pObj)->SetTargetPhysics(pPlayer->GetPhysics());
//	pLayer->AddObj(L"StaticCamera", pObj);
//	m_pMainCamera = dynamic_cast<CCamera*>(pObj);


	m_pLayer[CLayer::LAYERTYPE_UI] = pLayer;


	return S_OK;
}

void CInMap::Release()
{

}