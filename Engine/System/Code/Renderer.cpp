#include "stdafx.h"
#include "Renderer.h"

#include "Timer.h"
#include "GraphicDevice.h"

#include "ResourceMgr.h"

BEGIN(Engine)


float Renderer::m_fTimer = 0.f;
DWORD Renderer::m_dwFPSCnt = 0;


Renderer::Renderer()
	: m_pGraphicDevice( GraphicDevice::GetInstance() )
{

}

Renderer::~Renderer(void)
{

}

HRESULT Renderer::Init()
{
	return S_OK;
}

void Renderer::Render(Scene* _pScene)
{
	m_fTimer += Timer::GetInstance()->GetTime();
	++m_dwFPSCnt;


	// 	if (m_fTimer >= 1.f)
	// 	{
	// 		m_fTimer = 0.f;
	// 		m_dwFPSCnt = 0;
	// 	}


	m_pGraphicDevice->Render_Begin();
	_pScene->Render();
	m_pGraphicDevice->Render_End();
}


END