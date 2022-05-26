#include "win32.h"

#include "core.h"
#include "main.h"
#include "window_manager.h"

#include <SDL.h>

#ifdef _WIN32

// 0x51E430
DirectSoundCreateProc* gDirectSoundCreateProc = NULL;

// 0x51E434
HWND gProgramWindow = NULL;

// 0x51E454
HMODULE gDSoundDLL = NULL;

#endif // _WIN32

// 0x51E444
bool gProgramIsActive = false;

// 0x4DE700
int main(int argc, char* argv[])
{
    if (GetLastError() == ERROR_SUCCESS) {
        SDL_ShowCursor(SDL_DISABLE);
        if (_LoadDirectX()) {
            gProgramIsActive = true;
            falloutMain(argc, argv);
        }
    }
    return 0;
}

// 0x4DE8D0
bool _LoadDirectX()
{
#ifdef _WIN32
    gDSoundDLL = LoadLibraryA("DSOUND.DLL");
    if (gDSoundDLL == NULL) {
        goto err;
    }

    gDirectSoundCreateProc = (DirectSoundCreateProc*)GetProcAddress(gDSoundDLL, "DirectSoundCreate");
    if (gDirectSoundCreateProc == NULL) {
        goto err;
    }

    atexit(_UnloadDirectX);

    return true;

err:
    _UnloadDirectX();
    
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could not load DirectX", "This program requires DirectX 3.0a or later.", NULL);

    return false;
#else
    return true;
#endif // _WIN32
}

// 0x4DE988
void _UnloadDirectX(void)
{
#ifdef _WIN32
    if (gDSoundDLL != NULL) {
        FreeLibrary(gDSoundDLL);
        gDSoundDLL = NULL;
    }
#endif // _WIN32
}
