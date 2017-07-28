#include "stdafx.h"
#include "ObjMgr.h"

#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)


CObjMgr::CObjMgr()
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
		m_pLayer[i] = nullptr;
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObj(const CLayer::LayerType& _eLayerType,
					const wstring& _wstrObjKey,
					CObj* _pObj)
{
	if (m_pLayer[_eLayerType] == nullptr || _pObj == nullptr)
		return;

	m_pLayer[_eLayerType]->AddObj(_wstrObjKey, _pObj);
}

const CObj* CObjMgr::GetObj(const CLayer::LayerType& _eLayerType,
					const wstring& _wstrObjKey,
					const int& _iIdx /*= 0*/)
{
	if (m_pLayer[_eLayerType] == nullptr)
		return nullptr;

	return m_pLayer[_eLayerType]->GetObj(_wstrObjKey, _iIdx);
}

void CObjMgr::Release()
{
	for (int i = 0; i < CLayer::LAYERTYPE_END; ++i)
		m_pLayer[i] = nullptr;
}
