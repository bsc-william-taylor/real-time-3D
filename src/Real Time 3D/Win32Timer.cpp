

#include "Win32Timer.h"

Win32Timer::Win32Timer()
{
    QueryPerformanceFrequency(&freq);
    start();
    stop();
}

Win32Timer::~Win32Timer()
{
}

void Win32Timer::start()
{
    QueryPerformanceCounter(&startQuery);
}

void Win32Timer::stop()
{
    QueryPerformanceCounter(&stopQuery);
}

float Win32Timer::elapsed(TimeType type)
{
    QueryPerformanceCounter(&currentQuery);
    return(difference(type));
}

float Win32Timer::difference(TimeType type)
{
    float difference = 0.0f;

    switch (type)
    {
        case TimeType::Seconds:
        {
            difference = (float)(stopQuery.QuadPart - startQuery.QuadPart);
            break;
        }

        case TimeType::Milliseconds:
        {
            difference = (float)(1.0e3*(stopQuery.QuadPart - startQuery.QuadPart));
            break;
        }

        case TimeType::Nanoseconds:
        {
            difference = (float)(1.0e9*(stopQuery.QuadPart - startQuery.QuadPart));
            break;
        }
    };

    return(difference / freq.QuadPart);
}

LONGLONG Win32Timer::current()
{
    QueryPerformanceCounter(&currentQuery);
    return(currentQuery.QuadPart);
}