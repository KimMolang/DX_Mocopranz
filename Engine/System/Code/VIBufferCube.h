#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


class ENGINE_DLL VIBufferCube : public VIBuffer
{
public:
	explicit VIBufferCube();
	virtual ~VIBufferCube();


public:
	virtual HRESULT			Init();
	virtual void			Update();
	virtual void			Render();


private:
	void			Init_Vtx();
	void			Init_Idx();
	//void			Init_ColorShader();

	virtual void	CreateRasterizerState();
};


END
