#pragma once

#include "Resource.h"

BEGIN(Engine)


class Shader abstract : public Resource
{
protected:
	explicit Shader();
public:
	virtual ~Shader()	PURE;


public:
	virtual void	Render();
	void			Update() {};
private:
	void			Release();


protected:
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11InputLayout*		m_pVertexLayout;

	ID3D11PixelShader*		m_pPixelShader;
};


END
