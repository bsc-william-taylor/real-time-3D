
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
    Demo demo;
    demo.setWindowSize(0, 0, 1280, 720);
    demo.setRedrawRate(60);
    demo.execute();
    return 0;
}

#else

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR l, int cc)
{
    Demo demo;
    demo.WindowSize(0, 0, 1280, 720);
    demo.RedrawRate(60);
    demo.Execute();
    return 0;
}

#endif