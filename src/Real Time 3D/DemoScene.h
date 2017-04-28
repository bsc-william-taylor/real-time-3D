
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
    ThirdPersonCamera * m_pCamera;
    DynamicModel * m_pPlayer;
    StaticModel * m_pCity;

    GL_PostProcessor * m_pEffects;
    GL_MapOverlay * m_Overlaymap;
    GL_Heightmap * m_Heightmap;
    GL_Renderer * m_pRenderer;
    GL_Minimap * m_pMiniMap;
    GL_Skybox * m_pSkybox;
    GLboolean m_Loaded;

    AudioPlayer * m_pAudioPlayer;
    AudioObject * m_pMusic;
    Button * m_pOptions;
    Button * m_pQuit;
public:
    DemoScene();
    ~DemoScene();

    void MousePress(int, int, int, int);
    void Motion(float, float);
    void KeyPress(int, int);
    void Update();
    void Render();
    void Enter();
    void SetupGraphics();
    void SetupAudio();
};