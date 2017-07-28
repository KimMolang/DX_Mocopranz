#include "stdafx.h"
#include "ShaderSkyBox.h"

CShaderSkyBox::CShaderSkyBox(CDevice* _pDevice)
: CShader(_pDevice)
{

}

CShaderSkyBox::~CShaderSkyBox()
{
	Release();
}

CResource* CShaderSkyBox::Create(CDevice* _pDevice)
{
	CShaderSkyBox* pComponent = new CShaderSkyBox(_pDevice);
	if (FAILED(pComponent->Init()))
		::Safe_Delete(pComponent);

	return pComponent;
}

CResource* CShaderSkyBox::Clone()
{
	++(*m_pRefCnt);
	return new CShaderSkyBox(*this);
}

HRESULT CShaderSkyBox::Init()
{
	D3D11_INPUT_ELEMENT_DESC tInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT iElementNum = ARRAYSIZE(tInputLayout);


	DWORD swFlag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	swFlag |= D3D10_SHADER_DEBUG;
#endif

	ID3DBlob* pBlob = nullptr, *pErrorBlob = nullptr;
	ID3D11Device* pDevice = m_pDevice->GetDevice();

	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/Fx/SkyBox.fx", nullptr, nullptr,
		"VS", "vs_4_0", swFlag, 0, nullptr, &pBlob, &pErrorBlob, nullptr)))
	{
		pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
		pDevice->CreateInputLayout(
			tInputLayout, iElementNum, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pVertexLayout);
	}
	else
	{
		if (pErrorBlob) { FAILED_CHECK_MSG(E_FAIL, L"셰이더 컴파일 실패"); }
		else { FAILED_CHECK_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다."); }
		return E_FAIL;
	}

	pBlob = pErrorBlob = nullptr;
	if (SUCCEEDED(D3DX11CompileFromFile(L"./bin/Resource/Fx/SkyBox.fx", nullptr, nullptr,
		"PS", "ps_4_0", swFlag, 0, nullptr, &pBlob, &pErrorBlob, nullptr)))
	{
		pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	}
	else
	{
		if (pErrorBlob) { FAILED_CHECK_MSG(E_FAIL, L"셰이더 컴파일 실패"); }
		else { FAILED_CHECK_MSG(E_FAIL, L"셰이더 파일이 존재하지 않습니다."); }
		return E_FAIL;
	}
	::Safe_Release(pBlob);
	::Safe_Release(pErrorBlob);

	return S_OK;
}


void CShaderSkyBox::Update()
{

}

void CShaderSkyBox::Release()
{

}