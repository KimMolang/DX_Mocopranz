#include "stdafx.h"
#include "TestTerrain.h"

#include "ResourceMgr.h"
#include "Export_Function_Mgr.h"


TestTerrain::TestTerrain()
{
}

TestTerrain::~TestTerrain()
{

}

HRESULT TestTerrain::Init()
{
	Engine::Object::Init();

	// Model Buffer ---------------------
	Engine::Resource* pResurceCloned = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_BUFFER, L"Test_Buffer_Terrain");
	CHECK_NULLPTR_RETURN(pResurceCloned, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Buffer_Terrain", pResurceCloned));

	return S_OK;
}

Engine::Object::EState TestTerrain::Update()
{
	Engine::Object::Update_Component();
	return m_eObjState;
}

void TestTerrain::Render()
{
	Engine::Object::Render_Component();
}

void TestTerrain::Release()
{

}
