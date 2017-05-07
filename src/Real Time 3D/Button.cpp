
#include "Button.h"
#include "Win32Codes.h"

Button::Button()
	: sprite(new TextureGL()),
	  string(new TextGL())
{
	sprite->getMatrix()->ortho(vec2(0, 1280), vec2(0, 720));
	string->getMatrix()->ortho(vec2(0, 1280), vec2(0, 720));
}

Button::~Button()
{
	SAFE_RELEASE(string);
	SAFE_RELEASE(sprite);
}

void Button::SetPosition(std::string str, vec2 position, vec2 size)
{
	sprite->setTexture("data/img/button.png", GL_CLAMP_TO_EDGE);
	sprite->setPosition(vec3(position, 0.0), vec3(size, 0.0));
	sprite->prepare();

	string->setFont("data/img/MavenPro-Regular.ttf");
	string->setPosition(position);
	string->setText(str.c_str());
	string->setSize(25);
	string->prepare();

	GLuint height = (int)size.y - string->getHeight();
	GLuint width = (int)size.x - string->getWidth();

	string->getMatrix()->translate(vec3(width/2, height/2, 0.0));
	this->position = position;
    this->size = size;
}

bool Button::MouseState(int Key, int State, int x, int y)
{
	if(x >= position.x && x <= position.x + size.x 
		&& y >= position.y && y <= position.y + size.y)
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
	renderer->renderTexture(sprite);
	string->render();
}

TextureGL * Button::getTexture()
{
	return sprite;
}


TextGL * Button::getString()
{
	return string;
}