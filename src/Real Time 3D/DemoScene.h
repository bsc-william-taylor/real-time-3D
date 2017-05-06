
#pragma once

#include "ThirdPersonCamera.h"
#include "SceneManager.h"
#include "AudioPlayer.h"
#include "AudioObject.h"
#include "FreeCamera.h"
#include "Button.h"
#include "GL_PostProcessor.h"
#include "GL_MapOverlay.h"
#include "GL_Heightmap.h"
#include "GL_Minimap.h"

class DemoScene : public Scene
{
    ThirdPersonCamera* camera;
    DynamicModel* player;
    StaticModel* city;
    Button* options;
    Button* quit;

    GL_PostProcessor* effects;
    GL_MapOverlay* overlaymap;
    GL_Heightmap* heightmap;
    GL_Renderer* renderer;
    GL_Minimap* miniMap;
    GL_Skybox* skybox;
    GLboolean loaded;

    AudioPlayer* audioPlayer;
    AudioObject* music;
public:
    DemoScene();
    ~DemoScene();

    void mousePress(int, int, int, int);
    void motion(float, float);
    void keyPress(int, int);
    void setupGraphics();
    void setupAudio();
    void update();
    void render();
    void enter();
};