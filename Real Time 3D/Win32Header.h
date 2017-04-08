
#pragma once

#define SAFE_RELEASE(ptr) if(ptr) delete ptr; ptr = 0;
#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <dinput.h>	
#include <iostream>														
#include <stdarg.h>		
#include <gl\glew.h>
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

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "glu32.lib")	
#pragma comment(lib, "strmiids")


using std::vector;