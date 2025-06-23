#include <string.h>
#include <stdbool.h>

#include "methods.h"
#include "fields.h"
#include "../utils/utils.h"

const char* short_type_name(Il2CppType* type) {
    return convert_generic_type(Il2CppFunctions_t.type_get_name(type));
}

void dump_methods(Il2CppClass* class, FILE* f) {
    MethodInfo* method;
    void* iter = 0;
    bool printed_constructors = false;
    bool printed_methods = false;

    while ((method = Il2CppFunctions_t.class_get_methods(class, &iter))) {
        const char* name = Il2CppFunctions_t.method_get_name(method);
        Il2CppType* ret_type = Il2CppFunctions_t.method_get_return_type(method);
        const char* type_name = short_type_name(ret_type);

        bool is_ctor = (strcmp(name, ".ctor") == 0 || strcmp(name, ".cctor") == 0);

        if (is_ctor && !printed_constructors) {
            fprintf(f, "\n\t// Constructors\n\n");
            printed_constructors = true;
        }

        if (!is_ctor && !printed_methods) {
            fprintf(f, "\t// Methods\n\n");
            printed_methods = true;
        }

        fprintf(f, "\t// RVA: 0x%lX\n", (unsigned long) method_get_relative_pointer(method));

        if (is_ctor) {
            fprintf(f, "\tvoid %s(", name);
        } else {
            fprintf(f, "\t%s %s(", type_name, name);
        }

        bool first = true;
        int i;
        for (i = 0; i < Il2CppFunctions_t.method_get_param_count(method); i++) {
            Il2CppType* param = Il2CppFunctions_t.method_get_param(method, i);
            const char* full_type_name = Il2CppFunctions_t.type_get_name(param);

            if (!first) {
                fprintf(f, ", ");
            }

            char* simplified;

            if (strchr(full_type_name, '<')) {
                simplified = (char*) short_type_name(param);
            } else {
                const char* short_name = strrchr(full_type_name, '.');
                simplified = strdup(convert_primitive_types(short_name ? short_name + 1 : full_type_name));
            }

            fprintf(f, "%s param%i", simplified, i);
            free(simplified);
            first = false;
        }
        fprintf(f, ") { }\n\n");
        fflush(f);
        free((void*)type_name);
    }
}