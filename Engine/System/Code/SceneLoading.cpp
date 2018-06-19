#include "stdafx.h"
#include "SceneLoading.h"

#include <process.h>
#include "SceneMgr.h"

BEGIN(Engine)


SceneLoading::SceneLoading()
	: m_eLoadingState(ELoadingState::LOADING_STATE_READY)
{

}


SceneLoading::~SceneLoading()
{

}

unsigned int SceneLoading::StartLoading(void * _pArg)
{
	SceneLoading* pSceneLoading = static_cast<SceneLoading*>(_pArg);
	EnterCriticalSection(&pSceneLoading->GetCriticalSection());

	// Now Loading
	pSceneLoading->m_eLoadingState = SceneLoading::ELoadingState::LOADING_STATE_LOADING;
	pSceneLoading->LoadContens();

	// End the Loading
	pSceneLoading->m_eLoadingState = SceneLoading::ELoadingState::LOADING_STATE_END;

	LeaveCriticalSection(&pSceneLoading->GetCriticalSection());
	_endthreadex(0);


	return 0;
}

HRESULT SceneLoading::Init()
{
	

	return S_OK;
}

HRESULT SceneLoading::StartLoading()
{
	DoBeforeLoading();


	InitializeCriticalSection(&m_csCriticalSection);
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, StartLoading, this, 0, nullptr);

	if (m_hThread == nullptr)
		return E_FAIL;

	return S_OK;
}

void SceneLoading::Update()
{
	if (m_eLoadingState == ELoadingState::LOADING_STATE_END)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_csCriticalSection);

		DoAfterLoading();

		m_eLoadingState = ELoadingState::LOADING_STATE_CHANGE_SCENE;
		SceneMgr::GetInstance()->UpdateSceneAfterLoadingEnd();
	}
}

void SceneLoading::Render()
{
	
}

void SceneLoading::Release()
{

}


END