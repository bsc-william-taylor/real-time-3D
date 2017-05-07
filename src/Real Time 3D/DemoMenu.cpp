
#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoMenu.h"

DemoMenu::DemoMenu() :
    image(new TextureGL())
{
    image->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
    image->getMatrix()->ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));
    image->setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));

    header.setText("Real Time 3D - B00235610");
    header.setFont("data/img/MavenPro-Regular.ttf");
    header.setPosition(vec2(30, 625));
    header.setSize(75);

    footer.setText("Please be patient while the demo loads...");
    footer.setFont("data/img/MavenPro-Regular.ttf");
    footer.setPosition(vec2(800, 25));
    footer.setSize(25);

    renderer.pushTexture(image);
    renderer.prepare();
    alpha = 0.0f;
}

DemoMenu::~DemoMenu()
{
}

void DemoMenu::onUpdate()
{
    image->setShade(vec4(1, 1, 1, alpha));
    timer.stop();

    renderer.onUpdate();
    header.onUpdate();
    footer.onUpdate();

    alpha += 0.05f;
}

void DemoMenu::enter()
{
    timer.start();
}

void DemoMenu::render()
{
    renderer.render2D(GL_FALSE);
    renderer.render();
    header.render();
    footer.render();

    renderer.render3D(GL_FALSE);

    if (timer.difference(TimeType::Milliseconds) > 1000)
    {
        SceneManager::get()->switchTo(1);
    }
}