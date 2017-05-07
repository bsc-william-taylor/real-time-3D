
#include "PostProcessorGL.h"

PostProcessorGL::PostProcessorGL() :
    colour(vec4(1.0, 1.0, 1.0, 1.0))
{
}

PostProcessorGL::~PostProcessorGL()
{
}

GLvoid PostProcessorGL::enable()
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

GLvoid PostProcessorGL::execute()
{
    program->use();
    program->setMatrix("Projection", matrix.getProjection());
    program->setMatrix("Model", matrix.getModel());
    program->setMatrix("View", matrix.getView());

    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glUniform4fv(program->getUniform("overlay"), 1, glm::value_ptr(colour));
    glBindVertexArray(vertexArrayObject);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glViewport(0, 0, 1280, 720);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);

    program->release();
}

GLvoid PostProcessorGL::initialise(GLuint w, GLuint h)
{
    vertexArrayObject = NULL;

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLfloat Positions[] =
    {
        0, 0, 0, 0,
        0, h, 0, 1,
        w, 0, 1, 0,
        w, h, 1, 1
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, Positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    GLchar * vs = "data/shaders/postprocessor.vert";
    GLchar * fs = "data/shaders/postprocessor.frag";

    program = ShaderManagerGL::get()->getShader(vs, fs);

    matrix.ortho(vec2(0, w), vec2(0, h));

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    frameBuffer = NULL;

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBuffer, 0);

    depthBuffer = NULL;

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    glBindVertexArray(0);
}

GLvoid PostProcessorGL::setColourChannels(vec4 vec)
{
    colour = vec;
}