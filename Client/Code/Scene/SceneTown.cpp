#include "stdafx.h"
#include "SceneTown.h"

// for Test (수정)
#include "ResourceMgr.h"
#include "ObjectMgr.h"
#include "Export_Function_Mgr.h"
#include "VIBufferCube.h"
#include "ShaderColor.h"

#include "Object.h"

#include "../Mgr/ObjectFactory.h"

SceneTown::SceneTown()
{
}

SceneTown::~SceneTown()
{
}

HRESULT SceneTown::Init()
{
	Engine::Scene::Init();


	// for Test (수정)
	Engine::ShaderColor* pShader = new Engine::ShaderColor();
	pShader->Init(); // (수정) (이놈의 Init을 생성자에 넣어버릴까??)
	Engine::GetResourceMgr()->AddResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC
		, Engine::ResourceMgr::RESOURCE_TYPE_SHADER
		, L"Test_Shader_Color"
		, pShader);

	Engine::VIBufferCube* pVIBufferCube = new Engine::VIBufferCube();
	pVIBufferCube->Init(); // (수정) (이놈의 Init을 생성자에 넣어버릴까??)
	Engine::GetResourceMgr()->AddResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC
		, Engine::ResourceMgr::RESOURCE_TYPE_MODEL
		, L"Test_Buffer_Cube"
		, pVIBufferCube);
	

	// TestObject
	Engine::Object* pCreatedObj
		= ObjectFactory::GetInstance()->CreateObject(ObjectFactory::EObjectID::OBJECT_ID_TEST);
	pCreatedObj->Init();
	pCreatedObj->SetWorldMatrix(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Engine::GetObjectMgr()->AddObj(
		Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC
		, pCreatedObj);

	pCreatedObj
		= ObjectFactory::GetInstance()->CreateObject(ObjectFactory::EObjectID::OBJECT_ID_TEST);
	pCreatedObj->Init();
	pCreatedObj->SetWorldMatrix(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
	Engine::GetObjectMgr()->AddObj(
		Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC
		, pCreatedObj);

	pCreatedObj
		= ObjectFactory::GetInstance()->CreateObject(ObjectFactory::EObjectID::OBJECT_ID_TEST);
	pCreatedObj->Init();
	pCreatedObj->SetWorldMatrix(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	Engine::GetObjectMgr()->AddObj(
		Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC
		, pCreatedObj);

	pCreatedObj
		= ObjectFactory::GetInstance()->CreateObject(ObjectFactory::EObjectID::OBJECT_ID_TEST);
	pCreatedObj->Init();
	pCreatedObj->SetWorldMatrix(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	Engine::GetObjectMgr()->AddObj(
		Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC
		, pCreatedObj);

	// Camera
	Engine::GetObjectMgr()->AddObj(
		Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC
		, ObjectFactory::GetInstance()->CreateObject(ObjectFactory::EObjectID::OBJECT_ID_CAMERA_DYNAMIC));
	

	return S_OK;
}

void SceneTown::Update()
{
	Engine::Scene::Update();
}

void SceneTown::Render()
{
	Engine::Scene::Render();
}

void SceneTown::Release()
{
	Engine::Scene::Release();
}