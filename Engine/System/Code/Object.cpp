#include "stdafx.h"
#include "Object.h"

#include "Component.h"
#include "Transform.h"

BEGIN(Engine)


Object::Object()
{
	AddDefaultComponent();
}

Object::~Object()
{
	Release_Component();
}

void Object::SetWorldMatrix
(
	const D3DXVECTOR3& _vPos /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/
	, const D3DXVECTOR3& _vRadian /*= D3DXVECTOR3(0.0f, 0.0f, 0.0f)*/
	, const D3DXVECTOR3& _vScale /*= D3DXVECTOR3(1.0f, 1.0f, 1.0f)*/
)
{
	if (m_pTransform == nullptr)
		return;

	m_pTransform->SetWorldMatrix(_vPos, _vRadian, _vScale);
}

const Component* Object::GetComponent(const std::wstring& _wstrComponentKey)
{
	MAPCOMPONENT::iterator iter = m_mapComponent.find(_wstrComponentKey);

	if (iter == m_mapComponent.end())
		return nullptr;

	return iter->second;
}

void Object::AddDefaultComponent()
{
	// Transform ------------
	m_pTransform = new Transform();
	m_mapComponent.insert(
		std::make_pair(L"Transform", m_pTransform));
}

void Object::Update_Component()
{
	MAPCOMPONENT::iterator iter		= m_mapComponent.begin();
	MAPCOMPONENT::iterator iter_end	= m_mapComponent.end();

	for (; iter != iter_end; ++iter)
		iter->second->Update();
}

void Object::Render_Component()
{
	MAPCOMPONENT::iterator iter = m_mapComponent.begin();
	MAPCOMPONENT::iterator iter_end = m_mapComponent.end();

	for (; iter != iter_end; ++iter)
		iter->second->Render();
}

void Object::Release_Component()
{
	for_each(m_mapComponent.begin(), m_mapComponent.end(), Safe_Delete_map());
	m_mapComponent.clear();
}

HRESULT Object::Init()
{
	m_eObjState = EState::STATE_ALIVE;

	return S_OK;
}


END