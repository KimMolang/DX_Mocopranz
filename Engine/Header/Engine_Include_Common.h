#pragma once

// STL -----------------------------
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>

// D3DX -----------------------------
#include <D3D11.h>
#include <D3DX11.h>

#include <D3DX10.h>
#include <D3D10.h>

#include <d3dcompiler.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


#pragma  comment(lib, "d3dx11.lib")
#pragma  comment(lib, "d3d11.lib")

#pragma  comment(lib, "d3dx10.lib")
#pragma  comment(lib, "d3d10.lib")

#pragma  comment(lib, "D3DCompiler.lib")
#pragma  comment(lib, "dxerr.lib")
#pragma  comment(lib, "dxgi.lib")

#pragma  comment(lib, "dinput8.lib")
#pragma  comment(lib, "dxguid.lib")

#pragma  comment(lib, "d2d1.lib")
#pragma  comment(lib, "dwrite.lib")

//#pragma  comment(lib, "Effects11d.lib")

#ifdef _DEBUG
#pragma  comment(lib, "d3dx11d.lib")
#else
#pragma  comment(lib, "d3dx11.lib")
#endif

// Header
#include "Engine_Define_Check.h"
#include "Engine_Define_Dll.h"

#include "Engine_Function_Safe.h"

#include "Engine_Value_Common.h"