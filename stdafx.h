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
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>
#include <array>
#include <stdexcept>
#include <list>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <io.h>
#include <math.h>
#include <set>
#include <map>
#include <comdef.h>
#include <ctype.h>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <sys\utime.h>

#include <GdiPlus.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Utilities/UI_Element.h"
#include "Utilities/Button.h"
#include "Utilities/ConfigFile.h"
	
#include "Utilities/Textbox.h"
#include "Utilities/TextTools.h"
//#include "Utilities/UI_InformationBox.h"
#include "Utilities/UI_ScrollBar.h"

#include <Ptypes/pinet.h>
#include <Ptypes/ptypes.h>
#include <Ptypes/pstreams.h>
#include <Ptypes/ptime.h>
#include <Ptypes/pasync.h>
#include <Ptypes/pport.h>

#include <CBitmapEx/BitmapEx.h>

#include <EOMap/eo_data.hpp>
#include <EOMap/util/cio/cio.hpp>
#include <EOMap/eo_data.hpp>
#include <EOMap/eo_stream.hpp>

#include <EOServ/eodata.hpp>
#include <EOServ/packet.hpp>

#include "Utilities/Resource_Manager.h"
// global declarations
_COM_SMARTPTR_TYPEDEF(IDirect3D9, __uuidof(IDirect3D9));
// Declare Smart Pointers for IFoo, IBar, and IGak interfaces
_COM_SMARTPTR_TYPEDEF(IDirect3DDevice9, __uuidof(IDirect3DDevice9));