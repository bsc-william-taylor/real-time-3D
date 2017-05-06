
#pragma once

#include "SceneManager.h"
#include "RendererGL.h"
#include "TextureGL.h"
#include "Button.h"

class DemoOptions : public Scene
{
    RendererGL renderer;
    TextureGL texture;
    TextGL header;

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