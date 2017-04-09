
#version 330 core

uniform sampler2D sampler;

layout(location = 0) out vec4 colour;

smooth in vec3 normal;
smooth in vec2 texture;

void main()
{
	colour = texture2D(sampler, texture);

	vec4 diffuse = colour * max(0.0, dot(normalize(normal), vec3(-0.61, -0.64, -0.47)));
	colour *= 0.2;
	colour += (diffuse * 0.8);
	colour.a = 1.0;
}