
#ifndef UNTITLED_ENTRY_H
#define UNTITLED_ENTRY_H

#include <windows.h>
#include <stdint.h>

typedef struct {
    uintptr_t up;
    uintptr_t ga;

    uintptr_t il2cpp_init;
    size_t class_byval;
} Settings;

extern Settings settings;

size_t brute_class_byval();
DWORD MainThread(LPVOID hMod);

#endif //UNTITLED_ENTRY_H
