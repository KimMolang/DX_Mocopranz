#include "stdafx.h"
#include "ObjectMgr.h"

#include "Object.h"
#include "Layer.h"

BEGIN(Engine)
IMPLEMENT_SINGLETON(ObjectMgr)


ObjectMgr::ObjectMgr()
{
	for (int i = 0; i < Scene::ELayerType::LAYER_TYPE_MAX; ++i)
		m_pLayer[i] = nullptr;
}

ObjectMgr::~ObjectMgr()
{
	Release();
}

void ObjectMgr::AddObj
(
	const Scene::ELayerType& _eLayerType
	//, const std::wstring& _wstrObjKey
	, Object* _pObj
)
{
	if (m_pLayer[_eLayerType] == nullptr || _pObj == nullptr)
		return;

	m_pLayer[_eLayerType]->AddObj(/*_wstrObjKey, */_pObj);
}

void ObjectMgr::Release()
{
	for (int i = 0; i < Scene::ELayerType::LAYER_TYPE_MAX; ++i)
		m_pLayer[i] = nullptr;
}


END