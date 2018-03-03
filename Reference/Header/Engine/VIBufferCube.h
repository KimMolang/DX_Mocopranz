#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


//class CColorShader;
class VIBufferCube : public VIBuffer
{
protected:
	explicit VIBufferCube();
public:
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
	//CColorShader * m_pColorShader;
};


END
