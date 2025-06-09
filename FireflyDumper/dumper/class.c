
#include "class.h"

void get_class_modifiers(Il2CppClass* class, FILE* f) {
    uint32_t flags = Il2CppFunctions_t.class_get_flags(class);

    uint32_t visibility = flags & TYPE_ATTRIBUTE_VISIBILITY_MASK;
    switch (visibility) {
        case TYPE_ATTRIBUTE_PUBLIC:
        case TYPE_ATTRIBUTE_NESTED_PUBLIC:
            fprintf(f, "public ");
            break;
        case TYPE_ATTRIBUTE_NOT_PUBLIC:
        case TYPE_ATTRIBUTE_NESTED_ASSEMBLY:
            fprintf(f, "internal ");
            break;
        case TYPE_ATTRIBUTE_NESTED_PRIVATE:
            fprintf(f, "private ");
            break;
        case TYPE_ATTRIBUTE_NESTED_FAMILY:
            fprintf(f, "protected ");
            break;
        case TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM:
            fprintf(f, "private protected ");
            break;
        case TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM:
            fprintf(f, "protected internal ");
            break;
        default:
            fprintf(f, "/* unknown visiblity type */"); // should never happen
            break;
    }
    
    if ((flags & TYPE_ATTRIBUTE_ABSTRACT) && (flags & TYPE_ATTRIBUTE_SEALED)) {
        fprintf(f, "static ");
    } else if (!(flags & TYPE_ATTRIBUTE_INTERFACE) && (flags & TYPE_ATTRIBUTE_ABSTRACT)) {
        fprintf(f, "abstract ");
    } else if (!Il2CppFunctions_t.class_is_valuetype(class) &&
               !Il2CppFunctions_t.class_is_enum(class) &&
               (flags & TYPE_ATTRIBUTE_SEALED)) {
        fprintf(f, "sealed ");
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