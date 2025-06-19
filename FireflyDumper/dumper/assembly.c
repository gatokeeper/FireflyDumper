#include <string.h>

#include "assembly.h"
#include "fields.h"
#include "methods.h"
#include "class.h"

// stack overflow 💗
char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            memmove(q, p, r - p);
            q += r - p;
        }
        memmove(q, p, strlen(p) + 1);
    }
    return str;
}

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

        const char* full_name = Il2CppFunctions_t.type_get_name(class_get_type(class));
        const char* dot = strrchr(full_name, '.');
        const char* name = dot ? dot + 1 : full_name;
        const char* namespace = Il2CppFunctions_t.class_get_namespace(class);

        fprintf(f, "// TypeDefIndex: %i\n"
                   "// Module: %s (%i)\n"
                   "// FullName: %s\n"
                   "// Namespace: %s\n",
                i,
                Il2CppFunctions_t.image_get_name(image),
                assembly_index,
                full_name,
                (namespace[0] ? namespace : "(none)")
        );

        get_class_modifiers(class, f);
        fprintf(f, "%s", name);

        bool is_first_interface = true;
        Il2CppClass *parent = Il2CppFunctions_t.class_get_parent(class);
        if (parent != NULL) {
            const char* name1 = Il2CppFunctions_t.class_get_name(parent);
            if (strcmp(name1, "Object") != 0) {
                fprintf(f, " : %s", name1);
                is_first_interface = false;
            }
        }

        Il2CppClass* interface;
        void* iter = NULL;

        while ((interface = Il2CppFunctions_t.class_get_interfaces(class, &iter))) {
            const char* full = Il2CppFunctions_t.type_get_name(class_get_type(interface));
            
            char buffer[100];
            if (strcmp(namespace, "") != 0) {
                snprintf(buffer, sizeof(buffer), "%s.", namespace);
            }

            const char* name1 = strremove((char*)full, (const char*)buffer);
            const char* dot1 = strrchr(name1, '.');
            const char* name2 = dot1 ? dot1 + 1 : name1;

            if (strcmp(name1, "Object") != 0) {
                if (is_first_interface == true) {
                    fprintf(f, " : %s", name2);
                    is_first_interface = false;
                } else {
                    fprintf(f, ", %s", name2);
                }
            }
        }

        fprintf(f, "\n{\n");
        fprintf(f, "\t// Fields\n");
        dump_fields(class, f);
        
        dump_methods(class, f);
        fprintf(f, "}\n\n");
        fflush(f);
    }
}