#include "stdafx.h"
#include "SceneTown.h"

// for Test (수정)
#include "ResourceMgr.h"
#include "ObjectMgr.h"
#include "Export_Function_Mgr.h"
#include "VIBufferCube.h"
#include "../Object/TestObject.h"
#include "CameraDynamic.h"
#include "ShaderColor.h"

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
	TestObject* pTestObject = new TestObject();
	pTestObject->Init();
	Engine::GetObjectMgr()->AddObj(Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC, pTestObject);

	// Camera
	Engine::CameraDynamic* pCamera = new Engine::CameraDynamic();
	pCamera->Init();
	Engine::GetObjectMgr()->AddObj(Engine::Scene::ELayerType::LAYER_TYPE_GAMELOGIC, pCamera);
	

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