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

void GetCurTime(char* out, size_t out_size) {
    SYSTEMTIME t;
    GetLocalTime(&t);
    snprintf(out, out_size, "%04d-%02d-%02d %02d:%02d:%02d",
            t.wYear, t.wMonth, t.wDay,
            t.wHour, t.wMinute, t.wSecond);
}

DWORD MainThread(LPVOID hMod) {
    FILE *fptr = fopen("dump.cs", "w");
    char buff[100];
    GetCurTime(buff, sizeof(buff));
    fprintf(fptr, "// Firefly Dumper | %s\n// by gato, do not redistribute :3\n\n", buff);

    memset(&settings, 0, sizeof(settings));
    logger_init();
    logger_info("Heya :3");
    SetConsoleTitle("FireflyDumper by gato :3");

    char buffer[256];
    while (true) {
        settings.ga = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        settings.up = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
        settings.il2cpp_init = settings.up + (il2cpp_init_addr - ida_image_base);
        il2cpp_functions_init(settings.il2cpp_init);
        il2cpp_rva_offsets_init();

        if (settings.ga && settings.up && settings.il2cpp_init) {
            snprintf(buffer, sizeof(buffer), "GameAssembly.dll base address: 0x%llX", (uintptr_t)settings.ga);
            logger_info(buffer);

            snprintf(buffer, sizeof(buffer), "UnityPlayer.dll base address:  0x%llX", (uintptr_t)settings.up);
            logger_info(buffer);

            snprintf(buffer, sizeof(buffer), "il2cpp_init base address:      0x%llX", (uintptr_t)settings.il2cpp_init);
            logger_info(buffer);

            logger_info("Waiting a few seconds before dumping...");
            Sleep(5000);
            dump_domain(fptr);
            break;
        }

        Sleep(10000);
    }
    return 0;
}
