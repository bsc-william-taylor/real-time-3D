
#version 330 core

layout(location = 0) out vec4 Output;

uniform sampler2D Overlay;
uniform sampler2D Texture;
uniform sampler2D ID;

smooth in vec3 normal;
smooth in vec2 overlay;
smooth in vec2 texture;

void main()
{
	vec4 TextureColour = texture2D(ID, texture);
	vec4 addon = texture2D(Overlay, overlay);

	if(addon.a > 0.0)
	{
		vec4 shader = texture2D(Texture, texture);
	
		TextureColour = mix(TextureColour, shader, addon.a);
	}

	Output = TextureColour * max(0.0, dot(normalize(normal), normalize(vec3(-0.61, -0.64, -0.47))));
	Output.a = 1.0f;
}
