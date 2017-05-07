
#pragma once

#include "MajorInclude.h"

struct SpriteGL
{
    vector<vector<RGBQUAD>> colours;
    std::string name;
    GLuint textureID;
    GLuint height;
    GLuint width;
};

class TextureManagerGL
{
    static TextureManagerGL* manager;
    vector<SpriteGL*> textures;
public:
    TextureManagerGL();
    ~TextureManagerGL();

    static TextureManagerGL * get();

    SpriteGL* createTexture(GLubyte *, GLuint, GLuint, GLenum);
    SpriteGL* createTexture(const std::string&, GLenum);
    SpriteGL* createGlyph(FT_Face, GLenum);
    SpriteGL* loadTexture(const std::string&, GLenum e);

    GLuint getTextureCount();
    GLvoid freeTextures();
};