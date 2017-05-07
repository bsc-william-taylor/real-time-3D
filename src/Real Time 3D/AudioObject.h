
#pragma once

#include "AudioSource.h"
#include "AudioNode.h"

class AudioObject
{
	AudioSource audioSource;
	AudioNode audioNode;

	const char* filename;
public:
	AudioObject();
	~AudioObject();

	void SetAudioSource(const char *);
	void SetPosition(vec3);
	void RenderNode();
	void pause();
	void play();

	AudioSource * getSource();
	AudioNode * getNode();
};