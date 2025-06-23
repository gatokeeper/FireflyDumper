

#include <string.h>
#include "fields.h"
#include "../entry.h"
#include "../utils/utils.h"

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

bool UnboxIl2CppField(
        Il2CppClass* class,
        const char* type_name,
        char* flags_buf,
        const char* name,
        const char* data,
        char* tok,
        FILE* f
) {
    if (strcmp(type_name, "int") == 0 || strcmp(type_name, "uint") == 0) {
        int val = *(int*)data;
        fprintf(f, "\t%s%s %s = %d; // Token: %s\n", flags_buf, type_name, name, val, tok);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "long") == 0 || strcmp(type_name, "ulong") == 0) {
        long long val = *(long long*)data;
        fprintf(f, "\t%s%s %s = %lld; // Token: %s\n", flags_buf, type_name, name, val, tok);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "float") == 0) {
        float val = *(float*)data;
        fprintf(f, "\t%s%s %s = %g; // Token: %s\n", flags_buf, type_name, name, val, tok);
        fflush(f);
        return true;

    } else if (strcmp(type_name, "double") == 0) {
        double val = *(double*)data;
        fprintf(f, "\t%s%s %s = %g; // Token: %s\n", flags_buf, type_name, name, val, tok);
        fflush(f);
        return true;

    } else if (Il2CppFunctions_t.class_is_enum(class)) {
        int val = *(int*)data;
        fprintf(f, "\t%s%s %s = %d; // Token: %s\n", flags_buf, type_name, name, val, tok);
        fflush(f);
        return true;
    } else return false;
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

uint32_t get_MetadataToken(Il2CppObject* obj) {
    typedef uint32_t (*get_MetadataToken_t)(Il2CppObject* self);
    uintptr_t rva = settings.ga + Il2CppRVAOffsets_t.field.get_MetadataToken;
    get_MetadataToken_t get_MetadataTokenPtr = (get_MetadataToken_t)rva;
    return get_MetadataTokenPtr(obj);
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
    bool printed_fields = false;

    while ((field = Il2CppFunctions_t.class_get_fields(class, &iter))) {
        if (field != NULL && !printed_fields) {
            fprintf(f, "\t// Fields\n");
            printed_fields = true;
        }
        const char* name = Il2CppFunctions_t.field_get_name(field);
        const char* raw_type = Il2CppFunctions_t.type_get_name(
                Il2CppFunctions_t.field_get_type(field));
        char* full_type_name = convert_generic_type(raw_type);

        const char* dot = strrchr(full_type_name, '.');
        const char* type_name = dot ? dot + 1 : full_type_name;
        size_t offset = Il2CppFunctions_t.field_get_offset(field);

        char flags_buf[128];
        get_field_flags(field, flags_buf, sizeof(flags_buf));
        char* tok = decimal_to_hex_str((get_MetadataToken(GetFieldFromHandle(field))));

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

            if (!UnboxIl2CppField(class, type_name, flags_buf, name, raw_data, tok, f)) {
                fprintf(f, "\t%s%s %s; // Token: %s\n", flags_buf, type_name, name, tok);
                continue;
            }
        } else {
            fprintf(f, "\t%s%s %s; // Offset: 0x%llX Token: %s\n", flags_buf, type_name, name, offset, tok);
        }
        fflush(f);
        free(full_type_name);
    }
}
