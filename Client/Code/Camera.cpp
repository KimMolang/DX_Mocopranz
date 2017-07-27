#include "stdafx.h"
#include "Camera.h"

#include "Value.h"

const D3DXVECTOR3 CCamera::m_vUp		= D3DXVECTOR3(0.f, 1.f, 0.f);

CCamera::CCamera(CDevice* _pDevice)
: CObj(_pDevice)

, m_vEye(0.f, 0.f, 0.f)
, m_vAt(1.f, 0.f, 0.f)

, m_fFovy(0.f)
, m_fAspect(0.f)
, m_fNear(0.f)
, m_fFar(0.f)

, m_pViewBuffer(nullptr)
, m_pProjBuffer(nullptr)

, m_pDeviceContext(_pDevice->GetDeviceContext())
//, m_pInfoSubject(CInfoSubject::GetInstance())
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matOrtho);

	Init_ViewBuffer();
	Init_ProjBuffer();
	Init_Viewport();
}

CCamera::~CCamera()
{
	::Safe_Release(m_pViewBuffer);
	::Safe_Release(m_pProjBuffer);
}

void CCamera::Init_ViewBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));

	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_View);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	FAILED_CHECK_RETURN(
		m_pDevice->GetDevice()->CreateBuffer(&tBuffer, nullptr, &m_pViewBuffer), );
}

void CCamera::Init_ProjBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));

	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_Proj);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	FAILED_CHECK_RETURN(
		m_pDevice->GetDevice()->CreateBuffer(&tBuffer, nullptr, &m_pProjBuffer), );
}

void CCamera::Init_Viewport()
{
	m_tViewport.TopLeftX = m_tViewport.TopLeftY = 0.f;
	m_tViewport.Width = (float)CLIENT_WINCX;
	m_tViewport.Height = (float)CLIENT_WINCY;
	m_tViewport.MinDepth = 0.f;
	m_tViewport.MaxDepth = 1.f;

	m_pDeviceContext->RSSetViewports(1, &m_tViewport);


	D3DXMatrixOrthoLH(&m_matOrtho, (float)CLIENT_WINCX, (float)CLIENT_WINCY, 0.f, 1.f);
}

void CCamera::InitInfoSubject()
{
	//m_pInfoSubject->AddData(CInfoSubject::DATA_TYPE_CAMERA_VIEW, &m_matView);
	//m_pInfoSubject->AddData(CInfoSubject::DATA_TYPE_CAMERA_PROJECTION, &m_matProj);
	//m_pInfoSubject->AddData(CInfoSubject::DATA_TYPE_CAMERA_EYE, &m_vEye);
}

void CCamera::Invalidate_View()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	m_pDeviceContext->Map(m_pViewBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_View* pMatView = (Buffer_View*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatView->m_matView, &m_matView);

	m_pDeviceContext->Unmap(m_pViewBuffer, 0);
	m_pDeviceContext->VSSetConstantBuffers(VS_SLOT_VIEW_MATRIX, 1, &m_pViewBuffer);
}

void CCamera::Invalidate_Proj()
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovy, m_fAspect, m_fNear, m_fFar);


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	m_pDeviceContext->Map(m_pProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_Proj* pMatProj = (Buffer_Proj*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatProj->m_matProj, &m_matProj);

	m_pDeviceContext->Unmap(m_pProjBuffer, 0);
	m_pDeviceContext->VSSetConstantBuffers(VS_SLOT_PROJECTION_MATRIX, 1, &m_pProjBuffer);
}

void CCamera::Invalidate_Ortho()
{
	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	m_pDeviceContext->Map(m_pProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_Proj* pMatProj = (Buffer_Proj*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatProj->m_matProj, &m_matOrtho);

	m_pDeviceContext->Unmap(m_pProjBuffer, 0);
	m_pDeviceContext->VSSetConstantBuffers(VS_SLOT_PROJECTION_MATRIX, 1, &m_pProjBuffer);
}