#include "stdafx.h"
#include "SceneLoading.h"

#include <process.h>

BEGIN(Engine)


SceneLoading::SceneLoading()
{

}


SceneLoading::~SceneLoading()
{

}

//static unsigned int	__stdcall ResourceLoad(void* _pArg)
//{
//	SceneLoading* pSceneLoading = static_cast<SceneLoading*>(_pArg);
//	EnterCriticalSection(&pSceneLoading->GetCriticalSection());
//
//	//	CLoadMgr::GetInstance()->LoadResource(
//	//		CDevice::GetInstance(), CSceneMgr::GetInstance()->GetScene());
//	//
//
//	//CSceneMgr::GetInstance()->SetSceneLoadingEnd(true);
//
//	// 유니티에서는 씬 자체를 읽을 때
//	// 오브젝트 리스트와
//	// 그 오브젝트가 가지고 있는 컴포넌트를 읽어오는 듯
//
//	LeaveCriticalSection(&pSceneLoading->GetCriticalSection());
//	_endthreadex(0);
//
//
//	return 0;
//}

HRESULT SceneLoading::Init()
{
	//InitializeCriticalSection(&m_csCriticalSection);
	//m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ResourceLoad, this, 0, nullptr);

	//if (m_hThread == NULL)
	//	return E_FAIL;

	return S_OK;
}

void SceneLoading::Update()
{
	//if (CSceneMgr::GetInstance()->GetSceneLoadingEnd())
	//{
	//	WaitForSingleObject(m_hThread, INFINITE);
	//	CloseHandle(m_hThread);
	//	
	//	DeleteCriticalSection(&m_csCriticalSection);

	//	CSceneMgr::GetInstance()->SetSceneAftherLoading();
	//}
}

void SceneLoading::Render()
{
	
}

void SceneLoading::Release()
{

}


END