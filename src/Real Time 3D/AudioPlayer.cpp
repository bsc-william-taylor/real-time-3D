
#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	renderer = NULL;
	m_pCamera = NULL;
}

AudioPlayer::~AudioPlayer()
{
	m_pCamera = NULL;
}

void AudioPlayer::Set3DCamera(ICamera * camera)
{
	m_pCamera = camera;
}

void AudioPlayer::PushClip(AudioObject * source)
{
	m_Playables.push_back(source);
}

void AudioPlayer::PopClip(AudioObject * source)
{
	std::remove(m_Playables.begin(), m_Playables.end(), source);
}

void AudioPlayer::Set3DRenderer(GL_Renderer * renderer)
{
	this->renderer = renderer;
}

void AudioPlayer::Initialise()
{
	BASS_SetVolume(1.0f);

	unsigned int size = m_Playables.size();
	
	for(unsigned i = 0; i < size; i++)
	{
		renderer->PushAudioNode(m_Playables[i]->getNode());	
	}
}

void AudioPlayer::Stream()
{
	unsigned int size = m_Playables.size();
	
	for(unsigned i = 0; i < size; i++)
	{
		if(m_pCamera != NULL)
		{
			auto source = m_Playables[i]->getSource();
			vec3 vec = m_pCamera->getPosition();
			
			BASS_3DVECTOR p = BASS_3DVECTOR(vec.x, vec.y, vec.z);
			
			source->Translate(p);
			source->UpdatePosition();
		}
	}
}