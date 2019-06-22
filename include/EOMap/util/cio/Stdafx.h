// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string.h>
#include<fstream>
#include <iostream>     // 
// BOOST libs 
#include <boost\smart_ptr.hpp>
#include <boost\ptr_container\ptr_container.hpp>
#include <boost\lexical_cast\lexical_cast_old.hpp>

// TODO: reference additional headers your program requires here
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <comdef.h>

// global declarations
_COM_SMARTPTR_TYPEDEF(IDirect3D9, __uuidof(IDirect3D9));
// Declare Smart Pointers for IFoo, IBar, and IGak interfaces
_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9, __uuidof(IDirect3DDevice9));