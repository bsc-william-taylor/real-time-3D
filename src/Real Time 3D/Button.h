
/* -------------------------------------------------
  
 @Filename  : Button.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A simple button object class

 ------------------------------------------------- */

#pragma once

#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "GL_Text.h"

class Button
{
private:

	GL_Texture * m_pSprite;		// The texture
	GL_Text * m_pString;
	
	vec2 m_Position;			// Position
	vec2 m_Size;				// Size

public:

	// Constructor & Deconstructor
	Button();
	~Button();

	// Member Functions
	bool MouseState(int, int, int, int);
	void SetPosition(std::string, vec2, vec2);
	void Render(GL_Renderer *);

	// Get & Set Functions
	GL_Texture * getTexture();
	GL_Text * getString();
};