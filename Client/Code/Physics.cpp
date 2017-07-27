#include "stdafx.h"
#include "Physics.h"


CPhysics::CPhysics(CDevice* _pDevice)
: m_pDevice(_pDevice)
, m_pWorldBuffer(nullptr)
, m_eType(DYNAMIC)

, m_vPos(0.f, 0.f, 0.f)
, m_vRadian(0.f, 0.f, 0.f)
, m_vDir(g_vLook)

, m_fSpeed(0.f)
, m_fAccel(100.f)
, m_fWeight(0.f)

, m_fAcctime(0.f)
, m_fBoosterTimer(0.f)

, m_vScale(1.f, 1.f, 1.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	Init_WorldBuffer();
}

CPhysics::~CPhysics()
{
	Release();
}

CComponent* CPhysics::Create(CDevice* _pDevice)
{
	return new CPhysics(_pDevice);
}

void CPhysics::Init_WorldBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));
	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_World);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	FAILED_CHECK_RETURN(
		m_pDevice->GetDevice()->CreateBuffer(&tBuffer, nullptr, &m_pWorldBuffer), );
}

void CPhysics::SetWorldMatrix(const D3DXVECTOR3& _vPos,
									const D3DXVECTOR3& _vRadian,
									const D3DXVECTOR3& _vScale /* = D3DXVECTOR3(1.f, 1.f, 1.f) */)
{
	m_vPos = _vPos;
	m_vRadian = _vRadian;
	m_vScale = _vScale;

	Update_WorldMatrix();
}

void CPhysics::Update_WorldMatrix()
{
	D3DXMATRIX	matScale, matRotate, matTrans;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matRotate, m_vRadian.y, m_vRadian.x, m_vRadian.z);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = matScale * matRotate * matTrans;
}

void CPhysics::Update()
{
	
}

void CPhysics::Render()
{
	if (DYNAMIC == m_eType)
	{
		D3DXMATRIX	matScale, matRotate, matTrans;
		D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationYawPitchRoll(&matRotate,
			m_vRadian.y, m_vRadian.x, m_vRadian.z);
		D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		m_matWorld = matScale * matRotate * matTrans;
	}


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	ID3D11DeviceContext* pDeviceContext = m_pDevice->GetDeviceContext();
	pDeviceContext->Map(m_pWorldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_World* pMatWorld = (Buffer_World*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatWorld->m_matWorld, &m_matWorld);

	pDeviceContext->Unmap(m_pWorldBuffer, 0);
	pDeviceContext->VSSetConstantBuffers(VS_SLOT_WORLD_MATRIX, 1, &m_pWorldBuffer);
}

void CPhysics::Release()
{
	::Safe_Release(m_pWorldBuffer);
}

void CPhysics::AvoidPhysics(float _fTime){
	if (m_fSpeed > 0.0f){
		m_fSpeed -= m_fAccel * _fTime * m_fAcctime;
		m_fAcctime += .1f;
	}

	m_vRadian.z += m_fSpeed * _fTime;
	D3DXVec3TransformNormal(&m_vDir, &g_vLook, &m_matWorld);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

float CPhysics::BounceDecel(float _fTime){
	if (m_fSpeed >= 50.0f){
		m_fSpeed -= 50.0f;
	}
	if (m_fSpeed >= 0.0f){
		m_fSpeed = m_fAcctime * m_fAccel;
		m_fAcctime -= 0.01f;
	}
	m_vPos -= m_vDir * m_fSpeed * _fTime;

	return m_fSpeed;
}

void CPhysics::BoosterAccel(float _fTime){
	if (m_fSpeed < 300.0f){
		m_fSpeed = m_fAcctime * m_fAccel;
		m_fAcctime += 0.01f;
	}
	m_vPos += m_vDir * m_fSpeed * _fTime;
	m_fBoosterTimer += .1f;
}