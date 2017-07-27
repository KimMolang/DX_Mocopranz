#include "stdafx.h"
#include "Layer.h"

#include "Obj.h"


CLayer::CLayer(CDevice* _pDevice)
: m_pDevice(_pDevice)
{

}

CLayer::~CLayer()
{
	Release_Obj();
}

CLayer* CLayer::Create(CDevice* _pDevice)
{
	return new CLayer(_pDevice);
}

HRESULT CLayer::AddObj(const wstring& _wstrObjKey, CObj* _pObj)
{
	if (_pObj)
	{
		map<wstring, ListObj>::iterator iter = m_mapObjList.find(_wstrObjKey);

		if (iter == m_mapObjList.end())
			m_mapObjList[_wstrObjKey] = ListObj();

		m_mapObjList[_wstrObjKey].push_back(_pObj);
	}
	else return E_FAIL;

	return S_OK;
}

const CObj* CLayer::GetObj(const wstring& _wstrObjKey,
							const unsigned int& _iIndex /*= 0*/)
{
	map<wstring, ListObj>::iterator	iterMap = m_mapObjList.find(_wstrObjKey);

	if (iterMap == m_mapObjList.end())
		return nullptr;

	if (_iIndex >= iterMap->second.size())
		return nullptr;


	ListObj::iterator	iterList = iterMap->second.begin();
	for (unsigned int i = 0; i < _iIndex; ++iterList) {}
	return (*iterList);
}

const CComponent* CLayer::GetComponent(const wstring& _wstrObjKey, const wstring& _wstrComponentKey)
{
	map<wstring, ListObj>::iterator	iterMap = m_mapObjList.find(_wstrObjKey);

	if (iterMap == m_mapObjList.end())
		return nullptr;

	ListObj::iterator	iterList		= iterMap->second.begin();
	ListObj::iterator	iterList_end	= iterMap->second.end();

	for (; iterList != iterList_end; ++iterList)
	{
		const CComponent* pComponent = (*iterList)->GetComponent(_wstrComponentKey);

		if (pComponent != nullptr)
			return pComponent;
	}
	return nullptr;
}

void CLayer::Update_Obj()
{
	map<wstring, ListObj>::iterator	iterMap = m_mapObjList.begin();
	map<wstring, ListObj>::iterator iterMap_end = m_mapObjList.end();

	ListObj::iterator	iterList;
	ListObj::iterator	iterList_end;


	for (; iterMap != iterMap_end; ++iterMap)
	{
		iterList = iterMap->second.begin();
		iterList_end = iterMap->second.end();

		for (; iterList != iterList_end;)
		{
			if ((*iterList)->Update() == CObj::OBJ_STATE_DIE)
			{
				::Safe_Delete(*iterList);
				iterList = iterMap->second.erase(iterList);
			}
			else ++iterList;
		}
	}
}

void CLayer::Render_Obj()
{
	map<wstring, ListObj>::iterator	iterMap = m_mapObjList.begin();
	map<wstring, ListObj>::iterator iterMap_end = m_mapObjList.end();

	ListObj::iterator	iterList;
	ListObj::iterator	iterList_end;


	for (; iterMap != iterMap_end; ++iterMap)
	{
		iterList = iterMap->second.begin();
		iterList_end = iterMap->second.end();

		for (; iterList != iterList_end; ++iterList)
			(*iterList)->Render();
	}
}

void CLayer::Release_Obj()
{
	map<wstring, ListObj>::iterator	iterMap = m_mapObjList.begin();
	map<wstring, ListObj>::iterator iterMap_end = m_mapObjList.end();

	ListObj::iterator	iterList;
	ListObj::iterator	iterList_end;


	for (; iterMap != iterMap_end; ++iterMap)
	{
		iterList = iterMap->second.begin();
		iterList_end = iterMap->second.end();

		for (; iterList != iterList_end; ++iterList)
			::Safe_Delete(*iterList);

		iterMap->second.clear();
	}
	m_mapObjList.clear();
}




