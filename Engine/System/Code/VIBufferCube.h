#pragma once

#include "VIBuffer.h"

BEGIN(Engine)


class ENGINE_DLL VIBufferCube : public VIBuffer
{
public:
	static VIBufferCube* Create();
	CLONE(VIBufferCube);
private:
	explicit VIBufferCube();
public:
	virtual ~VIBufferCube();


public:
	virtual HRESULT			Init();
	virtual void			Update();


private:
	void			Init_Vtx();
	void			Init_Idx();
};


END
