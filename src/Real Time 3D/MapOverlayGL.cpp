
#include "MapOverlayGL.h"

MapOverlayGL::MapOverlayGL() :
    sprite(nullptr),
    map(nullptr)
{
}

MapOverlayGL::~MapOverlayGL()
{
}

GLvoid MapOverlayGL::setOverlayImage(const std::string& filename)
{
    sprite = TextureManagerGL::get()->createTexture(filename, GL_REPEAT);
}

GLvoid MapOverlayGL::setOverlayMap(const std::string& filename)
{
    map = TextureManagerGL::get()->createTexture(filename, GL_CLAMP_TO_EDGE);
}

GLvoid MapOverlayGL::prepareShader(ProgramGL * program)
{
    GLint overlay = glGetUniformLocation(program->getProgramID(), "Overlay");
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, map->textureID);
    glUniform1i(overlay, 1);

    GLint texture = glGetUniformLocation(program->getProgramID(), "Texture");
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, sprite->textureID);
    glUniform1i(texture, 2);
}

GLuint MapOverlayGL::getTextureID()
{
    return sprite->textureID;
}