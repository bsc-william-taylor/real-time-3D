
#include "TextureGL.h"
#include "TextureManagerGL.h"

TextureGL::TextureGL() :
    settings(GL_CLAMP_TO_EDGE),
    filename("")
{
    shade = vec4(1.0, 1.0, 1.0, 1.0);
    uv = vec4(0, 0, 1, 1);
}

TextureGL::~TextureGL()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
}

GLvoid TextureGL::surfacePlacements(GLuint m)
{
    setTexturePositions(vec2(0.0, 0.0), vec2(m, m));
}

void TextureGL::prepare()
{
    GLchar * vs = "data/shaders/texture.vert";
    GLchar * fs = "data/shaders/texture.frag";

    texture = TextureManagerGL::get()->createTexture(filename, settings);
    shader = ShaderManagerGL::get()->getShader(vs, fs);

    vec3 p = position;
    vec3 s = size;

    GLfloat data[] = {
        p.x, p.y, p.z, uv.x, uv.y,
        p.x, s.y, s.z, uv.x, uv.w,
        s.x, p.y, p.z, uv.z, uv.y,
        s.x, s.y, s.z, uv.z, uv.w
    };

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 20, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid*)12);
    glBindVertexArray(0);
}

vec4 TextureGL::getShade()
{
    return this->shade;
}

const std::string& TextureGL::getPath()
{
    return filename;
}

GLvoid TextureGL::setPosition(vec3 p, vec3 s)
{
    position = p;
    size = p + s;
}

GLvoid TextureGL::setShade(vec4 vec)
{
    this->shade = vec;
}

void TextureGL::setTexture(std::string filename, GLenum e)
{
    this->filename = filename;
    settings = e;
}

GLvoid TextureGL::setTexturePositions(vec2 a, vec2 b)
{
    uv = vec4(a, b);
}

GLuint TextureGL::getProgramID()
{
    return texture->textureID;
}

GLuint TextureGL::getVAO()
{
    return vertexArray;
}

MatrixGL* TextureGL::getMatrix()
{
    return &matrix;
}

ProgramGL* TextureGL::getProgram()
{
    return shader;
}