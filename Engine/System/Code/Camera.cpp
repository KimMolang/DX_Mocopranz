#include "stdafx.h"
#include "Camera.h"

#include "Engine_Define_Buffer_Index.h"
#include "Engine_Struct_Buffer.h"

#include "GraphicDevice.h"

BEGIN(Engine)


const D3DXVECTOR3 Camera::m_vUp = D3DXVECTOR3(0.f, 1.f, 0.f);

Camera::Camera()
	: Object()
	, m_vEye(0.f, 0.f, 0.f)
	, m_vAt(1.f, 0.f, 0.f)

	, m_fFovy(0.f)
	, m_fAspect(0.f)
	, m_fNear(0.f)
	, m_fFar(0.f)

	, m_pViewBuffer(nullptr)
	, m_pProjBuffer(nullptr)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matOrtho);

	Init_ViewBuffer();
	Init_ProjBuffer();
	Init_Viewport();
}

Camera::~Camera()
{
	::Safe_Release(m_pViewBuffer);
	::Safe_Release(m_pProjBuffer);
}

void Camera::Init_ViewBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));

	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_View);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CHECK_FAILED_RETURN(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&tBuffer, NULL, &m_pViewBuffer), );
}

void Camera::Init_ProjBuffer()
{
	D3D11_BUFFER_DESC tBuffer;
	ZeroMemory(&tBuffer, sizeof(D3D11_BUFFER_DESC));

	tBuffer.Usage = D3D11_USAGE_DYNAMIC;
	tBuffer.ByteWidth = sizeof(Buffer_Proj);
	tBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBuffer.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CHECK_FAILED_RETURN(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&tBuffer, NULL, &m_pProjBuffer), );
}

HRESULT Camera::Init()
{
	Object::Init();

	m_fFovy = (float)D3DXToRadian(90.f);
	//m_fAspect = float(CLIENT_WINCX) / CLIENT_WINCY; // (수정) (옵션) 해상도
	m_fAspect = float(1280) / 720; // (수정) (옵션) 해상도
	m_fNear = 1.f;
	m_fFar = 2400.f;

	Camera::Invalidate_View();
	Camera::Invalidate_Proj();


	return S_OK;
}

void Camera::Init_Viewport() // (수정) (옵션) 해상도
{
	m_tViewport.TopLeftX = m_tViewport.TopLeftY = 0.f;
	m_tViewport.Width = (float)1280; // (수정) (옵션) 해상도
	m_tViewport.Height = (float)720; // (수정) (옵션) 해상도
	m_tViewport.MinDepth = 0.f;
	m_tViewport.MaxDepth = 1.f;

	
	GraphicDevice::GetInstance()->GetDeviceContext()->RSSetViewports(1, &m_tViewport);

	// (수정) (옵션) 해상도
	D3DXMatrixOrthoLH(&m_matOrtho, (float)1280, (float)720, 0.f, 1.f);
}

void Camera::Invalidate_View()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	GraphicDevice::GetInstance()->GetDeviceContext()->Map(m_pViewBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_View* pMatView = (Buffer_View*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatView->m_matView, &m_matView);

	GraphicDevice::GetInstance()->GetDeviceContext()->Unmap(m_pViewBuffer, 0);
	GraphicDevice::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(VS_SLOT_VIEW_MATRIX, 1, &m_pViewBuffer);
}

void Camera::Invalidate_Proj()
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovy, m_fAspect, m_fNear, m_fFar);


	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	GraphicDevice::GetInstance()->GetDeviceContext()->Map(m_pProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_Proj* pMatProj = (Buffer_Proj*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatProj->m_matProj, &m_matProj);

	GraphicDevice::GetInstance()->GetDeviceContext()->Unmap(m_pProjBuffer, 0);
	GraphicDevice::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(VS_SLOT_PROJECTION_MATRIX, 1, &m_pProjBuffer);
}

void Camera::Invalidate_Ortho()
{
	D3D11_MAPPED_SUBRESOURCE tSubreResource;
	GraphicDevice::GetInstance()->GetDeviceContext()->Map(m_pProjBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	Buffer_Proj* pMatProj = (Buffer_Proj*)tSubreResource.pData;
	D3DXMatrixTranspose(&pMatProj->m_matProj, &m_matOrtho);

	GraphicDevice::GetInstance()->GetDeviceContext()->Unmap(m_pProjBuffer, 0);
	GraphicDevice::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(VS_SLOT_PROJECTION_MATRIX, 1, &m_pProjBuffer);
}


END