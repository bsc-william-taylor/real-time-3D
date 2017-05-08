
#include "Button.h"
#include "Win32Codes.h"

Button::Button()
{
    sprite.getMatrix()->ortho(vec2(0, 1280), vec2(0, 720));
    string.getMatrix()->ortho(vec2(0, 1280), vec2(0, 720));
}

Button::~Button()
{
}

void Button::setPosition(std::string str, vec2 pos, vec2 sz)
{
    position = pos;
    size = sz;

    sprite.setTexture("data/img/button.png", GL_CLAMP_TO_EDGE);
    sprite.setPosition(vec3(pos, 0.0), vec3(sz, 0.0));
    sprite.prepare();

    string.setFont("data/img/MavenPro-Regular.ttf");
    string.setPosition(pos);
    string.setText(str.c_str());
    string.setSize(25);
    string.prepare();

    GLuint height = (int)size.y - string.getHeight();
    GLuint width = (int)size.x - string.getWidth();

    string.getMatrix()->translate(vec3(width / 2, height / 2, 0.0));
}

bool Button::mouseState(int key, int state, int x, int y)
{
    if (x >= position.x && x <= position.x + size.x
        && y >= position.y && y <= position.y + size.y)
    {
        if (key == MOUSE_1 && state == RELEASED)
        {
            return true;
        }
    }

    return false;
}

void Button::render(RendererGL * renderer)
{
    renderer->renderTexture(&sprite);
    string.render();
}

TextureGL* Button::getTexture()
{
    return &sprite;
}

TextGL* Button::getString()
{
    return &string;
}