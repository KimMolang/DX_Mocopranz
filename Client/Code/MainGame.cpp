#include "stdafx.h"
#include "MainGame.h"

#include <time.h>

#include "Device.h"
#include "SceneMgr.h"

#include "Timer.h"
#include "KeyMgr.h"

extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;

CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Init()
{
	srand(unsigned int(time(nullptr)));

#ifdef _DEBUG
	FAILED_CHECK(CDevice::GetInstance()->Init(CDevice::WIN_MODE_WIN));
#else
	FAILED_CHECK(CDevice::GetInstance()->Init(CDevice::WIN_MODE_WIN));
#endif
	m_pDevice = CDevice::GetInstance();
	NULL_CHECK_RETURN(m_pDevice, E_FAIL);

	// Mgr ---------------------
	m_pSceneMgr = CSceneMgr::GetInstance();
	m_pTimer = CTimer::GetInstance();
	m_pKeyMgr = CKeyMgr::GetInstance();
	//m_pServerMgr = CServer::GetInstance();


	// Mgr Init ----------------
	m_pSceneMgr->Init(m_pDevice);
	m_pSceneMgr->SetScene(CSceneMgr::SCENE_ID_INMAP);
	m_pTimer->Init();
	m_pKeyMgr->Init(g_hInst, g_hWnd);
	////m_pServerMgr->InitServer(g_hWnd);


	return S_OK;
}

void CMainGame::Update()
{
	m_pTimer->Update();
	m_pKeyMgr->UpdateInputState();
	m_pSceneMgr->Update();
}

void CMainGame::Render()
{
	m_pSceneMgr->Render();
}

void CMainGame::Release()
{
	m_pTimer->DestroyInstance();
	m_pKeyMgr->DestroyInstance();
	m_pSceneMgr->DestroyInstance();

	//CObjMgr::GetInstance()->DestroyInstance();
	//CColMgr::GetInstance()->DestroyInstance();
	//CInMapMgr::GetInstance()->DestroyInstance();

	m_pDevice->DestroyInstance();


	//CInfoSubject::GetInstance()->DestroyInstance();
	////m_pServerMgr->DestroyInstance();

	//CResourceMgr::GetInstance()->DestroyInstance();
	//CLoadMgr::GetInstance()->DestroyInstance();
}
