
#pragma once

#include "ThirdPersonCamera.h"
#include "SceneManager.h"
#include "AudioPlayer.h"
#include "AudioObject.h"
#include "Button.h"
#include "PostProcessorGL.h"
#include "MinimapGL.h"
#include "HeightmapGL.h"
#include "MinimapGL.h"

class DemoScene : public Scene
{
    ThirdPersonCamera camera;
    PostProcessorGL effects;
    MapOverlayGL overlaymap;
    HeightmapGL heightmap;
    AudioPlayer audioPlayer;
    AudioObject music;
    RendererGL renderer;
    DynamicModel player;
    StaticModel city;
    MinimapGL miniMap;
    SkyboxGL skybox;
    Button options;
    Button quit;
    bool loaded;
public:
    DemoScene();
    ~DemoScene();

    void mousePress(int, int, int, int);
    void onMotion(float, float);
    void onKeyPress(int, int);
    void setupGraphics();
    void setupAudio();
    void onUpdate();
    void render();
    void enter();
};