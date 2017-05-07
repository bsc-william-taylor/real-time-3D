
#pragma once

#include "include/bass/bass.h"
#include <iostream>
#include <string>

#pragma comment(lib, "lib/bass/bass.lib")

class AudioSource
{
	BASS_3DVECTOR translateVector;
	BASS_3DVECTOR positionVector;
	HSTREAM stream;
public:
	AudioSource();
	~AudioSource();

	void translate(const BASS_3DVECTOR);
	void position(const BASS_3DVECTOR);
	void play(const std::string&);
	void updatePosition();
	void resetPosition();
	void pause();
	void stop();

	BASS_3DVECTOR getTranslate();
	BASS_3DVECTOR getPosition();
};