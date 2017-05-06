
#pragma once

#include "AudioObject.h"
#include "RendererGL.h"
#include "ICamera.h"

class AudioPlayer
{
private:

	std::vector<AudioObject *> m_Playables;
	RendererGL * renderer;
	ICamera * m_pCamera;

public:

	AudioPlayer();
	~AudioPlayer();

	void Set3DRenderer(RendererGL *);
	void Set3DCamera(ICamera *);

	void PushClip(AudioObject *);
	void PopClip(AudioObject *);
	void Initialise();
	void Stream();
};