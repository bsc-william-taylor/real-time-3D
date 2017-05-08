
#pragma once

#include "TextureManagerGL.h"
#include "TextureGL.h"

class TextGL
{
    struct Character
    {
        SpriteGL* sprite;
        GLuint vertexBuffer;
    };

    FT_Library freeTypeLibrary;
    FT_Face freeTypeFace;

    std::string fontname;
    std::string text;

    ProgramGL* shader;
    MatrixGL matrix;
    GLboolean loaded;
    GLuint fontSize;

    vector<Character*> characters;
    vec2 position;
public:
    TextGL();
    ~TextGL();

    GLvoid render();
    GLvoid prepare();
    GLvoid onUpdate();
    GLvoid setPosition(vec2);
    GLvoid setFont(std::string);
    GLvoid setText(std::string);
    GLvoid setSize(GLuint);

    GLuint getHeight();
    GLuint getWidth();

    ProgramGL * getProgram();
    MatrixGL * getMatrix();
};