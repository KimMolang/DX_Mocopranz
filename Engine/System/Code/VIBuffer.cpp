#include "stdafx.h"
#include "VIBuffer.h"

#include "GraphicDevice.h"

BEGIN(Engine)


void VertexAni::AddBone(int _iIdx, float _fWeight)
{
	for (int i = 0; i < BONE_NUM; ++i)
	{
		if (fBoneWeight[i] <= 0.0f)
		{
			iBoneIdx[i] = _iIdx;
			fBoneWeight[i] = _fWeight;
			return;
		}
	}

	fBoneWeight[0] += _fWeight;
}

VIBuffer::VIBuffer()
	: m_pRasterizerState(nullptr)

	, m_pVtxBuffer(nullptr)
	, m_nVtxNum(0)
	, m_nVtxStride(0)
	, m_nVtxOffset(0)
	, m_nVtxStart(0)

	, m_pIdxBuffer(nullptr)
	, m_nIdxNum(0)
	, m_nIdxStart(0)
	, m_nIdxPlus(0)
{

}

VIBuffer::~VIBuffer()
{

}

void VIBuffer::Render()
{
	if (nullptr == m_pVtxBuffer)
		return;

	ID3D11DeviceContext* pDeviceContext = GraphicDevice::GetInstance()->GetDeviceContext();
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &m_nVtxStride, &m_nVtxOffset);
	pDeviceContext->IASetIndexBuffer(m_pIdxBuffer, DXGI_FORMAT_R16_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_pRasterizerState)
		pDeviceContext->RSSetState(m_pRasterizerState);

	pDeviceContext->DrawIndexed(m_nIdxNum, m_nIdxStart, m_nIdxPlus);
	pDeviceContext->Draw(m_nVtxNum, m_nVtxStart);
}

void VIBuffer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC tRasterizerDesc;
	ZeroMemory(&tRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	tRasterizerDesc.CullMode = D3D11_CULL_BACK;
	tRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	GraphicDevice::GetInstance()->GetDevice()->CreateRasterizerState(&tRasterizerDesc, &m_pRasterizerState);
}


END