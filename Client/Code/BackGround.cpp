#include "stdafx.h"
#include "BackGround.h"

#include "Component.h"


CBackGround::CBackGround(CDevice* _pDevice)
: CObj(_pDevice)
, m_pBuffer(nullptr)
{
}

CBackGround::~CBackGround()
{

}

void CBackGround::SetWorldMatrix(const D3DXVECTOR3& _vPos /*= D3DXVECTOR3(0.f, 0.f, 0.f)*/,
	const D3DXVECTOR3& _vRadian /*= D3DXVECTOR3(0.f, 0.f, 0.f)*/,
	const D3DXVECTOR3& _vScale /*= D3DXVECTOR3(0.f, 0.f, 0.f)*/)
{
	m_pPhysics->SetWorldMatrix(_vPos, _vRadian, _vScale);
	D3DXVec3TransformNormal(&m_pPhysics->m_vDir, &g_vLook, &m_pPhysics->m_matWorld);
	D3DXVec3Normalize(&m_pPhysics->m_vDir, &m_pPhysics->m_vDir);
}
