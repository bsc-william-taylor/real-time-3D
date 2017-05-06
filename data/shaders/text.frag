

#version 330 core

uniform sampler2D sampler;

layout(location = 0) out vec4 colour;

in vec3 TextColour;
in vec2 texture;

void main()
{
	colour = vec4(0, 0, 0, texture2D(sampler, texture).a);
}