#pragma once

#include "Shader.h"

BEGIN(Engine)


class ENGINE_DLL ShaderColor : public Shader
{
public:
	explicit ShaderColor();
	virtual ~ShaderColor();

public:
	virtual HRESULT			Init();
};


END

