
#include "Demo.h"

#ifdef DEV
    #define MAIN main(int argc, const char * argv)
#else 
    #define MAIN WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR l, int cc)
#endif

int MAIN
{
    Demo demo;
    demo.setWindowSize(0, 0, 1280, 720);
    demo.setRedrawRate(60);
    demo.execute();
    return 0;
}

