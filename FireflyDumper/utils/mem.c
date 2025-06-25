#include "mem.h"
#include "../entry.h"
#include <psapi.h>

uintptr_t get_game_base() {
    return settings.ga;
}

uintptr_t get_player_base() {
    return settings.up;
}

uintptr_t get_game_size() {
    HMODULE hMod = (HMODULE)get_game_base();
    if (hMod == NULL) {
        return 0;
    }

    MODULEINFO moduleInfo;
    if (GetModuleInformation(GetCurrentProcess(), hMod, &moduleInfo, sizeof(moduleInfo))) {
        return moduleInfo.SizeOfImage;
    }

    return 0;
}

uintptr_t get_player_size() {
    HMODULE hMod = (HMODULE)get_player_base();
    if (hMod == NULL) {
        return 0;
    }

    MODULEINFO moduleInfo;
    if (GetModuleInformation(GetCurrentProcess(), hMod, &moduleInfo, sizeof(moduleInfo))) {
        return moduleInfo.SizeOfImage;
    }

    return 0;
}

int string_to_byte(const char* string, uint8_t* byte) {
    if (strlen(string) != 2) return 0;

    const char char1 = (char)toupper(string[0]);
    const char char2 = (char)toupper(string[1]);

    int nibble_a = (char1 >= '0' && char1 <= '9')
                       ? char1 - '0'
                       : (char1 >= 'A' && char1 <= 'F')
                             ? 0xA + (char1 - 'A')
                             : -1;

    int nibble_b = (char2 >= '0' && char2 <= '9')
                       ? char2 - '0'
                       : (char2 >= 'A' && char2 <= 'F')
                             ? 0xA + (char2 - 'A')
                             : -1;

    *byte = ((uint8_t)nibble_a << 4) | (uint8_t)nibble_b;
    return 1;
}

uintptr_t scan_codestyle(uintptr_t start, uintptr_t length, const uint8_t* bytes, const int* mask, size_t pattern_length) {
    uintptr_t u_start = start;

    uintptr_t addr;
    for (addr = u_start; addr + pattern_length <= u_start + length; addr++) {
        int i;
        for (i = 0; i < pattern_length; i++) {
            if (mask[i] && *(uint8_t*)(addr + i) != bytes[i]) {
                break;
            }

            if (i == pattern_length - 1) {
                return addr;
            }
        }
    }
}

uintptr_t scan(uintptr_t start, uintptr_t length, const char* pattern) {
    char* dup = strdup(pattern);
    if (!dup) return 0;

    size_t max_tokens = 512;
    char* tokens[512];
    size_t token_count = 0;

    char* token = strtok(dup, " ");
    while (token && token_count < max_tokens) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }

    uint8_t* bytes = malloc(token_count);
    int* mask = malloc(token_count * sizeof(int));

    if (!bytes || !mask) {
        free(dup);
        free(bytes);
        free(mask);
        return 0;
    }

    size_t i;
    for (i = 0; i < token_count; ++i) {
        if (strcmp(tokens[i], "?") == 0 || strcmp(tokens[i], "??") == 0) {
            mask[i] = 0;
        } else {
            uint8_t b;
            if (!string_to_byte(tokens[i], &b)) {
                free(dup);
                free(bytes);
                free(mask);
                return 0;
            }
            bytes[i] = b;
            mask[i] = 1;
        }
    }

    uintptr_t result = scan_codestyle(start, length, bytes, mask, token_count);

    free(dup);
    free(bytes);
    free(mask);
    return result;
}