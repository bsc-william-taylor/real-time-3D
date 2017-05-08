
#include "TextGL.h"

TextGL::TextGL() :
    fontSize(12),
    freeTypeFace(NULL)
{
    if (FT_Init_FreeType(&freeTypeLibrary))
    {
        std::cout << "Could not init freetype library\n" << std::endl;
    }

    loaded = GL_FALSE;
}

TextGL::~TextGL()
{
    FT_Done_Face(freeTypeFace);
    FT_Done_FreeType(freeTypeLibrary);
}

GLvoid TextGL::prepare()
{
}

GLvoid TextGL::onUpdate()
{
    matrix.loadIdenditity();
    matrix.ortho(vec2(0, 1280), vec2(0, 720));
}

GLvoid TextGL::render()
{
    glBindVertexArray(0);

    shader->use();
    shader->setMatrix("ModelMatrix", matrix.getModel());
    shader->setMatrix("ViewMatrix", matrix.getView());

    if (!loaded)
    {
        vec2 prevPosition = position;

        for (GLuint i = 0; i < text.size(); i++)
        {
            if (FT_Load_Char(freeTypeFace, text[i], FT_LOAD_RENDER) || text[i] == ' ')
            {
                position.x += 10;
            }
            else
            {
                GLint location = characters.size();

                GLenum error = glGetError();
                if (error != GL_NO_ERROR)
                {
                    MessageBox(0, std::to_string(error).c_str(), std::to_string(i).c_str(), 0);
                }

                characters.push_back(new Character());
                characters[location]->sprite = TextureManagerGL::get()->createGlyph(freeTypeFace, GL_ALPHA);

                GLuint bitmapHeight = freeTypeFace->glyph->bitmap.rows;
                GLuint bitmapWidth = freeTypeFace->glyph->bitmap.width;

                position.y -= bitmapHeight - freeTypeFace->glyph->bitmap_top;

                GLfloat units[] =
                {
                    position.x, position.y, 0, 1,
                    position.x + bitmapWidth, position.y, 1, 1,
                    position.x, position.y + bitmapHeight, 0, 0,
                    position.x + bitmapWidth, position.y + bitmapHeight, 1, 0,
                };

                glGenBuffers(1, &characters[location]->vertexBuffer);
                glBindBuffer(GL_ARRAY_BUFFER, characters[location]->vertexBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, &units, GL_DYNAMIC_DRAW);

                position.x += freeTypeFace->glyph->bitmap.width + 2;
                position.y = prevPosition.y;
            }
        }

        position = prevPosition;
        loaded = GL_TRUE;
    }

    for (unsigned int i = 0; i < characters.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, characters[i]->sprite->textureID);
        glBindBuffer(GL_ARRAY_BUFFER, characters[i]->vertexBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    shader->release();
}

GLvoid TextGL::setSize(GLuint size)
{
    if (freeTypeFace == NULL)
    {
        if (FT_New_Face(freeTypeLibrary, fontname.c_str(), 0, &freeTypeFace))
        {
            std::cout << "Could not open font " + fontname << std::endl;
        }
    }

    FT_Set_Pixel_Sizes(freeTypeFace, 0, size);
    fontSize = size;

    const char * vs = "data/shaders/text.vert";
    const char * fs = "data/shaders/text.frag";

    shader = ShaderManagerGL::get()->getShader(vs, fs);
}

GLuint TextGL::getHeight()
{
    GLuint height = NULL;
    for (GLuint i = 0; i < text.size(); i++)
    {
        FT_Load_Char(freeTypeFace, text[i], FT_LOAD_RENDER);

        height += freeTypeFace->glyph->bitmap.rows;
    }

    return(height / text.size());
}

GLuint TextGL::getWidth()
{
    GLuint width = 0;

    for (GLuint i = 0; i < text.size(); i++)
    {
        FT_Load_Char(freeTypeFace, text[i], FT_LOAD_RENDER);

        width += freeTypeFace->glyph->bitmap.width;
        width += 2;
    }

    return width;
}

GLvoid TextGL::setPosition(vec2 pos)
{
    position = pos;
}

GLvoid TextGL::setFont(std::string filename)
{
    fontname = filename;
}

GLvoid TextGL::setText(std::string val)
{
    text = val;
}

ProgramGL* TextGL::getProgram()
{
    return shader;
}

MatrixGL* TextGL::getMatrix()
{
    return &matrix;
}