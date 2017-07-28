#include "stdafx.h"
#include "Font.h"

#include "Device.h"
#include "ResourceMgr.h"
#include "Texture.h"

#include <D2D1.h>
#include <DWrite.h>


CFont::CFont(CDevice* _pDevice)
: CResource(_pDevice)
, m_pFW1FontWarpper(nullptr)
, m_pFW1FontFactory(nullptr)
//, m_pWriteFactory(nullptr)

, m_pDeivceContext(nullptr)

, m_eType(FONT_TYPE_BASIC)

, m_wstrText(L"")
, m_fSize(0.f)
, m_nColor(0xFFFFFFFF)
, m_nFlag(FW1_LEFT | FW1_TOP | FW1_RESTORESTATE)

, m_vPos(0.f, 0.f)

, m_fOutlineSize(1.f)
, m_nOutlineColor(0xFF000000)
{
	
}

CFont::~CFont()
{
	Release();
}

CResource* CFont::Create(CDevice* _pDevice,
						const wstring& _wstrPath)
{
	CResource* pResource = new CFont(_pDevice);
	if (FAILED(dynamic_cast<CFont*>(pResource)->Init(_wstrPath)))
		::Safe_Delete(pResource);

	return pResource;
}

CResource* CFont::Clone()
{
	++(*m_pRefCnt);
	return new CFont(*this);
}

HRESULT CFont::Init(const wstring& _wstrPath)
{
	m_pDeivceContext = m_pDevice->GetDeviceContext();
	Load_Font(_wstrPath);

	return S_OK;
}

HRESULT CFont::Load_Font(const wstring& _wstrPath)
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &m_pFW1FontFactory)))
	{
		MSG_BOX(L"FAILED CreateFactory");
		return E_FAIL;
	}

	if (FAILED(m_pFW1FontFactory->CreateFontWrapper(
		m_pDevice->GetDevice(), _wstrPath.c_str(), &m_pFW1FontWarpper)))
	{
		MSG_BOX(L"Not Find Font");
		return E_FAIL;
	}

// 	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pWriteFactory);
// 
// 	FW1_FONTWRAPPERCREATEPARAMS tFontData;
// 	ZeroMemory(&tFontData, sizeof(FW1_FONTWRAPPERCREATEPARAMS));
// 	tFontData.DefaultFontParams.FontStyle = DWRITE_FONT_STYLE_OBLIQUE;
// 	tFontData.DefaultFontParams.pszFontFamily = _wstrPath.c_str();

// 	m_pFW1FontFactory->CreateFontWrapper(
// 		m_pDevice->GetDevice(),
// 		m_pWriteFactory,
// 		&tFontData,
// 		&m_pFW1FontWarpper);


	return S_OK;
}

void CFont::Render()
{
	if (!m_pFW1FontWarpper)
		return;

	if (FONT_TYPE_OUTLINE == m_eType)
	{
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x - m_fOutlineSize, m_vPos.y - m_fOutlineSize,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x + m_fOutlineSize, m_vPos.y + m_fOutlineSize,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x + m_fOutlineSize , m_vPos.y - m_fOutlineSize ,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x - m_fOutlineSize , m_vPos.y + m_fOutlineSize ,
			m_nOutlineColor, m_nFlag);

		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x, m_vPos.y - m_fOutlineSize ,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x, m_vPos.y + m_fOutlineSize ,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x + m_fOutlineSize , m_vPos.y,
			m_nOutlineColor, m_nFlag);
		m_pFW1FontWarpper->DrawString(
			m_pDeivceContext,
			m_wstrText.c_str(), m_fSize,
			m_vPos.x - m_fOutlineSize , m_vPos.y,
			m_nOutlineColor, m_nFlag);
	}

	m_pFW1FontWarpper->DrawString(
		m_pDeivceContext,
		m_wstrText.c_str(), m_fSize,
		m_vPos.x, m_vPos.y,
		m_nColor, m_nFlag);
}

void CFont::Update()
{

}

void CFont::Release()
{
	if ((*m_pRefCnt) == 0)
	{
		::Safe_Release(m_pFW1FontWarpper);
		::Safe_Release(m_pFW1FontFactory);
		CResource::Release_RefCnt();
	}
	else --(*m_pRefCnt);
}
