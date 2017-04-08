
#version 330

uniform sampler2D texture;

in vec2 t;

out vec4 colour;

void main()
{
	colour = texture2D(texture, t);
	colour.a = 1.0;
}