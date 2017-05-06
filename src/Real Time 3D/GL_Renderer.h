
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
#include "GL_Heightmap.h"
#include "GL_Texture.h"
#include "GL_Skybox.h"
#include "AudioNode.h"
#include "GL_Text.h"
#include "Surface.h"

class GL_Renderer
{
private:

	vector<AudioNode *> m_AudioNodes;
	vector<Surface *> m_Surfaces;
	vector<IModel *> m_Models;

	vector<GL_Texture *> m_Textures;
	vector<GL_Text *> m_Labels;
	
	GL_Heightmap * heightmap;
	GL_Skybox * m_Skybox;
	
	vec4 m_SurfaceSize;
	vec2 a, b, c;

public:

	// Constructor & Deconstuctor
	GL_Renderer();	
	~GL_Renderer();
		
	// Member Functions
	GLvoid PushHeightmap(GL_Heightmap *);
	GLvoid PushAudioNode(AudioNode *);
	GLvoid PushTexture(GL_Texture *);
	GLvoid PushSkybox(GL_Skybox *);
	GLvoid PushModel(IModel *);
	GLvoid PushText(GL_Text *);
	
	GLvoid PushSurface(Surface *);
	GLvoid Prepare();
	GLvoid update();
	GLvoid render();

	GLvoid RenderTexture(GL_Texture *);
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

	GL_Heightmap * getHeightmap(){ return heightmap; }
};