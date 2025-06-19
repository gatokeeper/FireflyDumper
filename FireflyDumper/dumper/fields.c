

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
    if (strcmp(type_name, "System.Void") == 0) {
        return "void";
    }
    if (strcmp(type_name, "System.Byte") == 0) {
        return "byte";
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
        default:
            strncat(out_buf, "public ", buf_size - strlen(out_buf) - 1);
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
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.field.GetFieldFromHandle;
    GetFieldFromHandle_t GetFieldFromHandlePtr = (GetFieldFromHandle_t)rva;
    return GetFieldFromHandlePtr(field);
}

Il2CppObject* GetRawConstantValue(ReflectionFieldInfo* field) {
    typedef Il2CppObject *(*GetRawConstantValue_t)(Il2CppReflectionField* field);
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.field.GetRawConstantValue;
    GetRawConstantValue_t GetRawConstantValuePtr = (GetRawConstantValue_t)rva;
    ReflectionFieldInfo* field_info = GetFieldFromHandle(field);
    return GetRawConstantValuePtr(field_info);
}

Il2CppArray* GetCustomAttributes(FieldInfo* field, bool inherit) {
    typedef Il2CppArray* (*GetCustomAttributes_t)(ReflectionFieldInfo* fieldInfo, bool inherit);
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.field.GetCustomAttributes;
    GetCustomAttributes_t GetCustomAttributesPtr = (GetCustomAttributes_t)rva;
    ReflectionFieldInfo* field_info = GetFieldFromHandle(field);
    return GetCustomAttributesPtr(field_info, inherit);
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
        fprintf(f, "\t%s%s %s = %d; // Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "long") == 0 || strcmp(type_name, "ulong") == 0) {
        long long val = *(long long*)data;
        fprintf(f, "\t%s%s %s = %lld; // Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "float") == 0) {
        float val = *(float*)data;
        fprintf(f, "\t%s%s %s = %g; // Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "double") == 0) {
        double val = *(double*)data;
        fprintf(f, "\t%s%s %s = %g; // Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;

    } else if (Il2CppFunctions_t.class_is_enum(class)) {
        int val = *(int*)data;
        fprintf(f, "\t%s%s %s = %d; // Token: 0x0000000\n", flags_buf, type_name, name, val);
        fflush(f);
        return true;
    } else return false;
}

char* il2cpp_string_to_utf8(Il2CppString* str) {
    if (!str || str->length <= 0)
        return NULL;

    int len = str->length;
    uint16_t* utf16 = str->chars;

    int max_utf8_len = len * 3 + 1;
    char* utf8 = (char*)malloc(max_utf8_len);
    if (!utf8) return NULL;

    int pos = 0;
    int i;
    for (i = 0; i < len; i++) {
        uint16_t c = utf16[i];

        if (c < 0x80) {
            utf8[pos++] = (char)c;
        } else if (c < 0x800) {
            utf8[pos++] = 0xC0 | (c >> 6);
            utf8[pos++] = 0x80 | (c & 0x3F);
        } else {
            utf8[pos++] = 0xE0 | (c >> 12);
            utf8[pos++] = 0x80 | ((c >> 6) & 0x3F);
            utf8[pos++] = 0x80 | (c & 0x3F);
        }
    }

    utf8[pos] = '\0';
    return utf8;
}

const char* extract_property_name(const char* backing_field_name) {
    static char buf[256];

    const char* start = strchr(backing_field_name, '<');
    const char* end = strchr(backing_field_name, '>');
    if (start && end && end > start) {
        size_t len = end - start - 1;
        if (len >= sizeof(buf)) len = sizeof(buf) - 1;
        strncpy(buf, start + 1, len);
        buf[len] = '\0';
        return buf;
    }

    // empty
    return backing_field_name;
}

void dump_attribute_fields(Il2CppObject* attribute, FILE* f) {
    Il2CppClass* klass = *(Il2CppClass**)attribute;

    const char* attr_name = Il2CppFunctions_t.class_get_name(klass);

    fprintf(f, "\t[%s(", attr_name);

    void* iter = NULL;
    FieldInfo* field;
    bool first = true;
    while ((field = Il2CppFunctions_t.class_get_fields(klass, &iter))) {
        const char* raw_field_name = Il2CppFunctions_t.field_get_name(field);
        const char* field_name = extract_property_name(raw_field_name);
        Il2CppType* field_type = Il2CppFunctions_t.field_get_type(field);
        if (!field_type) {
            continue;
        }
        const char* type_name_full = Il2CppFunctions_t.type_get_name(field_type);
        const char* dot = strrchr(type_name_full, '.');
        const char* type_name = dot ? dot + 1 : type_name_full;

        size_t offset = Il2CppFunctions_t.field_get_offset(field);
        char* field_data_ptr = (char*)attribute + offset;

        if (!first) {
            fprintf(f, ", ");
        } else {
            first = false;
        }

        fprintf(f, "%s = ", field_name);

        if (strcmp(type_name, "String") == 0 || strcmp(type_name, "string") == 0 || strcmp(type_name_full, "System.String") == 0) {
            Il2CppString* str_obj = *(Il2CppString**)field_data_ptr;
            if (str_obj) {
                char* utf8_str = il2cpp_string_to_utf8(str_obj);
                fprintf(f, "\"%s\"", utf8_str);
                free(utf8_str);
            } else {
                fprintf(f, "null");
            }
        } else if (strcmp(type_name, "Boolean") == 0 || strcmp(type_name, "bool") == 0) {
            bool val = *(bool*)field_data_ptr;
            fprintf(f, "%s", val ? "true" : "false");
        } else if (strcmp(type_name, "Int32") == 0 || strcmp(type_name, "int") == 0) {
            int val = *(int*)field_data_ptr;
            fprintf(f, "%d", val);
        } else if (strcmp(type_name, "Single") == 0 || strcmp(type_name, "float") == 0) {
            float val = *(float*)field_data_ptr;
            fprintf(f, "%f", val);
        } else if (strcmp(type_name, "Double") == 0 || strcmp(type_name, "double") == 0) {
            double val = *(double*)field_data_ptr;
            fprintf(f, "%f", val);
        } else {
            // skip
        }
    }

    fprintf(f, ")]\n");
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

        Il2CppArray* attr_array = GetCustomAttributes(field, true);

        uint32_t i;
        for (i = 0; i < attr_array->max_length; i++) {
            Il2CppObject* attribute = attr_array->vector[i];
            dump_attribute_fields(attribute, f);
        }

        if (strstr(flags_buf, "const") &&
        Il2CppRVAOffsets_t.field.GetRawConstantValue != 0 &&
        Il2CppRVAOffsets_t.field.GetFieldFromHandle != 0) {

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
