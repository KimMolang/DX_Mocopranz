#include "stdafx.h"
#include "VIBufferCube.h"

BEGIN(Engine)


VIBufferCube * VIBufferCube::Create()
{
	VIBufferCube* pComponent = new VIBufferCube();
	if (FAILED(pComponent->Init()))
		::Safe_Delete(pComponent);

	return pComponent;
}

VIBufferCube::VIBufferCube()
{

}

VIBufferCube::~VIBufferCube()
{
	
}

HRESULT VIBufferCube::Init()
{
	VIBuffer::Init();

	m_nVtxNum = 8;
	m_nVtxStride = sizeof(VertexColor);
	m_nVtxOffset = 0;
	m_nVtxStart = 1;

	m_nIdxNum = 36;
	m_nIdxStart = 0;
	m_nIdxPlus = 0;

	Init_Vtx();
	Init_Idx();

	VIBuffer::CreateRasterizerState();


	return S_OK;
}

void VIBufferCube::Init_Vtx()
{
	VertexColor pVertex[] =
	{
		{ D3DXVECTOR3(-1.f, 1.f, -1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(1.f, 1.f, -1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(1.f, -1.f, -1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(-1.f, -1.f, -1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(-1.f, 1.f, 1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(1.f, 1.f, 1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(1.f, -1.f, 1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) },

	{ D3DXVECTOR3(-1.f, -1.f, 1.f)
		, D3DXVECTOR4(0.f, 1.f, 0.f, 1.f) }
	};


	D3D11_BUFFER_DESC tBufferDesc;
	ZeroMemory(&tBufferDesc, sizeof(D3D11_BUFFER_DESC));
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.ByteWidth = m_nVtxStride * m_nVtxNum;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.CPUAccessFlags = 0;
	tBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA tData;
	ZeroMemory(&tData, sizeof(D3D11_SUBRESOURCE_DATA));
	tData.pSysMem = pVertex;
	CHECK_FAILED_RETURN(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tData, &m_pVtxBuffer), );
}

void VIBufferCube::Init_Idx()
{
	Index16 pIdx[] =
	{
	// Front
	{ Index16(0, 1, 2) },
	{ Index16(0, 2, 3) },

	// Right
	{ Index16(1, 5, 6) },
	{ Index16(1, 6, 2) },

	// Bottom
	{ Index16(3, 2, 6) },
	{ Index16(3, 6, 7) },

	// Left
	{ Index16(4, 0, 3) },
	{ Index16(4, 3, 7) },

	// Top
	{ Index16(4, 5, 1) },
	{ Index16(4, 1, 0) },

	// Back
	{ Index16(5, 4, 7) },
	{ Index16(5, 7, 6) }
	};


	D3D11_BUFFER_DESC tBufferDesc;
	ZeroMemory(&tBufferDesc, sizeof(D3D11_BUFFER_DESC));
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	tBufferDesc.ByteWidth = sizeof(WORD)* m_nIdxNum;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA tData;
	ZeroMemory(&tData, sizeof(D3D11_SUBRESOURCE_DATA));
	tData.pSysMem = pIdx;
	CHECK_FAILED_RETURN(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&tBufferDesc, &tData, &m_pIdxBuffer), );
}

void VIBufferCube::Update()
{

}


END