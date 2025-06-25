#include "./utils/logger.h"
#include <windows.h>
#include "entry.h"

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        logger_init();
        CreateThread(NULL, 0, MainThread, hInstance, 0, NULL);
    }

    return TRUE;
}
