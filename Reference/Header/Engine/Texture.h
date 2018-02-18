#pragma once

#include "Resource.h"

BEGIN(Engine)


class Texture : public Resource
{
public :
	enum ETextureType { TEXTURE_TYPE_BASIC, TEXTURE_TYPE_DDS };

protected:
	Texture();
public:
	virtual ~Texture();


private:
	HRESULT		Load(std::wstring _wstrPath, const ETextureType& _eTextureType);
	void		Load_Basic(std::wstring _wstrPath);
	void		Load_DDS(std::wstring _wstrPath);

public:
	virtual void			Update();
	void					Render();
private:
	virtual void			Release();


private:
	ID3D11ShaderResourceView*	m_pTextures;
	ID3D11SamplerState*			m_pSamplerStates;
};


END