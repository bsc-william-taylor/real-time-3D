
#version 330 

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexPos;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 t;

void main()
{
	gl_Position = Projection * View * Model * vec4(vPosition, 1.0);
	t = vTexPos;
}