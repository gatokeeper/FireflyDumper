#ifndef PATTERNSCAN_MEM_H
#define PATTERNSCAN_MEM_H

#include <stdint.h>

#define SCAN_GA(pattern) scan(get_game_base(), get_game_size(), pattern)
#define SCAN_UP(pattern) scan(get_player_base(), get_player_size(), pattern)

uintptr_t scan(uintptr_t start, uintptr_t length, const char* pattern);
uintptr_t get_game_base();
uintptr_t get_game_size();
uintptr_t get_player_base();
uintptr_t get_player_size();
uintptr_t safe_scan(uintptr_t base, size_t size, const char* pattern);

#endif //PATTERNSCAN_MEM_H