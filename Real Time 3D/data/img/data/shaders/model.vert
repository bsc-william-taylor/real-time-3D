
#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inCoord;
layout (location = 2) in vec3 inNormal;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

smooth out vec2 texture;
smooth out vec3 normal;

void main()
{
	mat4 ModelViewMatrix = View * Model;

	gl_Position =  Projection * ModelViewMatrix * vec4(inPosition, 1.0);

	texture = inCoord.xy;
	normal = inNormal;
}