
/* -------------------------------------------------
  
 @Filename  : Win32Timer.h
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: A simple timer class

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"

enum class TimeType 
{
	SECONDS,
	MS,
	NS
};

class Win32Timer
{
private:

	LARGE_INTEGER m_current;
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_stop;
	LARGE_INTEGER m_freq;

public:
	
	Win32Timer();
	~Win32Timer();

	float Difference(TimeType);
	float Elapsed(TimeType);

	void Start();
	void Stop();

	LONGLONG Current();

private:

	void Query(LARGE_INTEGER&);
};