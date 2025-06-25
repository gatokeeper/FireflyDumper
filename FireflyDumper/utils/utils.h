

#ifndef ASTROLABE_UTILS_H
#define ASTROLABE_UTILS_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "../api/il2cpp_api_functions.h."

char* decimal_to_hex_str(uint32_t tok);
char* convert_generic_type(const char* input);
const char* extract_property_name(const char* backing_field_name);
char* il2cpp_string_to_utf8(Il2CppString* str);
char* strremove(char* str, const char* sub);
const char* get_field_flags(FieldInfo* field, char* out_buf, size_t buf_size);
bool UnboxIl2CppField(Il2CppClass* class, const char* type_name, char* flags_buf, const char* name, const char* data, char* tok, FILE* f);
const char* convert_primitive_types(const char* type_name);

#endif //ASTROLABE_UTILS_H
