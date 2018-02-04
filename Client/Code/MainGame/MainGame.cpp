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

	// (����)
	// �Ŵ����� �̱������� ��� x
	// �Ŵ����� ��� �̱��� �ϳ��� �����ϰ�
	// �� �ȿ� �ϳ��� �Ҵ� �޵���
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