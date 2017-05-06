
#version 330

layout(location = 0) in vec4 positions;

uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;

out vec2 texpos;

void main()
{
	gl_Position = Projection * View * Model * vec4(positions.xy, 0.0, 1.0);
	texpos = positions.zw;
}