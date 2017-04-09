
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vTexture;
layout (location = 2) in vec3 vOverlay;
layout (location = 3) in vec3 vNormals;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
uniform int Scale;

smooth out vec2 overlay;
smooth out vec2 texture;
smooth out vec3 normal;

void main() 
{
	vec4 ActualPosition = vec4(vPosition, 1.0);
	ActualPosition.y = ActualPosition.y * Scale;
	mat4 ModelView = View * Model;

	gl_Position =  Projection * ModelView * ActualPosition;

	texture = vTexture.xy;
	overlay = vOverlay.xy;
	normal = vNormals;
}