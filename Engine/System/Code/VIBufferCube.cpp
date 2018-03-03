#include "stdafx.h"
#include "VIBufferCube.h"

#include "GraphicDevice.h"
#include "Export_Function_Mgr_GraphicDevice.h"

//#include "ResourceMgr.h"
//#include "ColorShader.h"

BEGIN(Engine)


VIBufferCube::VIBufferCube()
//	: m_pColorShader(nullptr)
{

}

VIBufferCube::~VIBufferCube()
{
	Release();
}

HRESULT VIBufferCube::Init()
{
	m_nVtxNum = 8;
	m_nVtxStride = sizeof(VertexColor);
	m_nVtxOffset = 0;
	m_nVtxStart = 1;

	m_nIdxNum = 36;
	m_nIdxStart = 0;
	m_nIdxPlus = 0;

	Init_Vtx();
	Init_Idx();
	Init_ColorShader();
	CreateRasterizerState();

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
		GetGraphicDevice()->GetDevice()->CreateBuffer(&tBufferDesc, &tData, &m_pVtxBuffer), );
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
		GetGraphicDevice()->GetDevice()->CreateBuffer(&tBufferDesc, &tData, &m_pIdxBuffer), );
}

void VIBufferCube::Init_ColorShader()
{
	//m_pColorShader = dynamic_cast<CColorShader*>(CResourceMgr::GetInstance()->CloneResource(
	//	CResourceMgr::RESOURCE_ATTRI_STATIC, CResourceMgr::RESOURCE_TYPE_SHADER, L"Shader_Color"));
	//nullptr_CHECK(m_pColorShader);
}

void VIBufferCube::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC tRasterizerDesc;
	ZeroMemory(&tRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	tRasterizerDesc.CullMode = D3D11_CULL_NONE;
	tRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	GetGraphicDevice()->GetDevice()->CreateRasterizerState(&tRasterizerDesc, &m_pRasterizerState);
}

void VIBufferCube::Update()
{

}

void VIBufferCube::Render()
{
	//m_pColorShader->Render();
	VIBuffer::Render();
}

void VIBufferCube::Release()
{
	if ((*m_pRefCnt) == 0)
	{
		::Safe_Release(m_pVtxBuffer);
		::Safe_Release(m_pIdxBuffer);
		//::Safe_Delete(m_pColorShader);
		Resource::Release_RefCnt();
	}
	else --(*m_pRefCnt);
}


END