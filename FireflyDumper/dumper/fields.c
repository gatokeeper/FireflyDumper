

#include <string.h>
#include "fields.h"
#include "../entry.h"

const char* convert_primitive_types(const char* type_name) {
    if (strcmp(type_name, "System.Boolean") == 0) {
        return "bool";
    }
    if (strcmp(type_name, "System.String") == 0) {
        return "string";
    }
    if (strcmp(type_name, "System.String[]") == 0) {
        return "string[]";
    }
    if (strcmp(type_name, "System.Void") == 0) {
        return "void";
    }
    if (strcmp(type_name, "System.Byte") == 0) {
        return "byte";
    }
    if (strcmp(type_name, "System.Byte[]") == 0) {
        return "byte[]";
    }
    if (strcmp(type_name, "System.SByte") == 0) {
        return "sbyte";
    }
    if (strcmp(type_name, "System.Char") == 0) {
        return "char";
    }
    if (strcmp(type_name, "System.Decimal") == 0) {
        return "decimal";
    }
    if (strcmp(type_name, "System.Double") == 0) {
        return "double";
    }
    if (strcmp(type_name, "System.Single") == 0) {
        return "float";
    }
    if (strcmp(type_name, "System.Int32") == 0) {
        return "int";
    }
    if (strcmp(type_name, "System.UInt32") == 0) {
        return "uint";
    }
    if (strcmp(type_name, "System.IntPtr") == 0) {
        return "nint";
    }
    if (strcmp(type_name, "System.UIntPtr") == 0) {
        return "nuint";
    }
    if (strcmp(type_name, "System.Int64") == 0) {
        return "long";
    }
    if (strcmp(type_name, "System.UInt64") == 0) {
        return "ulong";
    }
    if (strcmp(type_name, "System.Int16") == 0) {
        return "short";
    }
    if (strcmp(type_name, "System.UInt16") == 0) {
        return "ushort";
    }

    // Arrays
    if (strcmp(type_name, "System.Boolean[]") == 0) {
        return "bool[]";
    }
    if (strcmp(type_name, "System.Char[]") == 0) {
        return "char[]";
    }
    if (strcmp(type_name, "System.Byte[]") == 0) {
        return "byte[]";
    }
    if (strcmp(type_name, "System.SByte[]") == 0) {
        return "sbyte[]";
    }
    if (strcmp(type_name, "System.String[]") == 0) {
        return "string[]";
    }
    if (strcmp(type_name, "System.Decimal[]") == 0) {
        return "decimal[]";
    }
    if (strcmp(type_name, "System.Double[]") == 0) {
        return "double[]";
    }
    if (strcmp(type_name, "System.Single[]") == 0) {
        return "float[]";
    }
    if (strcmp(type_name, "System.Int32[]") == 0) {
        return "int[]";
    }
    if (strcmp(type_name, "System.UInt32[]") == 0) {
        return "uint[]";
    }
    if (strcmp(type_name, "System.IntPtr[]") == 0) {
        return "nint[]";
    }
    if (strcmp(type_name, "System.UIntPtr[]") == 0) {
        return "nuint[]";
    }
    if (strcmp(type_name, "System.Int64[]") == 0) {
        return "long[]";
    }
    if (strcmp(type_name, "System.UInt64[]") == 0) {
        return "ulong[]";
    }
    if (strcmp(type_name, "System.Int16[]") == 0) {
        return "short[]";
    }
    if (strcmp(type_name, "System.UInt16[]") == 0) {
        return "ushort[]";
    }

    return type_name;
}

const char* get_field_flags(FieldInfo* field, char* out_buf, size_t buf_size) {
    uint32_t attrs = Il2CppFunctions_t.field_get_flags(field);
    uint32_t access = attrs & FIELD_ATTRIBUTE_FIELD_ACCESS_MASK;

    out_buf[0] = '\0';

    switch (access) {
        case FIELD_ATTRIBUTE_PRIVATE:
            strncat(out_buf, "private ", buf_size - strlen(out_buf) - 1);
            break;
        case FIELD_ATTRIBUTE_PUBLIC:
            strncat(out_buf, "public ", buf_size - strlen(out_buf) - 1);
            break;
        case FIELD_ATTRIBUTE_FAMILY:
            strncat(out_buf, "protected ", buf_size - strlen(out_buf) - 1);
            break;
        case FIELD_ATTRIBUTE_ASSEMBLY:
        case FIELD_ATTRIBUTE_FAM_AND_ASSEM:
            strncat(out_buf, "internal ", buf_size - strlen(out_buf) - 1);
            break;
        case FIELD_ATTRIBUTE_FAM_OR_ASSEM:
            strncat(out_buf, "protected internal ", buf_size - strlen(out_buf) - 1);
            break;
    }

    if (attrs & FIELD_ATTRIBUTE_LITERAL) {
        strncat(out_buf, "const ", buf_size - strlen(out_buf) - 1);
    } else {
        if (attrs & FIELD_ATTRIBUTE_STATIC) {
            strncat(out_buf, "static ", buf_size - strlen(out_buf) - 1);
        }
        if (attrs & FIELD_ATTRIBUTE_INIT_ONLY) {
            strncat(out_buf, "readonly ", buf_size - strlen(out_buf) - 1);
        }
    }

    return out_buf;
}

FieldInfo* GetFieldFromHandle(FieldInfo* field) {
    typedef FieldInfo* (*GetFieldFromHandle_t)(FieldInfo* field);
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.GetFieldFromHandle;
    GetFieldFromHandle_t GetFieldFromHandlePtr = (GetFieldFromHandle_t)rva;
    return GetFieldFromHandlePtr(field);
}

Il2CppObject* GetRawConstantValue(ReflectionFieldInfo* field) {
    typedef Il2CppObject *(*GetRawConstantValue_t)(Il2CppReflectionField* field);
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.GetRawConstantValue;
    GetRawConstantValue_t GetRawConstantValuePtr = (GetRawConstantValue_t)rva;
    ReflectionFieldInfo* field_info = GetFieldFromHandle(field);
   return GetRawConstantValuePtr(field_info);
}

bool UnboxIl2CppField(
        Il2CppClass* class,
        const char* type_name,
        char* flags_buf,
        const char* name,
        const char* data,
        FILE* f
) {
    if (strcmp(type_name, "int") == 0 || strcmp(type_name, "uint") == 0) {
        int val = *(int*)data;
        fprintf(f, "\t%s%s %s = %d; Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "long") == 0 || strcmp(type_name, "ulong") == 0) {
        long long val = *(long long*)data;
        fprintf(f, "\t%s%s %s = %lld; Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "float") == 0) {
        float val = *(float*)data;
        fprintf(f, "\t%s%s %s = %g; Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "double") == 0) {
        double val = *(double*)data;
        fprintf(f, "\t%s%s %s = %g; Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (Il2CppFunctions_t.class_is_enum(class)) {
        int val = *(int*)data;
        fprintf(f, "\t%s%s %s = %d; Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;
    } else return false;
}

void dump_fields(Il2CppClass* class, FILE* f) {
    FieldInfo* field;
    void* iter = 0;

    while ((field = Il2CppFunctions_t.class_get_fields(class, &iter))) {
        const char* name = Il2CppFunctions_t.field_get_name(field);
        const char* full_type_name = convert_primitive_types(
                Il2CppFunctions_t.type_get_name(
                        Il2CppFunctions_t.field_get_type(field)));

        const char* dot = strrchr(full_type_name, '.');
        const char* type_name = dot ? dot + 1 : full_type_name;
        size_t offset = Il2CppFunctions_t.field_get_offset(field);

        char flags_buf[128];
        get_field_flags(field, flags_buf, sizeof(flags_buf));

        if (strstr(flags_buf, "const") &&
        Il2CppRVAOffsets_t.GetRawConstantValue != 0 &&
        Il2CppRVAOffsets_t.GetFieldFromHandle != 0) {

            Il2CppObject* value = GetRawConstantValue(field);
            char* raw_data = (char*)value + 16;

            if (!UnboxIl2CppField(class, type_name, flags_buf, name, raw_data, f)) {
                fprintf(f, "\t%s%s %s; // Token: 0x0000000\n", flags_buf, type_name, name);
                continue;
            }
        } else {
            fprintf(f, "\t%s%s %s; // Offset: 0x%llX Token: 0x0000000\n", flags_buf, type_name, name, offset);
        }
        fflush(f);
    }
}
