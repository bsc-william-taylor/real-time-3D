
#version 330 core

layout (location = 0) in vec4 vPosition;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

out vec2 texture;

void main() 
{
	mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;

	vec4 position = vec4(vPosition.x, vPosition.y, 0.0, 1.0);
	vec2 texpos = vec2(vPosition.z, vPosition.w);
	
	gl_Position = ModelViewMatrix * position;
	
	texture = texpos;
}