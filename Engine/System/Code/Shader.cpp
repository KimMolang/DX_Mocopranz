#include "stdafx.h"
#include "Shader.h"

#include <fstream>

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
	ID3D11DeviceContext* pDeviceContext = GraphicDevice::GetInstance()->GetDeviceContext();

	if (m_pVertexLayout)
		pDeviceContext->IASetInputLayout(m_pVertexLayout);
	if (m_pVertexShader)
		pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	if (m_pPixelShader)
		pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
}

void Shader::Release()
{
	Resource::Release();

	if (m_pRefCnt == nullptr)
	{
		::Safe_Release(m_pVertexShader);
		::Safe_Release(m_pVertexLayout);
		::Safe_Release(m_pPixelShader);
	}
}

void Shader::OutputShaderErrorMessage(ID3D10Blob* _pErrorBlob, char* _fileName)
{
	// Get a pointer to the error message text buffer.
	char* compileErrors = (char*)(_pErrorBlob->GetBufferPointer());
	SIZE_T bufferSize = _pErrorBlob->GetBufferSize();

	std::ofstream fout;
	fout.open(_fileName);

	// Write out the error message.
	for (int i = 0; i<bufferSize; ++i)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();
}


END