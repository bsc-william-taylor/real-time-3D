
#pragma once

#include "RendererGL.h"
#include "TextureGL.h"
#include "TextGL.h"

class Button
{
	TextureGL* sprite;		
	TextGL* string;
	
	vec2 position;			
	vec2 size;				
public:
	Button();
	~Button();

	bool MouseState(int, int, int, int);
	void SetPosition(std::string, vec2, vec2);
	void render(RendererGL *);

	TextureGL * getTexture();
	TextGL * getString();
};