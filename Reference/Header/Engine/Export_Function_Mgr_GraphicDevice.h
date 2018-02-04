#pragma once

BEGIN(Engine)
#include "GraphicDevice.h"


inline GraphicDevice* GetGraphicDevice(void)
{
	return GraphicDevice::GetInstance();
}


END
