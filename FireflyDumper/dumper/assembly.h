

#include <stdio.h>
#include "../api/il2cpp_api_functions.h"

#ifndef ASTROLABE_ASSEMBLY_H
#define ASTROLABE_ASSEMBLY_H

char* strremove(char* str, const char* sub);
void dump_assembly(FILE* f, Il2CppAssembly* assembly, int assembly_index);

#endif //ASTROLABE_ASSEMBLY_H
