
#include "RendererGL.h"
#include "SurfaceManager.h"

RendererGL::RendererGL()
{
    textures.reserve(20);
    heightmap = NULL;
}

RendererGL::~RendererGL()
{
    // Add cleanup code
}

GLvoid RendererGL::pushAudioNode(AudioNode * node)
{
    if (node != NULL)
    {
        audioNodes.push_back(node);
    }
}

GLvoid RendererGL::pushHeightmap(HeightmapGL * object)
{
    if (object != NULL)
    {
        heightmap = object;
    }
}

GLvoid RendererGL::pushSurface(Surface * surface)
{
    if (surface != NULL)
    {
        surfaces.push_back(surface);
    }
}

GLvoid RendererGL::renderTexture(TextureGL * texture)
{
    ProgramGL * program = texture->getProgram();
    MatrixGL * matrix = texture->getMatrix();

    program->use();

    glBindVertexArray(texture->getVAO());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getProgramID());

    GLuint ID = glGetUniformLocation(program->getProgramID(), "shade");
    glUniform4fv(ID, 1, glm::value_ptr(texture->getShade()));
    program->setMatrix("Projection", matrix->getProjection());
    program->setMatrix("Model", matrix->getModel());
    program->setMatrix("View", matrix->getView());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

GLvoid RendererGL::render3D(GLboolean wireframe)
{
    glEnable(GL_DEPTH_TEST);

    if (!wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

GLvoid RendererGL::render2D(GLboolean wireframe)
{
    glDisable(GL_DEPTH_TEST);

    if (!wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

GLvoid RendererGL::renderModel(Model * model, mat4 mat)
{
    if (!model->isDynamic())
    {
        StaticModel * Model = (StaticModel *)model;
        ProgramGL * program = Model->getProgram();
        MatrixGL * matrix = Model->getMatrix();

        glBindVertexArray(Model->getVAO());

        program->use();
        program->setMatrix("Projection", matrix->getProjection());
        program->setMatrix("NormalMat", mat4(1.0));
        program->setMatrix("Model", matrix->getModel());
        program->setMatrix("View", matrix->getView());

        for (unsigned int i = 0; i < Model->getMeshNumber(); i++)
        {
            GLuint Index = Model->getMaterialIndex(i);
            GLuint ID = Model->getTextureID(Index);

            if (ID != -1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, ID);
            }

            glDrawArrays(GL_TRIANGLES, Model->getMeshStart(i), Model->getMeshEnd(i));
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        program->release();

        glBindVertexArray(0);
    }
    else
    {
        ((DynamicModel *)model)->render(mat);
    }
}

GLvoid RendererGL::pushSkybox(SkyboxGL * object)
{
    skybox = object;

    auto Textures = skybox->getTextures();

    for (unsigned int i = 0; i < Textures.size(); i++)
    {
        pushTexture(Textures[i]);
    }
}

GLvoid RendererGL::pushTexture(TextureGL * object)
{
    if (object != NULL)
    {
        textures.push_back(object);
    }
}

GLvoid RendererGL::pushModel(Model * object)
{
    if (object != NULL)
    {
        models.push_back(object);
    }
}

GLvoid RendererGL::ortho(const vec2 a, const vec2 b, const vec2 c)
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i]->getMatrix()->ortho(a, b, c);
    }
}

GLvoid RendererGL::setSurfaceSize(vec4 vec)
{
    this->surfaceSize = vec;
}

GLvoid RendererGL::LoadIdentity()
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i]->getMatrix()->loadIdenditity();
    }

    for (unsigned int i = 0; i < labels.size(); i++)
    {
        GLint height = (GLint)surfaceSize.w;
        GLint width = (GLint)surfaceSize.z;

        labels[i]->getMatrix()->loadIdenditity();
        labels[i]->getMatrix()->ortho(vec2(0, width), vec2(0, height), vec2(-1, 1));
    }

    for (unsigned int i = 0; i < models.size(); i++)
    {
        models[i]->getMatrix()->loadIdenditity();
    }

    for (unsigned int i = 0; i < audioNodes.size(); i++)
    {
        audioNodes[i]->getMatrix()->loadIdenditity();
    }

    if (heightmap)
    {
        heightmap->getMatrix()->loadIdenditity();
    }
}

GLvoid RendererGL::onUpdate()
{
    skybox ? skybox->onUpdate() : 0;
    if (heightmap)heightmap->onUpdate();
    for (unsigned int i = 0; i < textures.size(); i++)
        textures[i]->onUpdate();
    for (unsigned int i = 0; i < labels.size(); i++)
        labels[i]->onUpdate();
    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->onUpdate();
}

GLvoid RendererGL::prepare()
{

    if (heightmap)heightmap->prepare();


    for (unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i]->prepare();
    }


    for (unsigned int i = 0; i < labels.size(); i++)
        labels[i]->prepare();


    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->prepare();
}

GLvoid RendererGL::render()
{
    if (heightmap)heightmap->Draw();
    for (unsigned int i = 0; i < textures.size(); i++)
        renderTexture(textures[i]);
    for (unsigned int i = 0; i < models.size(); i++)
        renderModel(models[i], mat4(1.0f));
    for (unsigned int i = 0; i < labels.size(); i++)
        labels[i]->render();
    for (unsigned int i = 0; i < surfaces.size(); i++)
        surfaces[i]->render();

    for (unsigned int i = 0; i < audioNodes.size(); i++)
    {
        audioNodes[i]->render();
    }
}

GLvoid RendererGL::pushText(TextGL * textItem)
{
    if (textItem != NULL)
    {
        labels.push_back(textItem);
    }
}

GLvoid RendererGL::perspective(const float f, const vec2 v1, const vec2 v2)
{
    for (unsigned int i = 0; i < textures.size(); i++) {
        textures[i]->getMatrix()->perspective(f, v1, v2);
    }

    for (unsigned int i = 0; i < models.size(); i++) {
        models[i]->getMatrix()->perspective(f, v1, v2);
    }

    for (unsigned int i = 0; i < labels.size(); i++) {
        labels[i]->getMatrix()->perspective(f, v1, v2);
    }

    if (heightmap) {
        heightmap->getMatrix()->perspective(f, v1, v2);
    }
}

GLvoid RendererGL::rotateView(GLfloat f, vec3 a)
{
    if (heightmap)heightmap->getMatrix()->rotateView(f, a);
    for (unsigned int i = 0; i < textures.size(); i++)
        textures[i]->getMatrix()->rotateView(f, a);
    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->getMatrix()->rotateView(f, a);
    for (unsigned int i = 0; i < audioNodes.size(); i++)
        audioNodes[i]->getMatrix()->rotateView(f, a);
}

GLvoid RendererGL::rotate(GLfloat f, vec3 a)
{
    if (heightmap)heightmap->getMatrix()->rotate(f, a);
    for (unsigned int i = 0; i < textures.size(); i++)
        textures[i]->getMatrix()->rotate(f, a);
    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->getMatrix()->rotate(f, a);
}

GLvoid RendererGL::translateView(vec3 v)
{
    if (heightmap)heightmap->getMatrix()->translateView(v);
    skybox ? skybox->translate(v) : 0;
    for (unsigned int i = 0; i < textures.size(); i++)
        textures[i]->getMatrix()->translateView(v);
    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->getMatrix()->translateView(v);
    for (unsigned int i = 0; i < audioNodes.size(); i++)
        audioNodes[i]->getMatrix()->translateView(v);
}

GLvoid RendererGL::translate(vec3 v)
{
    if (heightmap)heightmap->getMatrix()->translate(v);
    for (unsigned int i = 0; i < textures.size(); i++)
        textures[i]->getMatrix()->translate(v);
    for (unsigned int i = 0; i < labels.size(); i++)
        labels[i]->getMatrix()->translate(v);
    for (unsigned int i = 0; i < models.size(); i++)
        models[i]->getMatrix()->translate(v);
}

HeightmapGL* RendererGL::getHeightmap()
{
    return heightmap;
}