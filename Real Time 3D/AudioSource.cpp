
#include "AudioSource.h"

using std::string;
using std::cout;
using std::endl;


AudioSource::AudioSource()
{
	m_pTranslate = BASS_3DVECTOR(0, 0, 0);
	m_pPosition = BASS_3DVECTOR(0, 0, 0);
	m_Stream = NULL;

	if(!BASS_Init(-1, 44100, BASS_DEVICE_3D, NULL, NULL))
	{
		cout << "Failed to init BASS" << endl;
	}
}

AudioSource::~AudioSource()
{
	BASS_Free();
}

void AudioSource::Play(const std::string& filename)
{
	m_Stream = BASS_StreamCreateFile(FALSE, filename.c_str(), 0, FALSE, BASS_SAMPLE_3D);

	BASS_ChannelPlay(m_Stream, FALSE);
}

void AudioSource::Position(const BASS_3DVECTOR position)
{
	m_pPosition = BASS_3DVECTOR(position);

	BASS_3DVECTOR NewPosition = m_pPosition;
	NewPosition.x += m_pTranslate.x;
	NewPosition.y += m_pTranslate.y;
	NewPosition.z += m_pTranslate.z;

	BASS_ChannelSet3DPosition(m_Stream, &(NewPosition),  NULL,  NULL);
	BASS_Apply3D();
}

void AudioSource::UpdatePosition()
{
	Position(this->m_pPosition);
}

void AudioSource::Pause()
{
	BASS_ChannelPause(m_Stream);
}

void AudioSource::Stop()
{
	BASS_ChannelStop(m_Stream);
}

void AudioSource::ResetPosition()
{
	m_pTranslate = BASS_3DVECTOR(0, 0, 0);
}

void AudioSource::Translate(const BASS_3DVECTOR translate)
{
	this->m_pTranslate = translate;
}

BASS_3DVECTOR AudioSource::getTranslate()
{
	return(this->m_pTranslate);
}

BASS_3DVECTOR AudioSource::getPosition()
{
	return(this->m_pPosition);
}