#include "stdafx.h"
#include "TestObject.h"

#include "ResourceMgr.h"
#include "Export_Function_Mgr.h"


TestObject::TestObject()
{
}

TestObject::~TestObject()
{

}

HRESULT TestObject::Init()
{
	Engine::Object::Init();

	// Model Buffer ---------------------
	m_pBuffer = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_BUFFER, L"Test_Buffer_Cube");
	CHECK_NULLPTR_RETURN(m_pBuffer, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Buffer_Box", m_pBuffer));


	// Shader ---------------------
	m_pShader = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_SHADER, L"Test_Shader_Color");
	CHECK_NULLPTR_RETURN(m_pShader, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Shader", m_pShader));

	return S_OK;
}

Engine::Object::EState TestObject::Update()
{
	return Engine::Object::Update();
}

void TestObject::Render()
{
	m_pTransform->Render();
	m_pShader->Render();
	m_pBuffer->Render();

	//Engine::Object::Render();
}

void TestObject::Release()
{

}
