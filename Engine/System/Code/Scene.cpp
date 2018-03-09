#include "stdafx.h"
#include "Scene.h"

#include "Layer.h"
#include "Camera.h"

#include "GraphicDevice.h"
#include "ObjectMgr.h"

BEGIN(Engine)


Scene::Scene()
	: m_pMainCamera(nullptr)
{
	for (int i = 0; i < ELayerType::LAYER_TYPE_MAX; ++i)
		m_pLayer[i] = nullptr;
}


Scene::~Scene()
{
	Release_Layer();
}

HRESULT Scene::Init()
{
	m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_BACK]		= new Layer();
	m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC]	= new Layer();
	m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_UI]			= new Layer();

	ObjectMgr::GetInstance()->SetLayer(
		m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_BACK],
		m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC],
		m_pLayer[Engine::Scene::ELayerType::LAYER_TYPE_UI]);

	return S_OK;
}

void Scene::Update()
{
	Update_Layer();
}

void Scene::Render()
{
	Render_Layer();
}

void Scene::Release()
{

}

void Scene::Update_Layer()
{
	for (int i = 0; i < ELayerType::LAYER_TYPE_MAX; ++i)
	{
		if (nullptr != m_pLayer[i])
			m_pLayer[i]->Update_Obj();
	}
}

void Scene::Render_Layer()
{
	for (int i = 0; i < ELayerType::LAYER_TYPE_MAX; ++i)
	{
		if (nullptr != m_pLayer[i])
		{
			switch (i)
			{
			case ELayerType::LAYER_TYPE_BACK:
				GraphicDevice::GetInstance()->Blend_Begin();
				m_pLayer[i]->Render_Obj();
				GraphicDevice::GetInstance()->Blend_End();
				break;

			case ELayerType::LAYER_TYPE_GAMELOGIC:
				m_pLayer[i]->Render_Obj();
				break;

			case ELayerType::LAYER_TYPE_UI:
				if (m_pMainCamera != nullptr) // (수정) No Check nullptr. replace it with null object
				{
					m_pMainCamera->Invalidate_Ortho();
				}

				GraphicDevice::GetInstance()->Blend_Begin();
				m_pLayer[i]->Render_Obj();
				GraphicDevice::GetInstance()->Blend_End();

				if (m_pMainCamera != nullptr) // (수정) No Check nullptr. replace it with null object
				{
					m_pMainCamera->Invalidate_View();
					m_pMainCamera->Invalidate_Proj();
				}
				break;
			}
		}
	}
}

void Scene::Release_Layer()
{
	for (int i = 0; i < ELayerType::LAYER_TYPE_MAX; ++i)
		::Safe_Delete(m_pLayer[i]);
}


END