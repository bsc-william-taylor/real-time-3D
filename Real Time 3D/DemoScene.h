
#pragma once

#include "ThirdPersonCamera.h"
#include "SceneManager.h"
#include "AudioPlayer.h"
#include "AudioObject.h"
#include "FreeCamera.h"

#include "GL_PostProcessor.h"
#include "GL_MapOverlay.h"
#include "GL_Heightmap.h"
#include "GL_Minimap.h"

class DemoScene : public Scene
{
private:

	ThirdPersonCamera * m_pCamera;
	DynamicModel * m_pPlayer;
	StaticModel * m_pCity;
	Surface * m_pSurface;

public:

	DemoScene();
	~DemoScene();

	void Motion(GLfloat, GLfloat);
	void KeyPress(GLint, GLint);
	void Update();
	void Render();
	void Enter();

private:

	void SetupGraphics();
	void SetupAudio();
	
private:

	GL_PostProcessor * m_pEffects;
	GL_MapOverlay * m_Overlaymap;
	GL_Heightmap * m_Heightmap;
	GL_Renderer * m_pRenderer;
	GL_Minimap * m_pMiniMap;
	GL_Skybox * m_pSkybox;
	GLboolean m_Loaded;

private:

	AudioPlayer * m_pAudioPlayer;
	AudioObject * m_pMusic;

};