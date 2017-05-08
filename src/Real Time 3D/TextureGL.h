
#pragma once

#include "TextureManagerGL.h"
#include "ShaderManagerGL.h"
#include "MinimapGL.h"

class TextureGL
{
    ProgramGL* shader;
    SpriteGL* texture;
    MatrixGL matrix;

    GLuint vertexArray;
    GLuint vertexBuffer;
    GLenum settings;

    vec3 position;
    vec4 shade;
    vec3 size;
    vec4 uv;

    std::string filename;
public:
    TextureGL();
    ~TextureGL();

    const std::string& getPath();

    GLvoid setShade(vec4);
    GLvoid setTexturePositions(vec2, vec2);
    GLvoid setTexture(std::string, GLenum);
    GLvoid setPosition(vec3, vec3);
    GLvoid surfacePlacements(GLuint);
    GLvoid onUpdate() {}
    GLvoid prepare();

    GLuint getVAO();
    GLuint getProgramID();

    MatrixGL* getMatrix();
    ProgramGL* getProgram();

    vec4 getShade();
};
