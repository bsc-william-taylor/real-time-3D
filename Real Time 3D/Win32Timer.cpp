
/* -------------------------------------------------
  
 @Filename  : Win32Timer.cpp
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: class implementation

 ------------------------------------------------- */

#include "Win32Timer.h"

Win32Timer::Win32Timer( )
{
  // Grab frequency of this processor
  QueryPerformanceFrequency(&m_freq);

  // Setup initial times
  Start();
  Stop();
}

Win32Timer::~Win32Timer()
{
}

// Records current time in start variable
void Win32Timer::Start()
{
	QueryPerformanceCounter(&m_start);
}

// Records current time in stop variable
void Win32Timer::Stop()
{
	QueryPerformanceCounter(&m_stop);
}

// Get current time from previous Start call
float Win32Timer::Elapsed(TimeType type)
{
	QueryPerformanceCounter(&m_current);
	return(Difference(type));
}

// Time between last Start and Stop calls
float Win32Timer::Difference(TimeType type)
{
	float difference = 0.0f;
	
	switch(type)
	{
		case TimeType::SECONDS:
		{
			difference = (float)(m_stop.QuadPart - m_start.QuadPart); 
			break;
		}
		
		case TimeType::MS:
		{
			difference = (float)(1.0e3*(m_stop.QuadPart - m_start.QuadPart));
			break;
		}
	
		case TimeType::NS:
		{
			difference = (float)(1.0e9*(m_stop.QuadPart - m_start.QuadPart));
			break;
		}
	};

	return(difference / m_freq.QuadPart);
}

// Get the current clock count
LONGLONG Win32Timer::Current()
{
	QueryPerformanceCounter(&m_current);
	return(m_current.QuadPart);
}