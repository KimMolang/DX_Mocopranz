/*!
 * \file Font.h
 * \date 2016/03/28 20:23
 *
 * \author ±è¸íÁö
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef Font_h__
#define Font_h__

#include "Resource.h"
#include "FW1FontWrapper.h"

class CFont : public CResource
{
public :
	enum FontType
	{
		FONT_TYPE_BASIC,
		FONT_TYPE_OUTLINE,
	};

private :
	IFW1FontWrapper*		m_pFW1FontWarpper;
	IFW1Factory*			m_pFW1FontFactory;
	//IDWriteFactory*			m_pWriteFactory;

	ID3D11DeviceContext*	m_pDeivceContext;

	


public :
	FontType		m_eType;

	wstring			m_wstrText;
	float			m_fSize;
	UINT32			m_nColor;
	UINT			m_nFlag;

	D3DXVECTOR2		m_vPos;

	float			m_fOutlineSize;
	UINT32			m_nOutlineColor;


public :
	static CResource*		Create(CDevice*, const wstring& _wstPath);
	virtual CResource*		Clone();

private:
	HRESULT			Load_Font(const wstring& _wstPath);

public:
	HRESULT			Init(const wstring& _wstPath);
	virtual void	Update();
	void			Render();
	virtual void	Release();


protected:
	explicit CFont(CDevice*);
public:
	virtual ~CFont();
};

#endif // Font_h__
