/*!
 * \file Texture.h
 * \date 2016/02/08 18:56
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

#ifndef Texture_h__
#define Texture_h__

#include "Resource.h"


class CTexture : public CResource
{
public :
	enum TextureType { TEXTURE_TYPE_BASIC, TEXTURE_TYPE_DDS };

private :
	ID3D11ShaderResourceView*	m_pTextures;
	ID3D11SamplerState*			m_pSamplerStates;


public:
	static CResource*		Create(CDevice* _pDevice,
									wstring _wtrPath,
									const TextureType& _eTextureType);
	virtual CResource*		Clone();

private:
	HRESULT		Load(wstring _wtrPath, const TextureType& _eTextureType);
	void		Load_Basic(wstring _wstrPath);
	void		Load_DDS(wstring _wstrPath);

public :
	virtual void			Update();
	void					Render();
private:
	virtual void			Release();


protected:
	CTexture(CDevice*);
public:
	virtual ~CTexture();
};

#endif // Texture_h__
