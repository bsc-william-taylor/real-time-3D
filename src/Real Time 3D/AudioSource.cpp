
#include "AudioSource.h"

AudioSource::AudioSource()
{
    translateVector = BASS_3DVECTOR(0, 0, 0);
    positionVector = BASS_3DVECTOR(0, 0, 0);
    stream = NULL;

    if (!BASS_Init(-1, 44100, BASS_DEVICE_3D, NULL, NULL))
    {
        std::cout << "Failed to init BASS" << std::endl;
    }
}

AudioSource::~AudioSource()
{
    BASS_Free();
}

void AudioSource::play(const std::string& filename)
{
    stream = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, FALSE, BASS_SAMPLE_3D);

    BASS_ChannelPlay(stream, FALSE);
}

void AudioSource::position(const BASS_3DVECTOR position)
{
    positionVector = BASS_3DVECTOR(position);
    BASS_3DVECTOR newPosition = position;
    newPosition.x += translateVector.x;
    newPosition.y += translateVector.y;
    newPosition.z += translateVector.z;

    BASS_ChannelSet3DPosition(stream, &(newPosition), NULL, NULL);
    BASS_Apply3D();
}

void AudioSource::updatePosition()
{
    position(positionVector);
}

void AudioSource::pause()
{
    BASS_ChannelPause(stream);
}

void AudioSource::stop()
{
    BASS_ChannelStop(stream);
}

void AudioSource::resetPosition()
{
    this->translateVector = BASS_3DVECTOR(0, 0, 0);
}

void AudioSource::translate(const BASS_3DVECTOR translate)
{
    this->translateVector = translate;
}

BASS_3DVECTOR AudioSource::getTranslate()
{
    return(translateVector);
}

BASS_3DVECTOR AudioSource::getPosition()
{
    return(positionVector);
}