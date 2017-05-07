
#include "TextureManagerGL.h"

TextureManagerGL * TextureManagerGL::manager = nullptr;

TextureManagerGL::TextureManagerGL()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TextureManagerGL::~TextureManagerGL()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    freeTextures();
}

SpriteGL * TextureManagerGL::createTexture(const std::string& filename, GLenum e)
{
    for (auto i = 0; i < textures.size(); i++)
    {
        if (textures[i]->name == filename)
        {
            return textures[i];
        }
    }

    auto texture = loadTexture(filename, e);

    if (texture != nullptr)
    {
        textures.push_back(texture);
    }

    return texture;
}

GLuint TextureManagerGL::getTextureCount()
{
    return(textures.size());
}

SpriteGL* TextureManagerGL::createTexture(GLubyte * data, GLuint width, GLuint height, GLenum format)
{
    auto sprite = new SpriteGL();
    sprite->height = height;
    sprite->width = width;

    glGenTextures(1, &sprite->textureID);
    glBindTexture(GL_TEXTURE_2D, sprite->textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)data);

    return sprite;
}

SpriteGL * TextureManagerGL::createGlyph(FT_Face face, GLenum format)
{
    auto sprite = new SpriteGL();
    sprite->height = face->glyph->bitmap.rows;
    sprite->width = face->glyph->bitmap.width;

    glGenTextures(1, &sprite->textureID);
    glBindTexture(GL_TEXTURE_2D, sprite->textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, sprite->width, sprite->height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)face->glyph->bitmap.buffer);

    return sprite;
}

SpriteGL* TextureManagerGL::loadTexture(const std::string& Location, GLenum e)
{
    FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(Location.c_str(), 0);
    FIBITMAP* texture = FreeImage_Load(formato, Location.c_str());
    FIBITMAP* temp = FreeImage_ConvertTo32Bits(texture);
    GLuint height = FreeImage_GetHeight(temp);
    GLuint width = FreeImage_GetWidth(temp);

    BYTE* newBits = new BYTE[height * width * 4];
    BYTE* prevBits = FreeImage_GetBits(temp);

    auto sprite = new SpriteGL();
    sprite->height = height;
    sprite->width = width;

    for (auto i = 0; i < width * height; i++)
    {
        newBits[i * 4 + 0] = prevBits[i * 4 + 2];
        newBits[i * 4 + 1] = prevBits[i * 4 + 1];
        newBits[i * 4 + 2] = prevBits[i * 4 + 0];
        newBits[i * 4 + 3] = prevBits[i * 4 + 3];
    }


    sprite->colours.reserve(width);
    sprite->colours.resize(width);

    for (GLuint i = 0; i < width; i++)
    {
        for (GLuint z = 0; z < height; z++)
        {
            if (z == 0)
            {
                sprite->colours[i].reserve(height);
            }

            RGBQUAD colours;
            FreeImage_GetPixelColor(temp, i, z, &colours);
            sprite->colours[i].push_back(colours);
        }
    }

    glGenTextures(1, &sprite->textureID);
    glBindTexture(GL_TEXTURE_2D, sprite->textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, e);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, e);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)newBits);

    FreeImage_Unload(texture);
    FreeImage_Unload(temp);

    delete[] newBits;
    return sprite;
}

GLvoid TextureManagerGL::freeTextures()
{
    for (GLuint i = 0; i < textures.size(); i++)
    {
        glDeleteTextures(1, &textures[i]->textureID);
        delete textures[i];
    }
}

TextureManagerGL* TextureManagerGL::get()
{
    if (manager == nullptr)
    {
        manager = new TextureManagerGL();
    }

    return manager;
}