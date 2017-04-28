
#pragma once

#include "SceneManager.h"
#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "Button.h"

class DemoOptions : public Scene
{
    GL_Renderer* m_pRenderer;
    GL_Texture* m_pTexture;
    GL_Text* m_pHeader;
    Button* m_pShowCollisionBoxes;
    Button* m_pEnablePostEffects;
    Button* m_pEnableWireframe;
    Button* m_pBackButton;
public:
    DemoOptions();
    ~DemoOptions();

    void MousePress(int, int, int, int);
    void ActivateButton(Button*);
    void Update();
    void Render();
};