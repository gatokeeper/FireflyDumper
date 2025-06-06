#include <windows.h>
#include <stdio.h>
#include <excpt.h>

#include "entry.h"
#include "utils/logger.h"
#include "api/il2cpp_api_functions.h"
#include "dumper/domain.h"

Settings settings = {0};

// imsory
static const uintptr_t ida_image_base = 0x180000000;
static const uintptr_t il2cpp_init_addr = 0x181EBA108;

DWORD MainThread(LPVOID hMod) {
    FILE *fptr = fopen("dump.cs", "w");

    memset(&settings, 0, sizeof(settings));
    logger_init();
    logger_info("Hello :3");

    char buffer[256];
    int loaded_modules = 0; // bool, lazy

    while (true) {
        settings.ga = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        settings.up = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
        settings.il2cpp_init = settings.up + (il2cpp_init_addr - ida_image_base);
        il2cpp_functions_init(settings.il2cpp_init);


        if (settings.ga && settings.up && settings.il2cpp_init && loaded_modules == 0) {
            snprintf(buffer, sizeof(buffer), "GameAssembly.dll base address: 0x%p", (void*)settings.ga);
            logger_info(buffer);

            snprintf(buffer, sizeof(buffer), "UnityPlayer.dll base address: 0x%p", (void*)settings.up);
            logger_info(buffer);

            snprintf(buffer, sizeof(buffer), "il2cpp_init: 0x%p", (void*)settings.il2cpp_init);
            logger_info(buffer);

            Sleep(10000);
            dump_domain(fptr);
            break;
        }

        Sleep(10000);
    }
    return 0;
}



