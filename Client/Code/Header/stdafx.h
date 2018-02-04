// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "..\Basic\targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// Library
#pragma  comment(lib, "System.lib")

// TODO: reference additional headers your program requires here
#include "../Header/Value_Common.h"

// Engine -----------------------------
#include "Engine_Include_Common.h"

// Export Function -----------------------------
//#include "Export_Function_System.h"