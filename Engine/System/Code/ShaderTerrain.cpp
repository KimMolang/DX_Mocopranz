#include "stdafx.h"
#include "ShaderTerrain.h"

#include "GraphicDevice.h"

BEGIN(Engine)


ShaderTerrain * ShaderTerrain::Create()
{
	ShaderTerrain* pComponent = new ShaderTerrain();
	if (FAILED(pComponent->Init()))
		::Safe_Delete(pComponent);

	return pComponent;
}

ShaderTerrain::ShaderTerrain()
{

}

ShaderTerrain::~ShaderTerrain()
{

}

HRESULT ShaderTerrain::Init()
{
	D3D11_INPUT_ELEMENT_DESC tInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT iElementNum = ARRAYSIZE(tInputLayout);


	DWORD swFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	swFlag |= D3D10_SHADER_DEBUG;
#endif

	ID3DBlob* pBlob = NULL, *pErrorBlob = NULL;
	ID3D11Device* pDevice = GraphicDevice::GetInstance()->GetDevice();

	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/HLSL/terrain.hlsl", NULL, NULL,
		"VS", "vs_4_0", swFlag, 0, NULL, &pBlob, &pErrorBlob, NULL)))
	{
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pVertexShader);
		pDevice->CreateInputLayout(
			tInputLayout, iElementNum, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pVertexLayout);
	}
	else
	{
		if (pErrorBlob) { CHECK_FAILED_MSG(E_FAIL, L"셰이더 컴파일 실패"); }
		else { CHECK_FAILED_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다."); }
		return E_FAIL;
	}

	pBlob = pErrorBlob = NULL;
	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/HLSL/terrain.hlsl", NULL, NULL,
		"PS", "ps_4_0", swFlag, 0, NULL, &pBlob, &pErrorBlob, NULL)))
	{
		pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pPixelShader);
	}
	else
	{
		if (pErrorBlob) { CHECK_FAILED_MSG(E_FAIL, L"셰이더 컴파일 실패"); }
		else { CHECK_FAILED_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다."); }
		return E_FAIL;
	}
	::Safe_Release(pBlob);
	::Safe_Release(pErrorBlob);

	return S_OK;
}

void ShaderTerrain::Render()
{
	// http://copynull.tistory.com/307?category=649931
	//D3D11_MAPPED_SUBRESOURCE mappedResource;
	//ID3D11DeviceContext* pDeviceContext = m_pGraphicDevice->GetDeviceContext();
	//pDeviceContext->Map(m_pWorldBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

	//Buffer_World* pMatWorld = (Buffer_World*)tSubreResource.pData;
	//D3DXMatrixTranspose(&pMatWorld->m_matWorld, &m_matWorld);

	//pDeviceContext->Unmap(m_pWorldBuffer, 0);
	//pDeviceContext->VSSetConstantBuffers(VS_SLOT_WORLD_MATRIX, 1, &m_pWorldBuffer);

	Shader::Render();
}


END