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

	// (수정)
	// 생각해보니까 우린 버퍼를 복사해서 쓰기 때문에 버퍼 안에 쉐이더라는 값이 있으면 안 됨..
	// 쉐이더도 따로 들고 있어야 하네?!
	// 그럼 렌더 어떻게 하지?!?!? 빠재 프레임워크 봐야겠다
	// 무튼 지금은 쉐이더 셋팅 안해서 터짐 (이어서)
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
