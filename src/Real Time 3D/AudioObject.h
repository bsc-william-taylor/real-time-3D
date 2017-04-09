
#pragma once

#include "AudioSource.h"
#include "AudioNode.h"

class AudioObject
{
private:

	AudioSource * m_pSource;
	AudioNode * m_pNode;

	const char * m_Filename;

public:

	AudioObject();
	~AudioObject();

	void SetAudioSource(const char *);
	void SetPosition(vec3);
	void RenderNode();
	void Pause();
	void Play();

	AudioSource * getSource() {
		return m_pSource;
	}

	AudioNode * getNode() {
		return m_pNode;
	}
};