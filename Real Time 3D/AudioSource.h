
#pragma once

#include "AudioHeader.h"

class AudioSource
{
private:

	BASS_3DVECTOR m_pTranslate;
	BASS_3DVECTOR m_pPosition;
	HSTREAM m_Stream;

public:

	AudioSource();
	~AudioSource();

	void Translate(const BASS_3DVECTOR);
	void Position(const BASS_3DVECTOR);
	void Play(const std::string&);
	void UpdatePosition();
	void ResetPosition();
	void Pause();
	void Stop();

	BASS_3DVECTOR getTranslate();
	BASS_3DVECTOR getPosition();
};