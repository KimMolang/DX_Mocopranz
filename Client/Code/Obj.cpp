#include "stdafx.h"
#include "Obj.h"

#include "Component.h"

bool CObj::m_bRenderObjCol_ProgressRateZone = false;
bool CObj::m_bRenderObjCol_Other			= false;
bool CObj::m_bRenderObjCol_UnMovableZone	= false;


CObj::CObj(CDevice* _pDevice)
: m_pDevice(_pDevice)
, m_eObjState(OBJ_STATE_NONE)
, m_pPhysics(nullptr)
{
	AddComponent();
}

CObj::~CObj()
{
	Release_Component();
}

void CObj::AddComponent()
{
	// Physics ------------
	m_pPhysics = dynamic_cast<CPhysics*>(CPhysics::Create(m_pDevice));
	NULL_CHECK(m_pPhysics);
	m_mapComponent.insert(make_pair(L"Physics", m_pPhysics));
}

const CComponent* CObj::GetComponent(const wstring& _wstrComponentKey)
{
	map<wstring, CComponent*>::iterator iter = m_mapComponent.find(_wstrComponentKey);

	if (iter == m_mapComponent.end())
		return nullptr;

	return iter->second;
}

void CObj::Update_Component()
{
	map<wstring, CComponent*>::iterator iter = m_mapComponent.begin();
	map<wstring, CComponent*>::iterator iter_end = m_mapComponent.end();

	for (; iter != iter_end; ++iter)
		iter->second->Update();
}

void CObj::Release_Component()
{
	for_each(m_mapComponent.begin(), m_mapComponent.end(), DeleteMap());
	m_mapComponent.clear();
}


