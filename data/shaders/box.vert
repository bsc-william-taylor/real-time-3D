
#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

void main() 
{
	mat4 ModelView = View * Model;
	gl_Position = Projection * ModelView * vec4(vPosition, 1.0);
}
