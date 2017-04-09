
/* -------------------------------------------------
  
 @Filename  : DemoScene.h
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: The main scene for the demo.

 ------------------------------------------------- */

#pragma once

// Include all other assets
#include "ThirdPersonCamera.h"
#include "SceneManager.h"
#include "AudioPlayer.h"
#include "AudioObject.h"
#include "FreeCamera.h"
#include "Button.h"

// Include GL Objects
#include "GL_PostProcessor.h"
#include "GL_MapOverlay.h"
#include "GL_Heightmap.h"
#include "GL_Minimap.h"

class DemoScene : public Scene
{
private:

	ThirdPersonCamera * m_pCamera;					// The scenes camera
	DynamicModel * m_pPlayer;						// The players model
	StaticModel * m_pCity;							// The city model					

public:

	// Constructor & Deconstructor
	DemoScene();
	~DemoScene();

	// Member Functions
	void MousePress(int, int, int, int);			// Mouse button handler	
	void Motion(float, float);						// Mouse motion handler
	void KeyPress(int, int);						// Key press handler
	void Update();									// Update function
	void Render();									// Draw function
	void Enter();									// Enter event handler

private:

	// Private Initialise Functions
	void SetupGraphics();
	void SetupAudio();
	
private:

	GL_PostProcessor * m_pEffects;				// Post Processing Class
	GL_MapOverlay * m_Overlaymap;				// Overlay for the heightmap
	GL_Heightmap * m_Heightmap;					// The scenes heightmap (3D terrain)
	GL_Renderer * m_pRenderer;					// The scenes renderer
	GL_Minimap * m_pMiniMap;					// The scenes minimap
	GL_Skybox * m_pSkybox;						// The scenes skybox
	GLboolean m_Loaded;						

private:

	AudioPlayer * m_pAudioPlayer;				// The audio player
	AudioObject * m_pMusic;						// Background music

	Button * m_pOptions;						// HUD Options Button
	Button * m_pQuit;							// HUD Options Button
};