#pragma once

#include "Shader.h"

BEGIN(Engine)


class ENGINE_DLL ShaderNull : public Shader
{
public:
	static ShaderNull* Create();
	CLONE(ShaderNull);
private:
	explicit ShaderNull();
public:
	virtual ~ShaderNull();
};


END

