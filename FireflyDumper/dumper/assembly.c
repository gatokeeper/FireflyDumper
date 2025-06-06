#include <string.h>

#include "assembly.h"
#include "fields.h"
#include "methods.h"
#include "class.h"

void dump_assembly(FILE* f, Il2CppAssembly* assembly, int assembly_index) {
    Il2CppImage* image = Il2CppFunctions_t.assembly_get_image(assembly);
    size_t class_count = Il2CppFunctions_t.image_get_class_count(image);

    fprintf(f, "// -~starting assembly~- #%i\n", assembly_index);
    fprintf(f, "// name: %s\n", Il2CppFunctions_t.image_get_name(image));
    fprintf(f, "// class count: %zu\n", class_count);
    fprintf(f, "// starting assembly #%i\n\n", assembly_index);

    int i;
    for (i = 0; i < class_count; i++) {
        Il2CppClass* class = Il2CppFunctions_t.image_get_class(image, i);

//        const char* full_name = Il2CppFunctions_t.class_get_name(class);
        const char *full_name = Il2CppFunctions_t.type_get_name(class_get_type(class));
        const char *dot = strrchr(full_name, '.');
        const char *name = dot ? dot + 1 : full_name;
        const char *namespace = Il2CppFunctions_t.class_get_namespace(class);

        fprintf(f, "// TypeDefIndex: %i\n"
                   "// Namespace: %s\n"
                   "// FullName: %s\n"
                   "// Module: %s (%i)\n",
                i,
                (namespace[0] ? namespace : "(none)"),
                name,
                Il2CppFunctions_t.image_get_name(image),
                assembly_index
        );

        get_class_modifiers(class, f);
        fprintf(f, "%s", name);

        Il2CppClass *parent = Il2CppFunctions_t.class_get_parent(class);
        if (parent != NULL) {
            const char* name1 = Il2CppFunctions_t.class_get_name(parent);
            if (strcmp(name1, "Object") != 0) {
                fprintf(f, " : %s", name1);
            }
        }

        fprintf(f, "\n{\n");
        fprintf(f, "\t// Fields\n");
        dump_fields(class, f);

        fprintf(f, "\n\t// Methods\n");
        dump_methods(class, f);
        fprintf(f, "}\n\n");
        fflush(f);
    }
}