
#pragma once

#include "SceneManager.h"
#include "Win32System.h"
#include "Win32Timer.h"

class Demo
{
    SceneManager* sceneManager;
    Win32System system;
    Win32Timer timer;
    float timeLeft;
    int fps;
public:
    Demo();
    ~Demo();

    void setWindowSize(int, int, int, int);
    void setRedrawRate(int);
    void hideConsole();
    void setupScenes();
    void setupOpenGL();
    void execute();

    struct DemoSettings
    {
        bool wireframeEnabled;
        bool showBoundingBoxes;
        bool enableFx;
    };

    static DemoSettings demoSettings;
};