
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 texture;

void main() 
{
	vec4 ActualPosition = vec4(vPosition, 1.0);
	mat4 ModelView = View * Model;
	gl_Position = Projection * ModelView * ActualPosition;
	texture = vTexture;
}