
#pragma once

#include "Win32Header.h"

enum class TimeType 
{
	Seconds,
	Milliseconds,
	Nanoseconds
};

class Win32Timer
{
	LARGE_INTEGER currentQuery;
	LARGE_INTEGER startQuery;
	LARGE_INTEGER stopQuery;
	LARGE_INTEGER freq;
public:
	Win32Timer();
	~Win32Timer();

	float difference(TimeType);
	float elapsed(TimeType);

	void start();
	void stop();

	LONGLONG current();
};