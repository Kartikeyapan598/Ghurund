// NativeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "core/Object.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "GhurundEngine.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace Ghurund;

extern "C" __declspec(dllexport) void *getArrayItem(void **array, int index) {
    return array[index];
}

extern "C" __declspec(dllexport) void Object_delete(Object *obj) {
    delete obj;
}
