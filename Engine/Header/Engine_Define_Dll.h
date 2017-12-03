#pragma once

#define BEGIN(NAMESPACE) namespace NAMESPACE {
#define END }


#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport) 
#else
#define ENGINE_DLL _declspec(dllimport) 
#endif