
#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoOptions.h"
#include "Demo.h"

DemoOptions::DemoOptions()
    : m_pShowCollisionBoxes(new Button()),
    m_pEnablePostEffects(new Button()),
    m_pEnableWireframe(new Button()),
    m_pBackButton(new Button()),
    m_pRenderer(new GL_Renderer()),
    m_pTexture(new GL_Texture()),
    m_pHeader(new GL_Text())
{
    m_pTexture->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
    m_pTexture->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));;
    m_pTexture->setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));
    m_pTexture->Prepare();

    m_pHeader->setText("Demo Options");
    m_pHeader->setFont("data/img/MavenPro-Regular.ttf");
    m_pHeader->setPosition(vec2(400, 550));
    m_pHeader->setSize(100);

    m_pShowCollisionBoxes->SetPosition("Show Collision Boxes?", vec2(450, 400), vec2(400, 100));
    m_pShowCollisionBoxes->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pEnablePostEffects->SetPosition("Enable Post FX Effects", vec2(450, 250), vec2(400, 100));
    m_pEnablePostEffects->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pEnableWireframe->SetPosition("Enable Wireframe", vec2(450, 100), vec2(400, 100));
    m_pEnableWireframe->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
    m_pBackButton->SetPosition("Back", vec2(10, 625), vec2(200, 50));
    m_pBackButton->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
}

DemoOptions::~DemoOptions()
{
    SAFE_RELEASE(m_pShowCollisionBoxes);
    SAFE_RELEASE(m_pEnablePostEffects);
    SAFE_RELEASE(m_pEnableWireframe);
    SAFE_RELEASE(m_pBackButton);

    SAFE_RELEASE(m_pRenderer);
    SAFE_RELEASE(m_pTexture);
    SAFE_RELEASE(m_pHeader);
}

void DemoOptions::MousePress(int Key, int State, int x, int y)
{
    if (m_pEnableWireframe->MouseState(Key, State, x, y))
    {
        if (Demo::demoSettings.enableFx)
        {
            ActivateButton(m_pEnablePostEffects);
        }

        Demo::demoSettings.wireframeEnabled = !Demo::demoSettings.wireframeEnabled;
        Demo::demoSettings.enableFx = false;
        ActivateButton(m_pEnableWireframe);
    }

    if (m_pShowCollisionBoxes->MouseState(Key, State, x, y))
    {
        Demo::demoSettings.showBoundingBoxes = !Demo::demoSettings.showBoundingBoxes;
        ActivateButton(m_pShowCollisionBoxes);
    }

    if (m_pEnablePostEffects->MouseState(Key, State, x, y))
    {
        Demo::demoSettings.enableFx = !Demo::demoSettings.enableFx;
        ActivateButton(m_pEnablePostEffects);
    }

    if (m_pBackButton->MouseState(Key, State, x, y))
        SceneManager::get()->SwitchTo(1);
}

void DemoOptions::ActivateButton(Button * button)
{
    auto t = button->getTexture();
    vec4 v = t->getShade();

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

void DemoOptions::Update()
{
    m_pTexture->Update();
    m_pHeader->Update();
}

void DemoOptions::Render()
{
    m_pRenderer->Render2D(GL_FALSE);

    glDisable(GL_DEPTH_TEST);

    m_pRenderer->RenderTexture(m_pTexture);

    m_pShowCollisionBoxes->Render(m_pRenderer);
    m_pEnablePostEffects->Render(m_pRenderer);
    m_pEnableWireframe->Render(m_pRenderer);
    m_pBackButton->Render(m_pRenderer);
    m_pHeader->Render();

    glEnable(GL_DEPTH_TEST);
    m_pRenderer->Render2D(Demo::demoSettings.wireframeEnabled);
}