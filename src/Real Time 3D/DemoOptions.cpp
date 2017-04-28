
#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoOptions.h"
#include "Demo.h"

DemoOptions::DemoOptions()
{
    m_pTexture.setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
    m_pTexture.getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));;
    m_pTexture.setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));
    m_pTexture.Prepare();

    m_pHeader.setText("Demo Options");
    m_pHeader.setFont("data/img/MavenPro-Regular.ttf");
    m_pHeader.setPosition(vec2(400, 550));
    m_pHeader.setSize(100);

    m_pShowCollisionBoxes.SetPosition("Show Collision Boxes?", vec2(450, 400), vec2(400, 100));
    m_pShowCollisionBoxes.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pEnablePostEffects.SetPosition("Enable Post FX Effects", vec2(450, 250), vec2(400, 100));
    m_pEnablePostEffects.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pEnableWireframe.SetPosition("Enable Wireframe", vec2(450, 100), vec2(400, 100));
    m_pEnableWireframe.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pBackButton.SetPosition("Back", vec2(10, 625), vec2(200, 50));
    m_pBackButton.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
}

DemoOptions::~DemoOptions()
{
}

void DemoOptions::mousePress(int Key, int State, int x, int y)
{
    if (m_pEnableWireframe.MouseState(Key, State, x, y))
    {
        if (Demo::demoSettings.enableFx)
        {
            activateButton(&m_pEnablePostEffects);
        }

        Demo::demoSettings.wireframeEnabled = !Demo::demoSettings.wireframeEnabled;
        Demo::demoSettings.enableFx = false;
        activateButton(&m_pEnableWireframe);
    }

    if (m_pShowCollisionBoxes.MouseState(Key, State, x, y))
    {
        Demo::demoSettings.showBoundingBoxes = !Demo::demoSettings.showBoundingBoxes;
        activateButton(&m_pShowCollisionBoxes);
    }

    if (m_pEnablePostEffects.MouseState(Key, State, x, y))
    {
        Demo::demoSettings.enableFx = !Demo::demoSettings.enableFx;
        activateButton(&m_pEnablePostEffects);
    }

    if (m_pBackButton.MouseState(Key, State, x, y))
        SceneManager::get()->SwitchTo(1);
}

void DemoOptions::activateButton(Button * button)
{
    auto t = button->getTexture();
    auto v = t->getShade();

    if (v == vec4(0.0, 1.0, 0.0, 1.0))
    {
        v = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        v = vec4(0.0, 1.0, 0.0, 1.0);
    }

    t->setShade(v);
}

void DemoOptions::update()
{
    m_pTexture.update();
    m_pHeader.update();
}

void DemoOptions::render()
{
    m_pRenderer.Render2D(GL_FALSE);

    glDisable(GL_DEPTH_TEST);

    m_pRenderer.RenderTexture(&m_pTexture);

    m_pShowCollisionBoxes.render(&m_pRenderer);
    m_pEnablePostEffects.render(&m_pRenderer);
    m_pEnableWireframe.render(&m_pRenderer);
    m_pBackButton.render(&m_pRenderer);
    m_pHeader.render();

    glEnable(GL_DEPTH_TEST);
    m_pRenderer.Render2D(Demo::demoSettings.wireframeEnabled);
}