
#version 330

uniform sampler2D sampler;

out vec4 colour;

in vec2 texpos;

void main()
{
	colour = texture2D(sampler, texpos);
	colour.rgba *= 2.0;
}