#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


class Shader;
class VIBufferCube : public VIBuffer
{
public:
	explicit VIBufferCube();
	virtual ~VIBufferCube();


public:
	virtual HRESULT			Init();
	virtual void			Update();
	virtual void			Render();
private:
	virtual void			Release();


private:
	void			Init_Vtx();
	void			Init_Idx();
	void			Init_ColorShader();

	virtual void	CreateRasterizerState();


private:
	Shader*			m_pShader;
};


END
