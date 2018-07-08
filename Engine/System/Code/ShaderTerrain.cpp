#include "stdafx.h"
#include "ShaderTerrain.h"

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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT iElementNum = ARRAYSIZE(tInputLayout);


	DWORD swFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	swFlag |= D3D10_SHADER_DEBUG;
#endif

	ID3DBlob* pBlob = nullptr, *pErrorBlob = nullptr;
	ID3D11Device* pDevice = GraphicDevice::GetInstance()->GetDevice();


	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/HLSL/terrain.hlsl", nullptr, nullptr,
		"VS", "vs_5_0", swFlag, 0, nullptr, &pBlob, &pErrorBlob, nullptr)))
	{
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pVertexShader);
		pDevice->CreateInputLayout(
			tInputLayout, iElementNum, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pVertexLayout);
	}
	else
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (pErrorBlob)
		{
			OutputShaderErrorMessage(pErrorBlob, "Error_ShaderTerrain_Init_VS.txt");
			CHECK_FAILED_MSG(E_FAIL
				, L"Failed. ErrorMessage is saved as Error_ShaderTerrain::Init::VS.txt");
		}
		else
		{
			CHECK_FAILED_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다.");
		}

		return E_FAIL;
	}

	pBlob = pErrorBlob = nullptr;
	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/HLSL/terrain.hlsl", nullptr, nullptr,
		"PS", "ps_5_0", swFlag, 0, nullptr, &pBlob, &pErrorBlob, nullptr)))
	{
		pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, &m_pPixelShader);
	}
	else
	{
		if (pErrorBlob)
		{
			OutputShaderErrorMessage(pErrorBlob, "Error_ShaderTerrain_Init_PS.txt");
			CHECK_FAILED_MSG(E_FAIL
				, L"Failed. ErrorMessage is saved as Error_ShaderTerrain::Init::PS.txt");
		}
		else
		{
			CHECK_FAILED_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다.");
		}

		return E_FAIL;
	}
	::Safe_Release(pBlob);
	::Safe_Release(pErrorBlob);


	return S_OK;
}

void ShaderTerrain::Render()
{
	Shader::Render();
}


END