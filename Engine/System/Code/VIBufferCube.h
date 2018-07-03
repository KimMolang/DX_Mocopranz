#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


class ENGINE_DLL VIBufferCube : public VIBuffer
{
public:
	static VIBufferCube* Create();
private:
	explicit VIBufferCube();
public:
	virtual ~VIBufferCube();


public:
	virtual HRESULT			Init();
	virtual void			Update();
	virtual void			Render();


private:
	void			Init_Vtx();
	void			Init_Idx();

	virtual void	CreateRasterizerState();
};


END
