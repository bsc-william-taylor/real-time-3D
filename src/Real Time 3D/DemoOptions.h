
#pragma once

#include "SceneManager.h"
#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "Button.h"

class DemoOptions : public Scene
{
    GL_Renderer renderer;
    GL_Texture texture;
    GL_Text header;

    Button showCollisionBoxes;
    Button enablePostEffects;
    Button enableWireframe;
    Button backButton;
public:
    DemoOptions();
    ~DemoOptions();

    void mousePress(int, int, int, int);
    void activateButton(Button*);
    void update();
    void render();
};