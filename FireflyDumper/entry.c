#include <windows.h>
#include <stdio.h>
#include <excpt.h>
#include <psapi.h>

#include "entry.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "dumper/domain.h"
#include "utils/mem.h"

#pragma comment(lib, "psapi.lib")

Settings settings = {0};

void GetCurTime(char* out, size_t out_size) {
    SYSTEMTIME t;
    GetLocalTime(&t);
    snprintf(out, out_size, "%04d-%02d-%02d %02d:%02d:%02d",
            t.wYear, t.wMonth, t.wDay,
            t.wHour, t.wMinute, t.wSecond);
}


// github.com/kitkat033/kitkat-multiverse/blob/main/starkat/sharpkat/entry.cpp
uintptr_t ExtractQwordTarget(uintptr_t instruction_address) {
    int32_t relative_offset = *(int32_t*)(instruction_address + 3);
    uintptr_t next_instruction = instruction_address + 7;
    uintptr_t target_address = next_instruction + relative_offset;
    return target_address;
}

uintptr_t get_il2cpp_init() {
    uintptr_t out = SCAN_UP("48 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? FF D0");

    if (out != 0) {
        out = ExtractQwordTarget(out);
    }
    return out;
}

DWORD MainThread(LPVOID hMod) {
    FILE* f = fopen("dump.cs", "w");
    char buff[100];
    GetCurTime(buff, sizeof(buff));
    fprintf(f, "// Firefly Dumper | %s\n// by gato, do not redistribute :3\n\n", buff);

    memset(&settings, 0, sizeof(settings));
    logger_init();
    logger_info("Heya :3");
    SetConsoleTitle("FireflyDumper by gato :3");

    while (true) {
        settings.ga = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
        settings.up = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");
        settings.il2cpp_init = get_il2cpp_init();
        VirtualProtect((LPVOID)settings.ga, get_game_size(), PAGE_EXECUTE_READWRITE, NULL);
        il2cpp_functions_init(settings.il2cpp_init);
        il2cpp_rva_offsets_init();

        if (settings.ga && settings.up && settings.il2cpp_init) {
            logger_infof("GameAssembly.dll base address: 0x%llX", (uintptr_t)settings.ga);
            logger_infof("UnityPlayer.dll base address:  0x%llX", (uintptr_t)settings.up);
            logger_infof("il2cpp_init base address:      0x%llX", (uintptr_t)settings.il2cpp_init);
            logger_info("Waiting a few seconds before dumping...");
            Sleep(2500);
            dump_domain(f);
            break;
        }

        Sleep(10000);
    }
    return 0;
}
