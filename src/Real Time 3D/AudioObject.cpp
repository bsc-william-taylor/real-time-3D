
#include "AudioObject.h"

AudioObject::AudioObject()
    : filename("")
{

}

AudioObject::~AudioObject()
{

}

void AudioObject::SetAudioSource(const char* filename)
{
    this->filename = filename;
}

void AudioObject::SetPosition(vec3 vec)
{
    BASS_3DVECTOR position;
    position.x = vec.x;
    position.y = vec.y;
    position.z = vec.z;

    audioSource.position(position);
    audioNode.initialise(vec, vec + vec3(2, 2, 2));
}

void AudioObject::RenderNode()
{
    audioNode.render();
}

void AudioObject::pause()
{
    if (filename != "")
    {
        audioSource.stop();
    }
}

void AudioObject::play()
{
    if (filename != "")
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