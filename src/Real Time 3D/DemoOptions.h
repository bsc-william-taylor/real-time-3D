
/* -------------------------------------------------
  
 @Filename  : DemoOptions.h
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: The options scene

 ------------------------------------------------- */

#pragma once

#include "SceneManager.h"
#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "Button.h"

class DemoOptions : public Scene
{
private:

	GL_Renderer * m_pRenderer;					// The scenes renderer
	GL_Texture * m_pTexture;					// The background
	GL_Text * m_pHeader;						// The scenes header (title)

	/* All buttons that allow you to alter the options */
	Button * m_pShowCollisionBoxes;	
	Button * m_pEnablePostEffects;
	Button * m_pEnableWireframe;
	Button * m_pBackButton;

public:

	// Constructor & Deconstructor
	DemoOptions();
	~DemoOptions();

	void MousePress(int, int, int, int);		// Mouse press handler
	void Update();								// Update Function
	void Render();								// Draw Function

private:

	/* Private function to activate button upon press */
	void ActivateButton(Button *);				
};