#include <string.h>
#include <stdbool.h>

#include "methods.h"
#include "fields.h"
#include "../utils/utils.h"
#include "../entry.h"

const char* short_type_name(Il2CppType* type) {
    return convert_generic_type(Il2CppFunctions.type_get_name(type));
}

void dump_methods(Il2CppClass* class, FILE* f) {
    MethodInfo* method;
    void* iter = 0;
    bool printed_constructors = false;
    bool printed_methods = false;

    while ((method = Il2CppFunctions.class_get_methods(class, &iter))) {
        const char* name = Il2CppFunctions.method_get_name(method);
        Il2CppType* type = Il2CppFunctions.method_get_return_type(method);
        const char* type_name = short_type_name(type);

        bool is_ctor = (strcmp(name, ".ctor") == 0 || strcmp(name, ".cctor") == 0);

        if (is_ctor && !printed_constructors) {
            fprintf(f, "\n\t// Constructors\n");
            printed_constructors = true;
        }

        if (!is_ctor && !printed_methods) {
            fprintf(f, "\t// Methods\n");
            printed_methods = true;
        }

        fprintf(f, "\t// RVA: 0x%lX\n", (unsigned long) method_get_relative_pointer(method));

        if (is_ctor) {
            fprintf(f, "\tvoid %s(", name);
        } else {
            if (strchr(type_name, '<')) {
                fprintf(f, "\t%s %s(", type_name, name);
            } else {
                const char* prim = convert_primitive_types(type_name);
                const char* dot = strrchr(prim, '.');
                dot = dot ? dot + 1 : prim;
                fprintf(f, "\t%s %s(", dot, name);
            }
        }

        bool first = true;
        int i;
        for (i = 0; i < Il2CppFunctions.method_get_param_count(method); i++) {
            Il2CppType* param = Il2CppFunctions.method_get_param(method, i);
            const char* full_type_name = Il2CppFunctions.type_get_name(param);

            if (!first) {
                fprintf(f, ", ");
            }

            if (strchr(full_type_name, '<')) {
                char* generic_type = convert_generic_type(full_type_name);
                fprintf(f, "%s param%i", generic_type, i);
                free(generic_type);
            } else {
                const char* prim_type = convert_primitive_types(full_type_name);
                const char* short_name = strrchr(prim_type, '.');
                short_name = short_name ? short_name + 1 : prim_type;
                fprintf(f, "%s param%i", short_name, i);
            }

            first = false;
        }

        fprintf(f, ") { }\n\n");
        fflush(f);
    }
}