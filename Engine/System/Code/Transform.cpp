#include "stdafx.h"
#include "Transform.h"

#include "Engine_Define_Buffer_Index.h"
#include "Engine_Struct_Buffer.h"

#include "GraphicDevice.h"

BEGIN(Engine)


Transform * Transform::Create()
{
	return new Transform();
}

Transform::Transform()
	: m_pGraphicDevice(GraphicDevice::GetInstance())
	, m_pWorldBuffer(nullptr)
	, m_eType(TransformType::DYNAMIC)

	, m_vPos(0.f, 0.f, 0.f)
	, m_vRadian(0.f, 0.f, 0.f)
	, m_vDir(DEFAULT_VALUE_LOOK_VECTOR)
	, m_vScale(1.f, 1.f, 1.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	Init_WorldBuffer();
}

Transform::~Transform()
{
	Release();
}

void Transform::Init_WorldBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));
	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_World);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	CHECK_FAILED_RETURN(
		m_pGraphicDevice->GetDevice()->CreateBuffer(&tBuffer, nullptr, &m_pWorldBuffer), );
}

void Transform::SetWorldMatrix
(
	const D3DXVECTOR3& _vPos,
	const D3DXVECTOR3& _vRadian,
	const D3DXVECTOR3& _vScale /* = D3DXVECTOR3(1.f, 1.f, 1.f) */
)
{
	m_vPos = _vPos;
	m_vRadian = _vRadian;
	m_vScale = _vScale;

	Update_WorldMatrix();

	D3DXVec3TransformNormal(&m_vDir, &DEFAULT_VALUE_LOOK_VECTOR, &m_matWorld);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

void Transform::Update_WorldMatrix()
{
	D3DXMATRIX	matScale, matRotate, matTrans;
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matRotate, m_vRadian.y, m_vRadian.x, m_vRadian.z);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = matScale * matRotate * matTrans;
}

void Transform::Update()
{

}

void Transform::Render()
{
	if (TransformType::DYNAMIC == m_eType)
	{
		D3DXMATRIX	matScale, matRotate, matTrans;
		D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
		D3DXMatrixRotationYawPitchRoll(&matRotate,
			m_vRadian.y, m_vRadian.x, m_vRadian.z);
		D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		m_matWorld = matScale * matRotate * matTrans;
	}


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	ID3D11DeviceContext* pDeviceContext = m_pGraphicDevice->GetDeviceContext();
	pDeviceContext->Map(m_pWorldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_World* pMatWorld = (Buffer_World*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatWorld->m_matWorld, &m_matWorld);

	pDeviceContext->Unmap(m_pWorldBuffer, 0);
	pDeviceContext->VSSetConstantBuffers(VS_SLOT_WORLD_MATRIX, 1, &m_pWorldBuffer);
}

void Transform::Release()
{
	::Safe_Release(m_pWorldBuffer);
}


END