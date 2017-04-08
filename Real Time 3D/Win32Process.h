
#include "Win32Header.h"

#define THREADPROC DWORD WINAPI

class Win32Process
{
	private:

		static THREADPROC ThreadProc(LPVOID);
		static CRITICAL_SECTION * g_Section;
		static UINT ThreadCount;

		HANDLE ThreadHandle;
		BOOL Completed;
		BOOL Continue;

	public:

	Win32Process();

		void StartProcess(;
		void TaskFinished();
		void BreakProcess();
		void Unlock();
		void Lock();

		bool VFinished();

		virtual void VOnUpdate() = 0;
		virtual bool VRunning() = 0;
		virtual void VOnAbort() = 0;
		virtual void VOnInit() = 0;
	
	~Win32Process();
};