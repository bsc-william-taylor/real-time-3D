
#pragma once

#include "AudioObject.h"
#include "GL_Renderer.h"
#include "ICamera.h"

class AudioPlayer
{
private:

	std::vector<AudioObject *> m_Playables;
	GL_Renderer * renderer;
	ICamera * m_pCamera;

public:

	AudioPlayer();
	~AudioPlayer();

	void Set3DRenderer(GL_Renderer *);
	void Set3DCamera(ICamera *);

	void PushClip(AudioObject *);
	void PopClip(AudioObject *);
	void Initialise();
	void Stream();
};