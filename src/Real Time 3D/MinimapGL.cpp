
#include "MinimapGL.h"

MinimapGL::MinimapGL()
{
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindVertexArray(0);
}

MinimapGL::~MinimapGL()
{
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &vertexBuffer);
}

GLvoid MinimapGL::initialise(Camera* newCamera)
{
    GLchar* vs = "data/shaders/postprocessor.vert";
    GLchar* fs = "data/shaders/postprocessor.frag";
    GLfloat position[] = {
         10,  550, 0,  0,
         10,  700, 0,  1,
         160, 550, 1,  0,
         160, 700, 1,  1
    };

    shader = ShaderManagerGL::get()->getShader(vs, fs);
    matrix.ortho(vec2(0, 1280), vec2(0, 720));
    camera = newCamera;

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, &position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glGenTextures(1, &colourBuffer);
    glBindTexture(GL_TEXTURE_2D, colourBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 240, 200, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourBuffer, 0);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 240, 200);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLvoid MinimapGL::renderToBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 240, 200);

    previousPosition = camera->getTranslate();
    previousRotation = camera->getRotation();
    previousPitch = camera->getPitch();

    camera->setPosition(vec3(previousPosition.x, -100, previousPosition.z));
    camera->setRotation(0);
    camera->setPitch(90);
}

GLvoid MinimapGL::renderToScreen()
{
    shader->use();
    shader->setMatrix("Projection", matrix.getProjection());
    shader->setMatrix("Model", matrix.getModel());
    shader->setMatrix("View", matrix.getView());

    glViewport(0, 0, 1280, 720);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, colourBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shader->release();

    camera->setPosition(previousPosition);
    camera->setRotation(previousRotation);
    camera->setPitch(previousPitch);
}