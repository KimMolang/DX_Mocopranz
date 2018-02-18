#include "stdafx.h"
#include "Shader.h"

#include "GraphicDevice.h"
#include "Export_Function_Mgr_GraphicDevice.h"

BEGIN(Engine)


Shader::Shader()
	: m_pVertexShader(nullptr)
	, m_pVertexLayout(nullptr)

	, m_pPixelShader(nullptr)
{

}

Shader::~Shader()
{
	Release();
}

void Shader::Render()
{
	ID3D11DeviceContext* pDeviceContext = GetGraphicDevice()->GetDeviceContext();

	if (m_pVertexLayout)
		pDeviceContext->IASetInputLayout(m_pVertexLayout);
	if (m_pVertexShader)
		pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	if (m_pPixelShader)
		pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}

void Shader::Release()
{
	if ((*m_pRefCnt) == 0)
	{
		::Safe_Release(m_pVertexShader);
		::Safe_Release(m_pVertexLayout);
		::Safe_Release(m_pPixelShader);
		Resource::Release_RefCnt();
	}
	else --(*m_pRefCnt);
}


END