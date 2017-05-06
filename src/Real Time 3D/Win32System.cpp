
#include "Win32System.h"

Win32System::Win32System() :
    type(WindowType::Windowed), quit(FALSE)
{
}

Win32System::~Win32System()
{
}

bool Win32System::windowRunning()
{
    return(window.onUpdate());
}

void Win32System::initialise()
{
    window.initialise();
    window.display(type);
    window.enableOpenGL();

    auto handle = window.GetHandle();
    driver.initialise(&handle);
    auto error = glewInit();

    if (error != GLEW_OK)
    {
        printf("Error: %s\n", glewGetErrorString(error));
        system("pause");
    }
}

void Win32System::swapWindowBuffers()
{
    SwapBuffers(GetDC(window.GetHandle()));
}

void Win32System::onUpdate()
{
    window.onUpdate();
    driver.onUpdate();
}

void Win32System::setWindowType(WindowType type)
{
    this->type = type;
}

void Win32System::setWindowTraits(CHAR * c, Region s)
{
    window.setTraits(c, s.x, s.y, s.w, s.h);
}

Win32Window* Win32System::getWindow()
{
    return &window;
}