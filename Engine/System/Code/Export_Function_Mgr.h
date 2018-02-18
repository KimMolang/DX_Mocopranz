#pragma once

BEGIN(Engine)
#include "Timer.h"
#include "KeyChecker.h"


inline Timer* GetTimer(void)
{
	return Timer::GetInstance();
}

inline KeyChecker* GetKeyChecker(void)
{
	return KeyChecker::GetInstance();
}



END
