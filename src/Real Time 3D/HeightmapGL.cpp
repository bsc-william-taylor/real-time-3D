
#include "ShaderManagerGL.h"
#include "HeightmapGL.h"

HeightmapGL::HeightmapGL()
    : filename(""),
    scale(50),
    matrix(new MatrixGL())
{
    matrix->perspective(70, vec2(16, 9), vec2(0.1, 1000));
    positions.reserve(2000);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &positionBuffer);
    glGenBuffers(1, &overlayBuffer);
    glGenBuffers(1, &uvBuffer);
    glGenBuffers(1, &normalBuffer);
    glBindVertexArray(0);
}

HeightmapGL::~HeightmapGL()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &positionBuffer);
    glDeleteBuffers(1, &overlayBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteBuffers(1, &normalBuffer);
}

GLfloat HeightmapGL::getY(GLuint x, GLuint z)
{
    GLfloat y = 0.0f;

    if (x < heightmap->colours.size() && z < heightmap->colours[x].size())
    {
        RGBQUAD colours = heightmap->colours[x][z];

        y += ((GLfloat)colours.rgbReserved) / 255.0f;
        y += ((GLfloat)colours.rgbGreen) / 255.0f;
        y += ((GLfloat)colours.rgbBlue) / 255.0f;
        y += ((GLfloat)colours.rgbRed) / 255.0f;
    }

    return(y);
}

GLvoid HeightmapGL::setScale(GLuint scale)
{
    this->scale = scale;
}

GLvoid HeightmapGL::prepare()
{
    heightmap = TextureManagerGL::get()->createTexture(filename, GL_CLAMP_TO_EDGE);
    texture = TextureManagerGL::get()->createTexture(textureFilename, GL_REPEAT);

    GLfloat y2 = 1.0f / (float)heightmap->height;
    GLfloat x2 = 1.0f / (float)heightmap->width;
    GLfloat tx = 0.0f;
    GLfloat ty = 0.0f;

    GLint x = -GLint(heightmap->width / 2);

    positions.reserve(heightmap->width * heightmap->width * 6);
    overlay.reserve(heightmap->width * heightmap->width * 6);
    normals.reserve(heightmap->width * heightmap->width * 6);
    uvs.reserve(heightmap->width * heightmap->width * 6);

    for (GLint c = 0; c < heightmap->width; c++, x++)
    {
        GLint z = -GLint(heightmap->width / 2);
        for (GLint i = 0; i < heightmap->height; i++, z++)
        {
            vec3 v1 = vec3(x, getY(c, i), z);
            vec3 v2 = vec3(x, getY(c, i + 1), z + 1);
            vec3 v3 = vec3(x + 1, getY(c + 1, i + 1), z + 1);

            positions.push_back(v1);
            positions.push_back(v2);
            positions.push_back(v3);

            overlay.push_back(vec3(x, z, 0));
            overlay.push_back(vec3(x, z + 1, 0));
            overlay.push_back(vec3(x + 1, z + 1, 0));

            uvs.push_back(vec3(tx, ty, 0));
            uvs.push_back(vec3(tx, ty + y2, 0));
            uvs.push_back(vec3(tx + x2, ty + y2, 0));

            normals.push_back(getNormal(v1, v3, v2));
            normals.push_back(getNormal(v2, v1, v3));
            normals.push_back(getNormal(v3, v2, v1));

            v1 = vec3(x, getY(c, i), z);
            v2 = vec3(x + 1, getY(c + 1, i), z);
            v3 = vec3(x + 1, getY(c + 1, i + 1), z + 1);

            positions.push_back(v1);
            positions.push_back(v2);
            positions.push_back(v3);

            overlay.push_back(vec3(x, z, 0));
            overlay.push_back(vec3(x + 1, z, 0));
            overlay.push_back(vec3(x + 1, z + 1, 0));

            uvs.push_back(vec3(tx, ty, 0));
            uvs.push_back(vec3(tx + x2, ty, 0));
            uvs.push_back(vec3(tx + x2, ty + y2, 0));

            normals.push_back(getNormal(v1, v2, v3));
            normals.push_back(getNormal(v2, v3, v1));
            normals.push_back(getNormal(v3, v1, v2));

            ty += y2;
        }

        ty = 0.0f;
        tx += x2;
    }

    for (unsigned int i = 0; i < normals.size() - 24; i++)
    {
        vec3 average = vec3(0.0, 0.0, 0.0);
        for (unsigned int b = i; b < i + 24; b++)
        {
            average += normals[b];
        }

        average /= 24;

        for (unsigned int b = i; b < i + 24; b++)
        {
            normals[b] = average;
        }
    }

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, overlayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * overlay.size(), &overlay[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    glLineWidth(0.1f);

    GLchar * vs = "data/shaders/heightmap.vert";
    GLchar * fs = "data/shaders/heightmap.frag";

    shader = ShaderManagerGL::get()->getShader(vs, fs);
}

GLfloat HeightmapGL::getMapY(vec3 camera)
{
    heightmap->height;
    heightmap->width;
    return 0;
}

GLvoid HeightmapGL::onUpdate()
{
    matrix->loadIdenditity();
    matrix->translate(vec3(0, -59.5, 0));
    matrix->scale(vec3(24, 1, 24));
}

vec3 HeightmapGL::getNormal(vec3 v1, vec3 v2, vec3 v3)
{
    vec3 Normal = glm::cross(v2 - v1, v3 - v1);
    Normal = glm::normalize(Normal);
    return(Normal);
}

GLvoid HeightmapGL::setMapTexture(std::string m_file)
{
    textureFilename = m_file;
}

GLvoid HeightmapGL::PushOverlay(MapOverlayGL * overlay)
{
    overlays.push_back(overlay);
}

GLvoid HeightmapGL::Draw()
{
    shader->use();
    glBindVertexArray(vertexArrayObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);

    GLint Sampler = glGetUniformLocation(shader->getProgramID(), "ID");
    glUniform1i(Sampler, 0);

    for (GLuint i = 0; i < overlays.size(); i++)
    {
        overlays[i]->prepareShader(shader);
    }

    shader->setMatrix("Projection", matrix->getProjection());
    shader->setMatrix("Model", matrix->getModel());
    shader->setMatrix("View", matrix->getView());

    GLint loc = glGetUniformLocation(shader->getProgramID(), "Scale");
    glUniform1i(loc, scale);
    glDrawArrays(GL_TRIANGLES, 0, 6 * (heightmap->height * heightmap->width));
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shader->release();
}

GLvoid HeightmapGL::setHeightMap(std::string filename)
{
    this->filename = filename;
}

ProgramGL* HeightmapGL::getProgram()
{
    return shader;
}

MatrixGL* HeightmapGL::getMatrix()
{
    return matrix;
}