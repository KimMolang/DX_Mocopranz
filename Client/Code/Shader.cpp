#include "stdafx.h"
#include "Shader.h"

CShader::CShader(CDevice* _pDevice)
: CResource(_pDevice)
, m_pVertexShader(nullptr)
, m_pVertexLayout(nullptr)

, m_pPixelShader(nullptr)
{

}

CShader::~CShader()
{
	Release();
}

void CShader::Render()
{
	ID3D11DeviceContext* pDeviceContext = m_pDevice->GetDeviceContext();

	if (m_pVertexLayout)
		pDeviceContext->IASetInputLayout(m_pVertexLayout);
	if (m_pVertexShader)
		pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	if (m_pPixelShader)
		pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
}

void CShader::Release()
{
	if ((*m_pRefCnt) == 0)
	{
		::Safe_Release(m_pVertexShader);
		::Safe_Release(m_pVertexLayout);
		::Safe_Release(m_pPixelShader);
		CResource::Release_RefCnt();
	}
	else --(*m_pRefCnt);
}
