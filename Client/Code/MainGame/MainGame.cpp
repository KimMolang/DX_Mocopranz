#include "stdafx.h"
#include "MainGame.h"

#include "GraphicDevice.h"
#include "Export_Function_Mgr_GraphicDevice.h"

#include "Timer.h"
#include "KeyChecker.h"
#include "SceneMgr.h"
#include "Export_Function_Mgr.h"

#include "../Mgr/SceneSetter.h"

extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;


MainGame::MainGame()
{

}

MainGame::~MainGame()
{
	Release();
}

HRESULT MainGame::Init()
{
	// Init a GraphicDevice
	//m_pGraphicDevice = std::make_shared<Engine::GraphicDevice>();
	m_pGraphicDevice = Engine::GetGraphicDevice();
	m_pGraphicDevice->Init( g_hWnd, CLIENT_WINDOW_SIZE_X, CLIENT_WINDOW_SIZE_Y );

	// Init a Timer, KeyChecker, SceneMgr
	m_pTimer		= Engine::GetTimer();
	m_pKeyChecker	= Engine::GetKeyChecker();
	m_pSceneMgr		= Engine::GetSceneMgr();
	m_pTimer->Init();
	m_pKeyChecker->Init(g_hInst, g_hWnd);
	m_pSceneMgr->Init();

	// Set First Scene
	SceneSetter::GetInstance()->SetScene(SceneSetter::ESceneID::SCENE_ID_TOWN);


	return S_OK;
}

void MainGame::Update()
{
	m_pTimer->Update();
	m_pKeyChecker->UpdateInputState();
	m_pSceneMgr->Update();
}

void MainGame::Render()
{
	m_pSceneMgr->Render();
}

void MainGame::Release()
{
	m_pSceneMgr->DestroyInstance();
	m_pKeyChecker->DestroyInstance();
	m_pTimer->DestroyInstance();

	m_pGraphicDevice->DestroyInstance();
}