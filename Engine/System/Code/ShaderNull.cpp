#include "stdafx.h"
#include "ShaderNull.h"

#include "GraphicDevice.h"

BEGIN(Engine)


ShaderNull * ShaderNull::Create()
{
	ShaderNull* pComponent = new ShaderNull();

	return pComponent;
}

ShaderNull::ShaderNull()
{

}

ShaderNull::~ShaderNull()
{

}


END