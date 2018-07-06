#pragma once

#include "Shader.h"

BEGIN(Engine)


class ENGINE_DLL ShaderColor : public Shader
{
public:
	static ShaderColor* Create();
	CLONE(ShaderColor);
private:
	explicit ShaderColor();
public:
	virtual ~ShaderColor();

public:
	virtual HRESULT			Init();
};


END

