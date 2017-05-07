
#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
    renderer = nullptr;
    camera = nullptr;
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::set3DCamera(Camera * camera)
{
    this->camera = camera;
}

void AudioPlayer::pushClip(AudioObject * source)
{
    playables.push_back(source);
}

void AudioPlayer::popClip(AudioObject* source)
{
    auto it = std::find(playables.begin(), playables.end(), source);

    if (it != playables.end())
    {
        playables.erase(it);
    }
}

void AudioPlayer::set3DRenderer(RendererGL * renderer)
{
    this->renderer = renderer;
}

void AudioPlayer::initialise()
{
    BASS_SetVolume(1.0f);

    for (auto i = 0; i < playables.size(); i++)
    {
        renderer->pushAudioNode(playables[i]->getNode());
    }
}

void AudioPlayer::stream()
{
    for (auto i = 0; i < playables.size(); i++)
    {
        if (camera != nullptr)
        {
            auto source = playables[i]->getSource();
            auto vector = camera->getPosition();

            source->translate({ vector.x, vector.y, vector.z });
            source->updatePosition();
        }
    }
}