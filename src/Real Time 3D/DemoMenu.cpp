
#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoMenu.h"

DemoMenu::DemoMenu()
{
    renderer = new GL_Renderer();
    background = new GL_Texture();
    timer = new Win32Timer();
    footer = new GL_Text();
    header = new GL_Text();

    background->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
    background->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));
    background->setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));

    header->setText("Real Time 3D - B00235610");
    header->setFont("data/img/MavenPro-Regular.ttf");
    header->setPosition(vec2(30, 625));
    header->setSize(75);

    footer->setText("Please be patient while the demo loads...");
    footer->setFont("data/img/MavenPro-Regular.ttf");
    footer->setPosition(vec2(800, 25));
    footer->setSize(25);

    renderer->PushTexture(background);
    renderer->Prepare();
    alpha = 0.0f;
}

DemoMenu::~DemoMenu()
{
    SAFE_RELEASE(renderer);
    SAFE_RELEASE(timer);
    SAFE_RELEASE(header);
    SAFE_RELEASE(footer);
}

void DemoMenu::Update()
{
    background->setShade(vec4(1, 1, 1, alpha));
    timer->Stop();

    renderer->Update();
    header->Update();
    footer->Update();

    alpha += 0.05f;
}

void DemoMenu::Enter()
{
    timer->Start();
}

void DemoMenu::Render()
{

    renderer->Render2D(GL_FALSE);
    renderer->Render();
    header->Render();
    footer->Render();
    renderer->Render3D(GL_FALSE);

    if (timer->Difference(TimeType::MS) > 1000)
    {
        SceneManager::get()->SwitchTo(1);
    }
}