#include "stdafx.h"
#include "MainGame.h"

#include "GraphicDevice.h"
#include "Export_Function_Mgr_GraphicDevice.h"

extern HWND g_hWnd;


MainGame::MainGame()
{

}

MainGame::~MainGame()
{
	Release();
}

HRESULT MainGame::Init()
{
	//m_pGraphicDevice = std::make_shared<Engine::GraphicDevice>();
	m_pGraphicDevice = Engine::GetGraphicDevice();
	m_pGraphicDevice->Init( g_hWnd, CLIENT_WINDOW_SIZE_X, CLIENT_WINDOW_SIZE_Y );

	// (수정)
	// 매니저는 싱글톤으로 사용 x
	// 매니저를 담는 싱글톤 하나를 생성하고
	// 그 안에 하나씩 할당 받도록
	return S_OK;
}

void MainGame::Update()
{
	
}

void MainGame::Render()
{
	
}

void MainGame::Release()
{
	::Safe_Release(m_pGraphicDevice);
}