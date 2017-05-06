
#version 330 core

uniform sampler2D sampler;

layout(location = 0) out vec4 colour;

in vec4 highlight;
in vec2 texture;

void main()
{
	colour = texture2D(sampler, texture) * highlight;
}