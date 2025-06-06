

#include <stdio.h>
#include "../api/il2cpp_api_functions.h"

#ifndef ASTROLABE_FIELDS_H
#define ASTROLABE_FIELDS_H

const char* convert_primitive_types(const char* type_name);
void dump_fields(Il2CppClass* class, FILE* f);

#endif //ASTROLABE_FIELDS_H
