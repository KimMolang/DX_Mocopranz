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
	Engine::Resource* pResurceCloned = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_BUFFER, L"Test_Buffer_Cube");
	CHECK_NULLPTR_RETURN(pResurceCloned, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Buffer_Box", pResurceCloned));

	return S_OK;
}

Engine::Object::EState TestObject::Update()
{
	return Engine::Object::Update();
}

void TestObject::Render()
{
	Engine::Object::Render();
}

void TestObject::Release()
{

}
