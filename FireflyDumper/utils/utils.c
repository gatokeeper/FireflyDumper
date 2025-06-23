

#include "utils.h"
#include "../dumper/fields.h"

char* decimal_to_hex_str(uint32_t tok) {
    static char buf[16];
    snprintf(buf, sizeof(buf), "0x%X", tok);
    return buf;
}

char* convert_generic_type(const char* input) {
    char buf[256];
    strncpy(buf, input, sizeof(buf));
    buf[sizeof(buf) - 1] = '\0';

    char* open = strchr(buf, '<');
    char* close = strchr(buf, '>');
    if (!open || !close || close < open) {
        return strdup(convert_primitive_types(input));
    }

    *open = '\0';
    *close = '\0';

    char* outer = buf;
    char* inner = open + 1;
    const char* inner_prim = convert_primitive_types(inner);

    char* outerSimple = strrchr(outer, '.');
    outer = outerSimple ? outerSimple + 1 : outer;

    char* innerSimple = strrchr(inner_prim, '.');
    inner_prim = innerSimple ? innerSimple + 1 : inner_prim;

    // useless lol
    const char* mappedInner = convert_primitive_types(inner_prim);

    char* result = malloc(strlen(outer) + strlen(mappedInner) + 4);
    sprintf(result, "%s<%s>", outer, mappedInner);
    return result;
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

const char* convert_primitive_types(const char* type_name) {
    if (strcmp(type_name, "System.Boolean") == 0) {
        return "bool";
    }
    if (strcmp(type_name, "System.String") == 0) {
        return "string";
    }
    if (strcmp(type_name, "System.Object") == 0) {
        return "object";
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
    if (strcmp(type_name, "System.Object[]") == 0) {
        return "object";
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
