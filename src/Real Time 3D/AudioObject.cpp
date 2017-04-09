
#include "AudioObject.h"

using std::string;
using std::cout;
using std::endl;

AudioObject::AudioObject()
	: m_pSource(new AudioSource()),
	  m_pNode(new AudioNode()),
	  m_Filename("")
{

}

AudioObject::~AudioObject()
{

}

void AudioObject::SetAudioSource(const char * filename)
{
	m_Filename = filename;
}

void AudioObject::SetPosition(vec3 vec)
{
	BASS_3DVECTOR position;
	position.x = vec.x;
	position.y = vec.y;
	position.z = vec.z;

	m_pSource->Position(position);
	m_pNode->Initialise(vec, vec + vec3(2, 2, 2));
}

void AudioObject::RenderNode()
{
	m_pNode->Render();
}

void AudioObject::Pause()
{
	if(m_Filename != "")
	{
		m_pSource->Stop();
	}
}

void AudioObject::Play()
{
	if(m_Filename != "")
	{
		m_pSource->Play(m_Filename);
	}
}