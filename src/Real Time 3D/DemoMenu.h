
#pragma once

#include "SceneManager.h"
#include "Win32Timer.h"
#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "GL_Text.h"

class DemoMenu : public Scene
{
    GL_Renderer* renderer;
    GL_Texture* background;
    GL_Text* footer;
    GL_Text* header;

    Win32Timer* timer;
    float alpha;
public:
    DemoMenu();
    ~DemoMenu();

    void Update();
    void Render();
    void Enter();
};