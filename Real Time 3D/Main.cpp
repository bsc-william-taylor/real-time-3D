
/* -------------------------------------------------
  
 @Filename  : Main.cpp
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: The main entry point for the program

 ------------------------------------------------- */

#include "Demo.h"

#define CONSOLE_MAIN

#ifdef CONSOLE_MAIN

int main(int argc, const char * argv) 
{
	Demo * Example = new Demo();

	Example->WindowSize(0, 0, 1280, 720);
	Example->RedrawRate(60);
	Example->Execute();

	delete(Example);
	return NULL;
}

#else

// Entry Point
int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR l, int cc)
{
	Demo * Example = new Demo();

	// Initialise Demo
	Example->WindowSize(0, 0, 1280, 720);
	Example->RedrawRate(60);
	Example->Execute();
	
	// Memory Cleanup
	delete(Example);
	return NULL;
}

#endif