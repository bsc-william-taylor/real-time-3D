
#pragma once

#include "DynamicModel.h"
#include "StaticModel.h"
#include "HeightmapGL.h"
#include "TextureGL.h"
#include "SkyboxGL.h"
#include "AudioNode.h"
#include "TextGL.h"
#include "Surface.h"

class RendererGL
{
    vector<AudioNode*> audioNodes;
    vector<TextureGL*> textures;
    vector<Surface*> surfaces;
    vector<TextGL*> labels;
    vector<Model*> models;

    HeightmapGL* heightmap;
    SkyboxGL* skybox;

    vec4 surfaceSize;
public:
    RendererGL();
    ~RendererGL();

    GLvoid pushHeightmap(HeightmapGL *);
    GLvoid pushAudioNode(AudioNode *);
    GLvoid pushTexture(TextureGL *);
    GLvoid pushSkybox(SkyboxGL *);
    GLvoid pushModel(Model *);
    GLvoid pushText(TextGL *);
    GLvoid pushSurface(Surface *);
    GLvoid prepare();
    GLvoid onUpdate();
    GLvoid render();

    GLvoid renderTexture(TextureGL *);
    GLvoid renderModel(Model *, mat4);
    GLvoid render3D(GLboolean);
    GLvoid render2D(GLboolean);

    GLvoid perspective(const float, const vec2, const vec2);
    GLvoid ortho(const vec2, const vec2, const vec2);
    GLvoid rotateView(GLfloat, vec3);
    GLvoid rotate(GLfloat, vec3);
    GLvoid translateView(vec3);
    GLvoid translate(vec3);
    GLvoid LoadIdentity();
    GLvoid setSurfaceSize(vec4);

    HeightmapGL* getHeightmap();
};