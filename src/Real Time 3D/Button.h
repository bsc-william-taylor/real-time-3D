
#pragma once

#include "RendererGL.h"
#include "TextureGL.h"
#include "TextGL.h"

class Button
{
    TextureGL sprite;
    TextGL string;
    vec2 position;
    vec2 size;
public:
    Button();
    ~Button();

    void setPosition(std::string, vec2, vec2);
    void render(RendererGL *);

    TextureGL* getTexture();
    TextGL* getString();

    bool mouseState(int, int, int, int);
};