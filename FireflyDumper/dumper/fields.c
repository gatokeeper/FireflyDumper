

#include <string.h>
#include "fields.h"
#include "../entry.h"
#include "../utils/utils.h"

FieldInfo* GetFieldFromHandle(FieldInfo* field) {
    typedef FieldInfo* (*GetFieldFromHandle_t)(FieldInfo* field);
    uintptr_t rva = ReflectionOffsets.field.GetFieldFromHandle;
    GetFieldFromHandle_t ptr = (GetFieldFromHandle_t)rva;
    return ptr(field);
}

Il2CppObject* GetRawConstantValue(ReflectionFieldInfo* field) {
    typedef Il2CppObject *(*GetRawConstantValue_t)(Il2CppReflectionField* field);
    uintptr_t rva = ReflectionOffsets.field.GetRawConstantValue;
    GetRawConstantValue_t ptr = (GetRawConstantValue_t)rva;
    ReflectionFieldInfo* field_info = GetFieldFromHandle(field);
    return ptr(field_info);
}

Il2CppArray* GetCustomAttributes(FieldInfo* field, bool inherit) {
    typedef Il2CppArray* (*GetCustomAttributes_t)(ReflectionFieldInfo* fieldInfo, bool inherit);
    uintptr_t rva = ReflectionOffsets.field.GetCustomAttributes;
    GetCustomAttributes_t ptr = (GetCustomAttributes_t)rva;
    ReflectionFieldInfo* field_info = GetFieldFromHandle(field);
    return ptr(field_info, inherit);
}

uint32_t get_MetadataToken(Il2CppObject* obj) {
    typedef uint32_t (*get_MetadataToken_t)(Il2CppObject* self);
    uintptr_t rva = ReflectionOffsets.field.get_MetadataToken;
    get_MetadataToken_t ptr = (get_MetadataToken_t)rva;
    return ptr(obj);
}

void dump_attribute_fields(Il2CppObject* attribute, FILE* f) {
    Il2CppClass* klass = *(Il2CppClass**)attribute;

    const char* attr_name = Il2CppFunctions.class_get_name(klass);

    fprintf(f, "\t[%s(", attr_name);

    void* iter = NULL;
    FieldInfo* field;
    bool first = true;
    while ((field = Il2CppFunctions.class_get_fields(klass, &iter))) {
        const char* raw_field_name = Il2CppFunctions.field_get_name(field);
        const char* field_name = extract_property_name(raw_field_name);
        Il2CppType* field_type = Il2CppFunctions.field_get_type(field);
        if (!field_type) {
            continue;
        }
        const char* type_name_full = Il2CppFunctions.type_get_name(field_type);
        const char* dot = strrchr(type_name_full, '.');
        const char* type_name = dot ? dot + 1 : type_name_full;

        size_t offset = Il2CppFunctions.field_get_offset(field);
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

    while ((field = Il2CppFunctions.class_get_fields(class, &iter))) {
        if (field != NULL && !printed_fields) {
            fprintf(f, "\t// Fields\n");
            printed_fields = true;
        }
        const char* name = Il2CppFunctions.field_get_name(field);
        const char* raw_type = Il2CppFunctions.type_get_name(
                Il2CppFunctions.field_get_type(field));
        char* full_type_name = convert_generic_type(raw_type);

        const char* dot = strrchr(full_type_name, '.');
        const char* type_name = dot ? dot + 1 : full_type_name;
        size_t offset = Il2CppFunctions.field_get_offset(field);

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
        ReflectionOffsets.field.GetRawConstantValue != 0 &&
        ReflectionOffsets.field.GetFieldFromHandle != 0) {

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
