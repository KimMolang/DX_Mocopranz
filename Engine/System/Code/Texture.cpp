#include "stdafx.h"
#include "Texture.h"

#include "Engine_Define_Buffer_Index.h"

#include "GraphicDevice.h"

BEGIN(Engine)


Texture * Texture::Create(std::wstring _wstrPath, const ETextureType & _eTextureType)
{
	Texture* pComponent = new Texture();
	if (FAILED(pComponent->Load(_wstrPath, _eTextureType)))
		::Safe_Delete(pComponent);

	return pComponent;
}

Texture::Texture()
{

}

Texture::~Texture()
{
	
}

HRESULT Texture::Load(std::wstring _wstrPath, const ETextureType& _eTextureType)
{
	switch (_eTextureType)
	{
	case TEXTURE_TYPE_BASIC:	Load_Basic(_wstrPath);	break;
	case TEXTURE_TYPE_DDS:		Load_DDS(_wstrPath);	break;

	default: return E_FAIL;
	}


	return S_OK;
}

void Texture::Load_Basic(std::wstring _wstrPath)
{
	D3DX11CreateShaderResourceViewFromFile(
		GraphicDevice::GetInstance()->GetDevice(), _wstrPath.c_str(), NULL, NULL, &m_pTextures, NULL);

	ID3D11SamplerState* pSamplerState = NULL;
	D3D11_SAMPLER_DESC tData;

	ZeroMemory(&tData, sizeof(D3D11_SAMPLER_DESC));
	tData.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	tData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tData.ComparisonFunc = D3D11_COMPARISON_NEVER;
	tData.MinLOD = 0;
	tData.MaxLOD = 0;
	GraphicDevice::GetInstance()->GetDevice()->CreateSamplerState(&tData, &m_pSamplerStates);
}

void Texture::Load_DDS(std::wstring _wstrPath)
{
	D3DX11_IMAGE_LOAD_INFO tLoadInfo;
	tLoadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	ID3D11Texture2D* pTexture2D = NULL;

	D3DX11CreateTextureFromFile(
		GraphicDevice::GetInstance()->GetDevice(), _wstrPath.c_str()
		,&tLoadInfo, NULL, (ID3D11Resource**)&pTexture2D, NULL);

	D3D11_TEXTURE2D_DESC tTextureData;
	pTexture2D->GetDesc(&tTextureData);

	D3D11_SHADER_RESOURCE_VIEW_DESC tViewData;
	tViewData.Format = tTextureData.Format;
	tViewData.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	tViewData.TextureCube.MipLevels = tTextureData.MipLevels;
	tViewData.TextureCube.MostDetailedMip = 0;

	GraphicDevice::GetInstance()->GetDevice()->
		CreateShaderResourceView(pTexture2D, &tViewData, &m_pTextures);

	ID3D11SamplerState* pSamplerState = NULL;
	D3D11_SAMPLER_DESC tSamplerData;

	ZeroMemory(&tSamplerData, sizeof(D3D11_SAMPLER_DESC));
	tSamplerData.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	tSamplerData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamplerData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamplerData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tSamplerData.ComparisonFunc = D3D11_COMPARISON_NEVER;
	tSamplerData.MinLOD = 0;
	tSamplerData.MaxLOD = D3D11_FLOAT32_MAX;
	GraphicDevice::GetInstance()->GetDevice()->CreateSamplerState(&tSamplerData, &m_pSamplerStates);
}

void Texture::Update()
{

}

void Texture::Render()
{
	GraphicDevice::GetInstance()->GetDeviceContext()->PSSetShaderResources(PS_SLOT_TEXTURE, 1, &m_pTextures);
	GraphicDevice::GetInstance()->GetDeviceContext()->PSSetSamplers(PS_SLOT_SAMPLER_STATE, 1, &m_pSamplerStates);
}

void Texture::Release()
{
	Resource::Release();

	if (m_pRefCnt == nullptr)
	{
		::Safe_Release(m_pTextures);
		::Safe_Release(m_pSamplerStates);
	}
}


END
