

#include "TextureManagerGL.h"
#include "ShaderManagerGL.h"
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
    delete TextureManagerGL::get();
    delete ShaderManagerGL::get();
    delete SceneManager::get();
}

void Demo::execute()
{
    setupScenes();
    setupOpenGL();

    while (system.windowRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        system.onUpdate();
        timeLeft = 0;

        sceneManager->UpdateManager();
        system.swapWindowBuffers();

        while (timeLeft < (GLfloat)1.0e9 / fps)
        {
            timer.stop();
            timeLeft = timer.difference(TimeType::Nanoseconds);
        }

        timer.start();
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
    timer.start();
}

void Demo::setWindowSize(int x, int y, int w, int h)
{
    Region sizes;
    sizes.w = w;
    sizes.h = h;
    sizes.x = x;
    sizes.y = y;

    system.setWindowTraits("Real Time 3D", sizes);
    system.setWindowType(WindowType::Windowed);
    system.initialise();
}

void Demo::setRedrawRate(int FPS)
{
    fps = FPS;
}