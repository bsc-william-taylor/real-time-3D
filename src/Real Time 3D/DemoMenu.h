
/* -------------------------------------------------
  
 @Filename  : DemoMenu.h
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: The loading screen for the demo

 ------------------------------------------------- */

#pragma once

#include "SceneManager.h"
#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "GL_Text.h"

#include "Win32Timer.h"

class DemoMenu : public Scene
{
private:

	GL_Renderer * m_pMenuRenderer;		// The loading screens renderer
	GL_Texture * m_pBackground;			// The loading screens background
	GL_Text * m_Footer;					// The loading screens footer
	GL_Text * m_Header;					// The loading screens title

public:

	// Constructor & Deconstructor
	DemoMenu();
	~DemoMenu();

	// Member Functions
	void Update();						// Update function
	void Render();						// Render function 
	void Enter();						// Enter event handler

private:

	Win32Timer * m_pTimer;				// The windows timer
	float m_Alpha;					// The background alpha
};