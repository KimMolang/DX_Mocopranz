#include "stdafx.h"
#include "MainGame.h"

#include "Device.h"

CMainGame::CMainGame()
{

}

CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Init()
{
	m_pDevice = std::make_unique<CDevice>();
	m_pDevice->Init();

	return S_OK;
}

void CMainGame::Update()
{
	
}

void CMainGame::Render()
{
	
}

void CMainGame::Release()
{
	::Safe_Release(m_pDevice);
}