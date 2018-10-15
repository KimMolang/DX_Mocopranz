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

	// Texture ------------
	m_pTexture = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_TEXTURE, L"Test_Texture_Terrain");
	CHECK_NULLPTR_RETURN(m_pTexture, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Texture_Terrain", m_pTexture));


	// Model Buffer ---------------------
	m_pBuffer = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_BUFFER, L"Test_Buffer_Terrain");
	CHECK_NULLPTR_RETURN(m_pBuffer, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Buffer_Terrain", m_pBuffer));


	// Shader ---------------------
	m_pShader = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_SHADER, L"Test_Shader_Terrain");
	CHECK_NULLPTR_RETURN(m_pShader, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Shader", m_pShader));

	return S_OK;
}

Engine::Object::EState TestTerrain::Update()
{
	Engine::Object::Update_Component();
	return m_eObjState;
}

void TestTerrain::Render()
{
	m_pTransform->Render();
	m_pTexture->Render();
	m_pShader->Render();
	m_pBuffer->Render();

	//Engine::Object::Render_Component();
}

void TestTerrain::Release()
{

}
