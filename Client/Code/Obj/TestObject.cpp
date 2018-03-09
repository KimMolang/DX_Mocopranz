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
	// Model Buffer ---------------------
	Engine::Resource* pResurceCloned = Engine::GetResourceMgr()->CloneResource(
		Engine::ResourceMgr::RESOURCE_ATTRI_STATIC, Engine::ResourceMgr::RESOURCE_TYPE_MODEL, L"Test_Buffer_Cube");
	CHECK_NULLPTR_RETURN(pResurceCloned, E_FAIL);

	m_mapComponent.insert(std::make_pair(L"Buffer", pResurceCloned));

	return S_OK;
}

Engine::Object::EState TestObject::Update()
{
	Engine::Object::Update_Component();
	return m_eObjState;
}

void TestObject::Render()
{
	Engine::Object::Render_Component();
}

void TestObject::Release()
{

}
