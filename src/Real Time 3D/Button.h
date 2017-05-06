
/* -------------------------------------------------
  
 @Filename  : Button.h
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: A simple button object class

 ------------------------------------------------- */

#pragma once

#include "RendererGL.h"
#include "TextureGL.h"
#include "TextGL.h"

class Button
{
private:

	TextureGL * m_pSprite;		// The texture
	TextGL * m_pString;
	
	vec2 m_Position;			// Position
	vec2 m_Size;				// Size

public:

	// Constructor & Deconstructor
	Button();
	~Button();

	// Member Functions
	bool MouseState(int, int, int, int);
	void SetPosition(std::string, vec2, vec2);
	void render(RendererGL *);

	// Get & Set Functions
	TextureGL * getTexture();
	TextGL * getString();
};