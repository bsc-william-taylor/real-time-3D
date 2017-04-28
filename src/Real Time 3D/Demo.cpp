

#include "GL_Texture_Manager.h"
#include "GL_Shader_Manager.h"
#include "DemoOptions.h"
#include "Win32Codes.h"
#include "SceneManager.h"
#include "DemoMenu.h"
#include "DemoScene.h"
#include "Demo.h"
#include "Memory.h"

Demo::DemoSettings Demo::demoSettings;

Demo::Demo()
    : fps(60)
{
    sceneManager = SceneManager::get();
    sceneManager->PassEngine(this);

    demoSettings.wireframeEnabled = false;
    demoSettings.showBoundingBoxes = false;
    demoSettings.enableFx = false;
}

Demo::~Demo()
{
    delete GL_TextureManager::get();
    delete GL_Shader_Manager::get();
    delete SceneManager::get();

    SAFE_RELEASE(timer);
    SAFE_RELEASE(win32System);
}

void Demo::execute()
{
    setupScenes();
    setupOpenGL();

    while (win32System->WindowRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        win32System->update();
        timeLeft = 0;

        sceneManager->UpdateManager();
        win32System->SwapWindowBuffers();

        while (timeLeft < (GLfloat)1.0e9 / fps)
        {
            timer->Stop();
            timeLeft = timer->Difference(TimeType::NS);
        }

        timer->Start();
    }
}

void Demo::hideConsole()
{
    if (FreeConsole() != NULL)
    {
        return;
    }

    std::cerr << "Cant hide the console" << std::endl;
}

void Demo::setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Demo::setupScenes()
{
    sceneManager = SceneManager::get();
    sceneManager->PushState(new DemoMenu());
    sceneManager->PushState(new DemoScene());
    sceneManager->PushState(new DemoOptions());
    sceneManager->StartFrom(0);
    sceneManager->getCurrent()->enter();

    timer = new Win32Timer();
    timer->Start();
}

void Demo::setWindowSize(int x, int y, int w, int h)
{
    Win32Window::Sizes sizes;
    sizes.w = w;
    sizes.h = h;
    sizes.x = x;
    sizes.y = y;

    win32System = new Win32System();
    win32System->setWindowTraits("Real Time 3D", sizes);
    win32System->setWindowType(Win32Window::Type::WINDOWED);
    win32System->Initialise();
    win32System->Show();
}

void Demo::setRedrawRate(int FPS)
{
    fps = FPS;
}