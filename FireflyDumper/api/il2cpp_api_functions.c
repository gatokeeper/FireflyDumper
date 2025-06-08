
#include <stdio.h>
#include "il2cpp_api_functions.h"
#include "../entry.h"

Il2CppFunctions Il2CppFunctions_t;
Il2CppRVAOffsets Il2CppRVAOffsets_t;

uintptr_t method_get_relative_pointer(void* arg) {
    if (!arg) return 0;

    uintptr_t ptr = *(uintptr_t*)((uintptr_t)arg + 0x08);

    if (ptr == 0) {
        return 0;
    }

    return ptr - settings.ga;
}

void* class_get_type(void* arg) {
    return (void*)((uintptr_t)arg + settings.class_byval);
}

void il2cpp_rva_offsets_init() {
    Il2CppRVAOffsets_t.GetFieldFromHandle = 0x104ED800;
    Il2CppRVAOffsets_t.GetRawConstantValue = 0x104F3910;
}

void il2cpp_functions_init(uintptr_t il2cpp_init_addr) {
    Il2CppFunctions_t.table = (void**)il2cpp_init_addr;

    // i love macros
    #define RESOLVE_FUNC(name, index) Il2CppFunctions_t.name = (typeof(Il2CppFunctions_t.name)) Il2CppFunctions_t.table[index];

    RESOLVE_FUNC(assembly_get_image, 22);

    RESOLVE_FUNC(class_get_methods, 35);
    RESOLVE_FUNC(class_get_name, 37);
    RESOLVE_FUNC(class_get_namespace, 39);

    RESOLVE_FUNC(domain_get, 63);
    RESOLVE_FUNC(domain_get_assemblies, 65);

    RESOLVE_FUNC(image_get_class_count, 169);
    RESOLVE_FUNC(image_get_class, 170);
    RESOLVE_FUNC(image_get_name, 168);

    RESOLVE_FUNC(class_get_fields, 31);
    RESOLVE_FUNC(class_get_parent, 40);
    RESOLVE_FUNC(class_is_valuetype, 43);
    RESOLVE_FUNC(class_get_flags, 45);
    RESOLVE_FUNC(class_from_type, 49);
    RESOLVE_FUNC(class_is_enum, 53);

    RESOLVE_FUNC(field_get_flags, 72);
    RESOLVE_FUNC(field_get_name, 73);
    RESOLVE_FUNC(field_get_offset, 75);
    RESOLVE_FUNC(field_get_type, 76);

    RESOLVE_FUNC(method_get_name, 117);
    RESOLVE_FUNC(method_get_return_type, 116);
    RESOLVE_FUNC(method_get_param_count, 123);
    RESOLVE_FUNC(method_get_param, 124);

    RESOLVE_FUNC(type_get_name, 161);
    RESOLVE_FUNC(type_is_byref, 162);
    RESOLVE_FUNC(type_get_attrs, 163);

    RESOLVE_FUNC(thread_attach, 154);

    #undef RESOLVE_FUNC
} // il2cpp_functions_init

