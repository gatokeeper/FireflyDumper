
#include "class.h"

void get_class_modifiers(Il2CppClass* class, FILE* f) {
    uint32_t flags = Il2CppFunctions_t.class_get_flags(class);

    if (flags & TYPE_ATTRIBUTE_PUBLIC || flags & TYPE_ATTRIBUTE_NESTED_PUBLIC) {
        fprintf(f, "public ");
    } else if (flags & TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM) {
        fprintf(f, "protected internal ");
    } else if (flags & TYPE_ATTRIBUTE_NESTED_FAMILY) {
        fprintf(f, "protected ");
    } else if (flags & TYPE_ATTRIBUTE_NESTED_ASSEMBLY) {
        fprintf(f, "internal ");
    } else if (flags & TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM) {
        fprintf(f, "private protected ");
    } else if (flags & TYPE_ATTRIBUTE_NESTED_PRIVATE) {
        fprintf(f, "private ");
    }

    // Others
    if (flags & TYPE_ATTRIBUTE_ABSTRACT) {
        fprintf(f, "abstract ");
    }

    if (flags & TYPE_ATTRIBUTE_INTERFACE) {
        fprintf(f, "interface ");
    } else if (Il2CppFunctions_t.class_is_enum(class)) {
        fprintf(f, "enum ");
    } else if (Il2CppFunctions_t.class_is_valuetype(class)) {
        fprintf(f, "struct ");
    } else {
        fprintf(f, "class ");
    }
}
