#pragma once

#include "Resource.h"
#include "GraphicDevice.h"

BEGIN(Engine)


class ENGINE_DLL Shader abstract : public Resource
{
protected:
	explicit Shader();
public:
	virtual ~Shader()	PURE;


public:
	virtual void	Render();
	virtual void	Update() {};
private:
	void			Release();

protected:
	void OutputShaderErrorMessage(ID3D10Blob* _pErrorBlob, char* _fileName);


protected:
	ID3D11VertexShader*		m_pVertexShader;
	ID3D11InputLayout*		m_pVertexLayout;

	ID3D11PixelShader*		m_pPixelShader;
};


END
