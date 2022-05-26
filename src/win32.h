#ifndef WIN32_H
#define WIN32_H

#include <stdbool.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <mmreg.h>

#define DIRECTSOUND_VERSION 0x0300
#include <dsound.h>

typedef HRESULT(__stdcall DirectSoundCreateProc)(GUID*, LPDIRECTSOUND*, IUnknown*);

extern DirectSoundCreateProc* gDirectSoundCreateProc;
extern HWND gProgramWindow;

#endif // _WIN32

extern bool gProgramIsActive;

bool _LoadDirectX();
void _UnloadDirectX(void);

#endif /* WIN32_H */
