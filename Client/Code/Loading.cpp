#include "stdafx.h"
#include "Loading.h"

#include <process.h>

#include "LoadMgr.h"
#include "SceneMgr.h"


CLoading::CLoading(CDevice* _pDevice)
: CScene(_pDevice)
{
}


CLoading::~CLoading()
{
	Release();
}

CLoading* CLoading::Create(CDevice* _pDevice)
{
	CLoading* pScene = new CLoading(_pDevice);

	if (FAILED(pScene->Init()))
		::Safe_Delete(pScene);

	return pScene;
}

// static size_t	__stdcall ResourceLoad(void* _pArg)
// {
// 	CLoading* pLoading = (CLoading*)_pArg;
// 	EnterCriticalSection(&pLoading->GetCriticalSection());
// 
//  	CLoadMgr::GetInstance()->LoadResource(
//  		CDevice::GetInstance(), CSceneMgr::GetInstance()->GetScene());
// 	
// 
// 	CSceneMgr::GetInstance()->SetSceneLoadingEnd(true);
// 	LeaveCriticalSection(&pLoading->GetCriticalSection());
// 	_endthreadex(0);
// 	
// 
// 	return 0;
// }

HRESULT CLoading::Init()
{
	// 로딩 이미지 뿌려주세요.

// 	InitializeCriticalSection(&m_tCriticalSection);
// 	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ResourceLoad, this, 0, NULL);


	CLoadMgr::GetInstance()->LoadResource(
		CDevice::GetInstance(), CSceneMgr::GetInstance()->GetScene());
	CSceneMgr::GetInstance()->SetSceneLoadingEnd(true);

	return S_OK;
}

void CLoading::Update()
{
	if (CSceneMgr::GetInstance()->GetSceneLoadingEnd())
	{
// 		WaitForSingleObject(m_hThread, INFINITE);
// 		CloseHandle(m_hThread);
// 
// 		DeleteCriticalSection(&m_tCriticalSection);

		CSceneMgr::GetInstance()->SetSceneAftherLoading();
	}
}

void CLoading::Render()
{

}

void CLoading::Release()
{

}

