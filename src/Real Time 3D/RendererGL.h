
/* -------------------------------------------------
  
 @Filename  : GL_Renderer.h
 @author	: William Taylor
 @date		: 14/02/2014
  @purpose	: A renderer which draws objects
              and executes operations on all 
			  objects in a Scene.

 ------------------------------------------------- */

#pragma once

#include "DynamicModel.h"
#include "StaticModel.h"
#include "HeightmapGL.h"
#include "TextureGL.h"
#include "SkyboxGL.h"
#include "AudioNode.h"
#include "TextGL.h"
#include "Surface.h"

class RendererGL
{
private:

	vector<AudioNode *> m_AudioNodes;
	vector<Surface *> m_Surfaces;
	vector<IModel *> m_Models;

	vector<TextureGL *> m_Textures;
	vector<TextGL *> m_Labels;
	
	HeightmapGL * heightmap;
	SkyboxGL * m_Skybox;
	
	vec4 m_SurfaceSize;
	vec2 a, b, c;

public:

	// Constructor & Deconstuctor
	RendererGL();	
	~RendererGL();
		
	// Member Functions
	GLvoid PushHeightmap(HeightmapGL *);
	GLvoid PushAudioNode(AudioNode *);
	GLvoid PushTexture(TextureGL *);
	GLvoid PushSkybox(SkyboxGL *);
	GLvoid PushModel(IModel *);
	GLvoid PushText(TextGL *);
	
	GLvoid PushSurface(Surface *);
	GLvoid Prepare();
	GLvoid update();
	GLvoid render();

	GLvoid RenderTexture(TextureGL *);
	GLvoid RenderModel(IModel *, mat4);
	GLvoid Render3D(GLboolean);
	GLvoid Render2D(GLboolean);

	// Object Operations
	GLvoid Perspective(const float, const vec2, const vec2);
	GLvoid Ortho(const vec2, const vec2, const vec2);
	GLvoid RotateView(GLfloat, vec3);
	GLvoid Rotate(GLfloat, vec3);
	GLvoid TranslateView(vec3);
	GLvoid Translate(vec3);
	GLvoid LoadIdentity();

	// Get & Set Functions
	GLvoid setSurfaceSize(vec4);

	HeightmapGL * getHeightmap(){ return heightmap; }
};