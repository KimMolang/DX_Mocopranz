#include "stdafx.h"
#include "Object.h"

#include "Component.h"

BEGIN(Engine)


Object::Object()
{
	AddDefaultComponent();
}

Object::~Object()
{
	Release_Component();
}

const Component* Object::GetComponent(const Component::EType& _eType)
{
	MAPCOMPONENT::iterator iter = m_mapComponent.find(_eType);

	if (iter == m_mapComponent.end())
		return NULL;

	return iter->second;
}

void Object::AddDefaultComponent()
{
	// Transform ------------
	//m_pPhysics = dynamic_cast<CPhysics*>(CPhysics::Create(m_pDevice));
	//NULL_CHECK(m_pPhysics);
	//m_mapComponent.insert(make_pair(L"Physics", m_pPhysics));
}

void Object::Update_Component()
{
	MAPCOMPONENT::iterator iter		= m_mapComponent.begin();
	MAPCOMPONENT::iterator iter_end	= m_mapComponent.end();

	for (; iter != iter_end; ++iter)
		iter->second->Update();
}

void Object::Release_Component()
{
	for_each(m_mapComponent.begin(), m_mapComponent.end(), Safe_Delete_map());
	m_mapComponent.clear();
}


END