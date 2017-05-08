
#include "AudioObject.h"

AudioObject::AudioObject() : filename("")
{
}

AudioObject::~AudioObject()
{
}

void AudioObject::setAudioSource(const char* fn)
{
    filename = fn;
}

void AudioObject::setPosition(vec3 vec)
{
    BASS_3DVECTOR position;
    position.x = vec.x;
    position.y = vec.y;
    position.z = vec.z;

    audioSource.position(position);
    audioNode.initialise(vec, vec + vec3(2, 2, 2));
}

void AudioObject::renderNode()
{
    audioNode.render();
}

void AudioObject::pause()
{
    if (!filename.empty())
    {
        audioSource.stop();
    }
}

void AudioObject::play()
{
    if (!filename.empty())
    {
        audioSource.play(filename);
    }
}

AudioSource* AudioObject::getSource()
{
    return &audioSource;
}

AudioNode* AudioObject::getNode()
{
    return &audioNode;
}