#pragma once

#include "Timer.h"
#include "KeyChecker.h"

#include "ResourceMgr.h"
#include "ObjectMgr.h"
#include "SceneMgr.h"

BEGIN(Engine)


inline Timer* GetTimer(void)
{
	return Timer::GetInstance();
}

inline KeyChecker* GetKeyChecker(void)
{
	return KeyChecker::GetInstance();
}


inline ResourceMgr* GetResourceMgr(void)
{
	return ResourceMgr::GetInstance();
}

inline ObjectMgr* GetObjectMgr(void)
{
	return ObjectMgr::GetInstance();
}

inline SceneMgr* GetSceneMgr(void)
{
	return SceneMgr::GetInstance();
}


END
