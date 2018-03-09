#include "stdafx.h"
#include "SceneTown.h"

// for Test (수정)
#include "ResourceMgr.h"
#include "ObjectMgr.h"
#include "Export_Function_Mgr.h"
#include "VIBufferCube.h"
#include "../Object/TestObject.h"
#include "CameraDynamic.h"

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
	Engine::GetResourceMgr()->AddResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC
		, Engine::ResourceMgr::RESOURCE_TYPE_MODEL
		, L"Test_Buffer_Cube"
		, new Engine::VIBufferCube());

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