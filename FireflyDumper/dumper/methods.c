

#include <string.h>
#include <stdbool.h>
#include "methods.h"
#include "fields.h"

const char* short_type_name(Il2CppType* type) {
    return convert_primitive_types(Il2CppFunctions_t.type_get_name(type));
}

void dump_methods(Il2CppClass* class, FILE* f) {
    MethodInfo* method;
    void* iter = 0;

    while ((method = Il2CppFunctions_t.class_get_methods(class, &iter))) {
        const char* name = Il2CppFunctions_t.method_get_name(method);
        const char* full_type_name = convert_primitive_types(
                Il2CppFunctions_t.type_get_name(
                        Il2CppFunctions_t.method_get_return_type(method)));

        const char* dot = strrchr(full_type_name, '.');
        const char* type_name = dot ? dot + 1 : full_type_name;

        fprintf(f, "\t%s %s(", type_name, name);
        bool first = true;

        int i;
        for (i = 0; i < Il2CppFunctions_t.method_get_param_count(method); i++) {
            Il2CppType* param = Il2CppFunctions_t.method_get_param(method, i);
            if (!first) {
                fprintf(f, ", ");
            }
            fprintf(f, "%s param%i", short_type_name(param), i);
            first = false;
        }
        fprintf(f, ") { } // RVA 0x%lX\n", (unsigned long) method_get_relative_pointer(method));
        fflush(f);
    }
}