
#pragma once

#include "SceneManager.h"
#include "Win32Timer.h"
#include "RendererGL.h"
#include "TextureGL.h"
#include "TextGL.h"

class DemoMenu : public Scene
{
    RendererGL renderer;
    TextureGL* image;
    TextGL footer;
    TextGL header;

    Win32Timer timer;
    float alpha;
public:
    DemoMenu();
    ~DemoMenu();

    void onUpdate();
    void render();
    void enter();
};