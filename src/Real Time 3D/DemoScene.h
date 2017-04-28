
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
    ThirdPersonCamera* m_pCamera;
    DynamicModel* m_pPlayer;
    StaticModel* m_pCity;
    Button* m_pOptions;
    Button* m_pQuit;

    GL_PostProcessor* m_pEffects;
    GL_MapOverlay* m_Overlaymap;
    GL_Heightmap* m_Heightmap;
    GL_Renderer* m_pRenderer;
    GL_Minimap* m_pMiniMap;
    GL_Skybox* m_pSkybox;
    GLboolean m_Loaded;

    AudioPlayer* m_pAudioPlayer;
    AudioObject* m_pMusic;
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