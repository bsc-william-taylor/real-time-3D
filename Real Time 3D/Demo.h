
/* -------------------------------------------------
  
 @Filename  : Demo.h
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: The main class for the demo it 
			  manages allt he scenes and inits
			  all components.

 ------------------------------------------------- */

#pragma once

#include "SceneManager.h"
#include "Win32System.h"
#include "Win32Timer.h"

class Demo
{
private:

	SceneManager * m_pScenes;				// The scene manager		
	Win32System * m_pWin32;					// The windows system
	Win32Timer * m_pTimer;					// The window timer
	unsigned int m_FPS;						// The redraw rate
	float m_TimeLeft;						// Time left from drawing

public:

	// Constructor & Deconstructor
	Demo();
	~Demo();

	// Member Functions
	void WindowSize(int, int, int, int);	// Sets Window Size
	void RedrawRate(int);					// Sets Demo's FPS
	void HideConsole();						// Hides the console
	void Execute();							// Starts the program

private:

	// Private Initialise Functions
	void Init_Scenes();						// Initialises all scenes
	void Init_OpenGL();						// Initialises OpenGL

public:

	// Global Demo Settings
	struct DemoSettings
	{
		bool Wireframe;						// Display scene in wireframe
		bool Boxes;							// Display bounding boxes
		bool FX;							// Display effects
	};

	// Static variable to access settings
	static DemoSettings m_gSettings;
};