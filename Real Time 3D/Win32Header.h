
/* -------------------------------------------------
  
 @Filename  : Win32Header.h
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: Simple include file for all win32 files

 ------------------------------------------------- */

#pragma once

// Define the DirectInput version we want to use
#define DIRECTINPUT_VERSION 0x0800

// Include headers
#include <Windows.h>
#include <dinput.h>	
#include <iostream>														
#include <stdarg.h>		
#include "lib\glew\glew.h"
#include <gl\GLU.h>	
#include <dshow.h>
#include <Mfidl.h>
#include <fcntl.h>	
#include <gl\gl.h>
#include <Psapi.h>
#include <string>													
#include <vector>
#include <time.h>
#include <Evr.h>
#include <io.h>
#include <list>

// link librarys
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "lib/glew/glew32.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "glu32.lib")	
#pragma comment(lib, "strmiids")

using std::vector;

// some useful macros
#define SAFE_RELEASE(ptr) if(ptr) delete ptr; ptr = 0;
#define RELEASE_MANAGER(ptr) if(ptr) delete ptr;

// END