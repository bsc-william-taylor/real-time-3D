
/* -------------------------------------------------
  
 @Filename  : Button.cpp
 @author	: William Taylor
 @date		: 19/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Button.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
Button::Button()
	: m_pSprite(new TextureGL()),
	  m_pString(new TextGL())
{
	m_pSprite->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720));
	m_pString->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720));
}

Button::~Button()
{
	SAFE_RELEASE(m_pString);
	SAFE_RELEASE(m_pSprite);
}

// Member Functions
void Button::SetPosition(std::string str, vec2 position, vec2 size)
{
	m_pSprite->setTexture("data/img/button.png", GL_CLAMP_TO_EDGE);
	m_pSprite->setPosition(vec3(position, 0.0), vec3(size, 0.0));
	m_pSprite->Prepare();

	m_pString->setFont("data/img/MavenPro-Regular.ttf");
	m_pString->setPosition(position);
	m_pString->setText(str.c_str());
	m_pString->setSize(25);
	m_pString->Prepare();

	GLuint Height = (int)size.y - m_pString->getHeight();
	GLuint Width = (int)size.x - m_pString->getWidth();

	m_pString->getMatrix()->Translate(vec3(Width/2, Height/2, 0.0));
	m_Position = position;
	m_Size = size;
}

bool Button::MouseState(int Key, int State, int x, int y)
{
	if(x >= m_Position.x && x <= m_Position.x + m_Size.x 
		&& y >= m_Position.y && y <= m_Position.y + m_Size.y)
	{
		if(Key == MOUSE_1 && State == RELEASED)
		{
			return true;
		}
	}

	return false;
}

void Button::render(RendererGL * renderer)
{
	renderer->RenderTexture(m_pSprite);
	m_pString->render();
}

// Get & Set Functions
TextureGL * Button::getTexture()
{
	return m_pSprite;
}


TextGL * Button::getString()
{
	return m_pString;
}