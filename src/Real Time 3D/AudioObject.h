
#pragma once

#include "AudioSource.h"
#include "AudioNode.h"

class AudioObject
{
    AudioSource audioSource;
    AudioNode audioNode;

    std::string filename;
public:
    AudioObject();
    ~AudioObject();

    void setAudioSource(const char*);
    void setPosition(vec3);
    void renderNode();
    void pause();
    void play();

    AudioSource* getSource();
    AudioNode* getNode();
};