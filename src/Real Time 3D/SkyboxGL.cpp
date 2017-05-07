
#include "SkyboxGL.h"

SkyboxGL::SkyboxGL()
{
    distance = 1000.0f;
    overdraw = 0.0f;

    for (int i = 0; i < 5; i++)
    {
        skyboxTextures.push_back(new TextureGL());
    }
}

SkyboxGL::~SkyboxGL()
{
    for (auto& texture : skyboxTextures)
    {
        delete texture;
    }
}

GLvoid SkyboxGL::folder(std::string filename)
{
    filenames.push_back(filename + "right.jpg");
    filenames.push_back(filename + "front.jpg");
    filenames.push_back(filename + "back.jpg");
    filenames.push_back(filename + "left.jpg");
    filenames.push_back(filename + "top.jpg");
}

void SkyboxGL::onUpdate()
{
    GLfloat position = (GLfloat)(distance / 2.0f);

    auto right = skyboxTextures[RIGHT]->getMatrix();
    auto left = skyboxTextures[LEFT]->getMatrix();

    right->translate(vec3(position, 0, 0));
    right->rotate(-1.57079633f, vec3(0.0, 1.0, 0.0));

    left->translate(vec3(-position, 0, 0));
    left->rotate(1.57079633f, vec3(0.0, 1.0, 0.0));
}

GLvoid SkyboxGL::translate(vec3 vector)
{
    for (GLint i = 0; i < 5; i++)
    {
        skyboxTextures[i]->getMatrix()->translateView(-vector);
    }
}

void SkyboxGL::setup()
{
    vec3 positions[5];
    vec3 size[5];

    GLfloat position = (GLfloat)(distance / 2.0f);

    positions[RIGHT] = vec3(-position, -position, 00000.0f);
    positions[FRONT] = vec3(-position, -position, position);
    positions[BACK] = vec3(-position, -position, -position);
    positions[LEFT] = vec3(-position, -position, 00000.0f);
    positions[TOP] = vec3(-position, position, -position);

    size[RIGHT] = vec3(distance, distance, 0000000.0f);
    size[FRONT] = vec3(distance, distance, 0000000.0f);
    size[BACK] = vec3(distance, distance, 0000000.0f);
    size[LEFT] = vec3(distance, distance, 0000000.0f);
    size[TOP] = vec3(distance, 0.0000000f, distance);

    skyboxTextures[FRONT]->setTexturePositions(vec2(1.0, 0.0), vec2(0.0, 1.0));

    for (GLint i = 0; i < 5; i++)
    {
        skyboxTextures[i]->setPosition(positions[i], size[i]);
        skyboxTextures[i]->setTexture(filenames[i], GL_CLAMP_TO_EDGE);
    }
}

vector<TextureGL *>& SkyboxGL::getTextures()
{
    return skyboxTextures;
}

GLvoid SkyboxGL::setDistance(GLfloat distance)
{
    this->distance = distance;
}

GLvoid SkyboxGL::setOverdraw(GLfloat overdraw)
{
    this->overdraw = overdraw;
}