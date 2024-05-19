#ifndef Timer_h
#define Timer_h

#include <windows.h>

extern void NTAPI NtSetTimerResolution(ULONG desiredResolution, BOOLEAN setResolution, PULONG currentResolution);
extern void NTAPI NtDelayExecution(BOOLEAN alertable, PLARGE_INTEGER delayInterval);

#endif