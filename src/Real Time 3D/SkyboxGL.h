
#pragma once

#include "TextureGL.h"

enum SIDES
{
    RIGHT,
    FRONT,
    BACK,
    LEFT,
    TOP,
};

class SkyboxGL
{
    vector<TextureGL *> skyboxTextures;
    vector<std::string> filenames;

    GLfloat overdraw;
    GLfloat distance;
public:

    SkyboxGL();
    ~SkyboxGL();

    GLvoid setOverdraw(GLfloat);
    GLvoid setDistance(GLfloat);
    GLvoid folder(std::string);
    GLvoid translate(vec3);
    GLvoid onUpdate();
    GLvoid setup();

    vector<TextureGL *>& getTextures();
};