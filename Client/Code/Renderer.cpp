#include "stdafx.h"
#include "Renderer.h"

#include "Timer.h"

#include "Device.h"
//#include "TextureShader.h"

//#include "ResourceMgr.h"

extern HWND		g_hWnd;

float CRenderer::m_fTimer		= 0.f;
DWORD CRenderer::m_dwFPSCnt		= 0;


CRenderer::CRenderer(CDevice* _pDevice)
: m_pDevice(_pDevice)
, m_pScene(nullptr)
{

}

CRenderer::~CRenderer(void)
{

}

CRenderer* CRenderer::Create(CDevice* _pDeviceClass)
{
	CRenderer* pRenderer = new CRenderer(_pDeviceClass);

	if (FAILED(pRenderer->Init()))
		::Safe_Delete(pRenderer);


	return pRenderer;
}

HRESULT CRenderer::Init()
{

	return S_OK;
}

void CRenderer::Render()
{
	m_fTimer += CTimer::GetInstance()->GetTime();
	++m_dwFPSCnt;


// 	if (m_fTimer >= 1.f)
// 	{
// 		m_fTimer = 0.f;
// 		m_dwFPSCnt = 0;
// 	}


	m_pDevice->Render_Begin();

	if (m_pScene != nullptr)
		m_pScene->Render();
	
	m_pDevice->Render_End();
}


