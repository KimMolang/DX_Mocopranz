#include "stdafx.h"
#include "Scene.h"

#include "Function.h"
#include "Camera.h"


CScene::CScene(CDevice* _pDevice)
: m_pDevice(_pDevice)
, m_pMainCamera(nullptr)
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
		m_pLayer[i] = nullptr;
}


CScene::~CScene()
{
	Release_Layer();
}

void CScene::Update_Layer()
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
	{
		if (nullptr != m_pLayer[i])
			m_pLayer[i]->Update_Obj();
	}
}

void CScene::Render_Layer()
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
	{
		if (nullptr != m_pLayer[i])
		{
			switch (i)
			{
			case CLayer::LAYERTYPE_ENVIRONMENT :
				m_pDevice->Blend_Begin();
				m_pLayer[i]->Render_Obj();
				m_pDevice->Blend_End();
				break;

			case CLayer::LAYERTYPE_GAMELOGIC :
				m_pLayer[i]->Render_Obj();
				break;

			case CLayer::LAYERTYPE_UI :
				if (m_pMainCamera != nullptr)
					m_pMainCamera->Invalidate_Ortho();

				m_pDevice->Blend_Begin();
				m_pLayer[i]->Render_Obj();
				m_pDevice->Blend_End();

				if (m_pMainCamera != nullptr)
				{
					m_pMainCamera->Invalidate_View();
					m_pMainCamera->Invalidate_Proj();
				}
				break;

			}
		}
	}
}

void CScene::Release_Layer()
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
		::Safe_Delete(m_pLayer[i]);
}
