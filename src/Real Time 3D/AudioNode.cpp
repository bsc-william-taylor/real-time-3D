
#include "AudioNode.h"

AudioNode::AudioNode()
{
}

AudioNode::~AudioNode()
{
}

GLvoid AudioNode::initialise(vec3 p, vec3 s)
{
    shader = ShaderManagerGL::get()->getShader("data/shaders/cube.vert", "data/shaders/cube.frag");
    sprite.setTexture("data/img/audio.png", GL_CLAMP_TO_EDGE);
    sprite.prepare();

    matrix.loadIdenditity();
    matrix.perspective(70.0f, vec2(16, 9), vec2(0.1, 10000));

    GLfloat texpos[] = {
        0.0, 1.0,	1.0, 1.0,
        1.0, 0.0,	1.0, 0.0,
        0.0, 0.0,	0.0, 1.0,
        0.0, 1.0,	1.0, 1.0,
        1.0, 0.0,	1.0, 0.0,
        0.0, 0.0,	0.0, 1.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
        0.0, 0.0,	0.0, 0.0,
    };

    vec3 positions[] =
    {
        // Back face
        vec3(p.x, s.y, s.z), vec3(s.x, s.y, s.z), vec3(s.x, p.y, s.z),
        vec3(s.x, p.y, s.z), vec3(p.x, p.y, s.z), vec3(p.x, s.y, s.z),
        // Font face
        vec3(s.x, s.y, p.z), vec3(p.x, s.y, p.z), vec3(p.x, p.y, p.z),
        vec3(p.x, p.y, p.z), vec3(s.x, p.y, p.z), vec3(s.x, s.y, p.z),
        // Left face
        vec3(p.x, s.y, p.z), vec3(p.x, s.y, s.z), vec3(p.x, p.y, s.z),
        vec3(p.x, p.y, s.z), vec3(p.x, p.y, p.z), vec3(p.x, s.y, p.z),
        // Right face
        vec3(s.x, s.y, s.z), vec3(s.x, s.y, p.z), vec3(s.x, p.y, p.z),
        vec3(s.x, p.y, p.z), vec3(s.x, p.y, s.z), vec3(s.x, s.y, s.z),
        // Top face 
        vec3(p.x, s.y, p.z), vec3(s.z, s.y, p.z), vec3(s.x, s.y, s.z),
        vec3(s.x, s.y, s.z), vec3(p.x, s.y, s.y), vec3(p.x, s.y, p.z),
        // Bottom face
        vec3(p.x, p.y, s.z), vec3(s.x, p.y, s.z), vec3(s.x, p.y, p.z),
        vec3(s.x, p.y, p.z), vec3(p.x, p.y, p.z), vec3(p.x, p.y, s.z),
    };

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 36, &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 12, &texpos, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
}

GLvoid AudioNode::render()
{
    shader->use();
    shader->setMatrix("Projection", matrix.getProjection());
    shader->setMatrix("Model", matrix.getModel());
    shader->setMatrix("View", matrix.getView());

    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, sprite.getProgramID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    shader->release();
}

MatrixGL* AudioNode::getMatrix()
{
    return &matrix;
}