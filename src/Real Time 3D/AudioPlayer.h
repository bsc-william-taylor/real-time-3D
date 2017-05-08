
#pragma once

#include "AudioObject.h"
#include "RendererGL.h"
#include "Camera.h"

class AudioPlayer
{
    std::vector<AudioObject*> playables;
    RendererGL* renderer;
    Camera* camera;
public:
    AudioPlayer();
    ~AudioPlayer();

    void set3DRenderer(RendererGL*);
    void set3DCamera(Camera*);
    void pushClip(AudioObject*);
    void popClip(AudioObject*);
    void initialise();
    void stream();
};