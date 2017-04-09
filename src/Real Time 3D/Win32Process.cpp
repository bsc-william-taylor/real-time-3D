
#include "Win32Process.h"

CRITICAL_SECTION * Win32Process::g_Section = NULL;
UINT Win32Process::ThreadCount = NULL;

DWORD WINAPI Win32Process::ThreadProc(LPVOID data)
{
	Win32Process * Process = static_cast<Win32Process *>(data);
	Process->VOnInit();

	while(Process->VRunning())
	{
		while(!Process->VFinished())
		{
			Process->VOnUpdate();
		}
	}

	Process->VOnAbort();
	return NULL;
}

Win32Process::Win32Process()
{
	if(g_Section == NULL)
	{
		g_Section = new CRITICAL_SECTION();
		InitializeCriticalSection((&*g_Section));
	}

	ThreadCount++;
}

void Win32Process::TaskFinished()
{
	Completed = true;
}

bool Win32Process::VFinished()
{
	return Completed;
}

void Win32Process::StartProcess()
{
	ThreadHandle = CreateThread(NULL, 0, &ThreadProc, this, 0, NULL);
	Completed = false;

	SetThreadPriority(ThreadHandle, THREAD_PRIORITY_NORMAL);
}

void Win32Process::Unlock()
{
	LeaveCriticalSection(&*Win32Process::g_Section);
}

void Win32Process::Lock()
{
	EnterCriticalSection(&*Win32Process::g_Section);
}

void Win32Process::BreakProcess()
{
	TerminateThread(ThreadHandle, NULL);
	ThreadCount--;
}

Win32Process::~Win32Process()
{
	BreakProcess();
	if(ThreadCount == 0)
	{
		DeleteCriticalSection(g_Section);
		g_Section = NULL;
	}
}