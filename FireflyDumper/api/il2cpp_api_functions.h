

#ifndef ASTROLABE_IL2CPP_API_FUNCTIONS_H
#define ASTROLABE_IL2CPP_API_FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*
 * Field Attributes (21.1.5).
 */

#define FIELD_ATTRIBUTE_FIELD_ACCESS_MASK     0x0007
#define FIELD_ATTRIBUTE_COMPILER_CONTROLLED   0x0000
#define FIELD_ATTRIBUTE_PRIVATE               0x0001
#define FIELD_ATTRIBUTE_FAM_AND_ASSEM         0x0002
#define FIELD_ATTRIBUTE_ASSEMBLY              0x0003
#define FIELD_ATTRIBUTE_FAMILY                0x0004
#define FIELD_ATTRIBUTE_FAM_OR_ASSEM          0x0005
#define FIELD_ATTRIBUTE_PUBLIC                0x0006

#define FIELD_ATTRIBUTE_STATIC                0x0010
#define FIELD_ATTRIBUTE_INIT_ONLY             0x0020
#define FIELD_ATTRIBUTE_LITERAL               0x0040
#define FIELD_ATTRIBUTE_NOT_SERIALIZED        0x0080
#define FIELD_ATTRIBUTE_SPECIAL_NAME          0x0200
#define FIELD_ATTRIBUTE_PINVOKE_IMPL          0x2000

/* For runtime use only */
#define FIELD_ATTRIBUTE_RESERVED_MASK         0x9500
#define FIELD_ATTRIBUTE_RT_SPECIAL_NAME       0x0400
#define FIELD_ATTRIBUTE_HAS_FIELD_MARSHAL     0x1000
#define FIELD_ATTRIBUTE_HAS_DEFAULT           0x8000
#define FIELD_ATTRIBUTE_HAS_FIELD_RVA         0x0100

/*
 * Method Attributes (22.1.9)
 */

#define METHOD_IMPL_ATTRIBUTE_CODE_TYPE_MASK       0x0003
#define METHOD_IMPL_ATTRIBUTE_IL                   0x0000
#define METHOD_IMPL_ATTRIBUTE_NATIVE               0x0001
#define METHOD_IMPL_ATTRIBUTE_OPTIL                0x0002
#define METHOD_IMPL_ATTRIBUTE_RUNTIME              0x0003

#define METHOD_IMPL_ATTRIBUTE_MANAGED_MASK         0x0004
#define METHOD_IMPL_ATTRIBUTE_UNMANAGED            0x0004
#define METHOD_IMPL_ATTRIBUTE_MANAGED              0x0000

#define METHOD_IMPL_ATTRIBUTE_FORWARD_REF          0x0010
#define METHOD_IMPL_ATTRIBUTE_PRESERVE_SIG         0x0080
#define METHOD_IMPL_ATTRIBUTE_INTERNAL_CALL        0x1000
#define METHOD_IMPL_ATTRIBUTE_SYNCHRONIZED         0x0020
#define METHOD_IMPL_ATTRIBUTE_NOINLINING           0x0008
#define METHOD_IMPL_ATTRIBUTE_MAX_METHOD_IMPL_VAL  0xffff

#define METHOD_ATTRIBUTE_MEMBER_ACCESS_MASK        0x0007
#define METHOD_ATTRIBUTE_COMPILER_CONTROLLED       0x0000
#define METHOD_ATTRIBUTE_PRIVATE                   0x0001
#define METHOD_ATTRIBUTE_FAM_AND_ASSEM             0x0002
#define METHOD_ATTRIBUTE_ASSEM                     0x0003
#define METHOD_ATTRIBUTE_FAMILY                    0x0004
#define METHOD_ATTRIBUTE_FAM_OR_ASSEM              0x0005
#define METHOD_ATTRIBUTE_PUBLIC                    0x0006

#define METHOD_ATTRIBUTE_STATIC                    0x0010
#define METHOD_ATTRIBUTE_FINAL                     0x0020
#define METHOD_ATTRIBUTE_VIRTUAL                   0x0040
#define METHOD_ATTRIBUTE_HIDE_BY_SIG               0x0080

#define METHOD_ATTRIBUTE_VTABLE_LAYOUT_MASK        0x0100
#define METHOD_ATTRIBUTE_REUSE_SLOT                0x0000
#define METHOD_ATTRIBUTE_NEW_SLOT                  0x0100

#define METHOD_ATTRIBUTE_STRICT                    0x0200
#define METHOD_ATTRIBUTE_ABSTRACT                  0x0400
#define METHOD_ATTRIBUTE_SPECIAL_NAME              0x0800

#define METHOD_ATTRIBUTE_PINVOKE_IMPL              0x2000
#define METHOD_ATTRIBUTE_UNMANAGED_EXPORT          0x0008

/*
 * For runtime use only
 */
#define METHOD_ATTRIBUTE_RESERVED_MASK             0xd000
#define METHOD_ATTRIBUTE_RT_SPECIAL_NAME           0x1000
#define METHOD_ATTRIBUTE_HAS_SECURITY              0x4000
#define METHOD_ATTRIBUTE_REQUIRE_SEC_OBJECT        0x8000

/*
* Type Attributes (21.1.13).
*/
#define TYPE_ATTRIBUTE_VISIBILITY_MASK       0x00000007
#define TYPE_ATTRIBUTE_NOT_PUBLIC            0x00000000
#define TYPE_ATTRIBUTE_PUBLIC                0x00000001
#define TYPE_ATTRIBUTE_NESTED_PUBLIC         0x00000002
#define TYPE_ATTRIBUTE_NESTED_PRIVATE        0x00000003
#define TYPE_ATTRIBUTE_NESTED_FAMILY         0x00000004
#define TYPE_ATTRIBUTE_NESTED_ASSEMBLY       0x00000005
#define TYPE_ATTRIBUTE_NESTED_FAM_AND_ASSEM  0x00000006
#define TYPE_ATTRIBUTE_NESTED_FAM_OR_ASSEM   0x00000007

#define TYPE_ATTRIBUTE_LAYOUT_MASK           0x00000018
#define TYPE_ATTRIBUTE_AUTO_LAYOUT           0x00000000
#define TYPE_ATTRIBUTE_SEQUENTIAL_LAYOUT     0x00000008
#define TYPE_ATTRIBUTE_EXPLICIT_LAYOUT       0x00000010

#define TYPE_ATTRIBUTE_CLASS_SEMANTIC_MASK   0x00000020
#define TYPE_ATTRIBUTE_CLASS                 0x00000000
#define TYPE_ATTRIBUTE_INTERFACE             0x00000020

#define TYPE_ATTRIBUTE_ABSTRACT              0x00000080
#define TYPE_ATTRIBUTE_SEALED                0x00000100
#define TYPE_ATTRIBUTE_SPECIAL_NAME          0x00000400

#define TYPE_ATTRIBUTE_IMPORT                0x00001000
#define TYPE_ATTRIBUTE_SERIALIZABLE          0x00002000

#define TYPE_ATTRIBUTE_STRING_FORMAT_MASK    0x00030000
#define TYPE_ATTRIBUTE_ANSI_CLASS            0x00000000
#define TYPE_ATTRIBUTE_UNICODE_CLASS         0x00010000
#define TYPE_ATTRIBUTE_AUTO_CLASS            0x00020000

#define TYPE_ATTRIBUTE_BEFORE_FIELD_INIT     0x00100000
#define TYPE_ATTRIBUTE_FORWARDER             0x00200000

#define TYPE_ATTRIBUTE_RESERVED_MASK         0x00040800
#define TYPE_ATTRIBUTE_RT_SPECIAL_NAME       0x00000800
#define TYPE_ATTRIBUTE_HAS_SECURITY          0x00040000

/*
* Flags for Params (22.1.12)
*/
#define PARAM_ATTRIBUTE_IN                 0x0001
#define PARAM_ATTRIBUTE_OUT                0x0002
#define PARAM_ATTRIBUTE_OPTIONAL           0x0010
#define PARAM_ATTRIBUTE_RESERVED_MASK      0xf000
#define PARAM_ATTRIBUTE_HAS_DEFAULT        0x1000
#define PARAM_ATTRIBUTE_HAS_FIELD_MARSHAL  0x2000
#define PARAM_ATTRIBUTE_UNUSED             0xcfe0

// Flags for Generic Parameters (II.23.1.7)
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_NON_VARIANT                           0x00
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_COVARIANT                             0x01
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_CONTRAVARIANT                         0x02
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_VARIANCE_MASK                         0x03
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_REFERENCE_TYPE_CONSTRAINT             0x04
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_NOT_NULLABLE_VALUE_TYPE_CONSTRAINT    0x08
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_DEFAULT_CONSTRUCTOR_CONSTRAINT        0x10
#define IL2CPP_GENERIC_PARAMETER_ATTRIBUTE_SPECIAL_CONSTRAINT_MASK               0x1C

/**
 * 21.5 AssemblyRefs
 */
#define ASSEMBLYREF_FULL_PUBLIC_KEY_FLAG      0x00000001
#define ASSEMBLYREF_RETARGETABLE_FLAG         0x00000100
#define ASSEMBLYREF_ENABLEJITCOMPILE_TRACKING_FLAG 0x00008000
#define ASSEMBLYREF_DISABLEJITCOMPILE_OPTIMIZER_FLAG 0x00004000

typedef void Il2CppDomain;
typedef void Il2CppClass;
typedef void Il2CppType;
typedef void Il2CppObject;
typedef void Il2CppAssembly;
typedef void Il2CppImage;
typedef void Il2CppThread;
typedef void Il2CppType;
typedef void ReflectionFieldInfo;
typedef void ReflectionMethodInfo;
typedef void ParameterInfo;
typedef void FieldInfo;
typedef void MethodInfo;

typedef struct MonitorData MonitorData;
typedef uint32_t il2cpp_array_size_t;

typedef struct {
    void* klass;
    void* monitor;
    int32_t length;
    uint16_t chars[];
} Il2CppString;

typedef struct {
    FieldInfo* field;
} Il2CppReflectionField;

typedef struct {
    uintptr_t length;
    uintptr_t lower_bound;
} Il2CppArrayBounds;

typedef struct {
    Il2CppClass* klass;
    MonitorData* monitor;
    Il2CppArrayBounds* bounds;
    uintptr_t max_length;
    Il2CppObject* vector[0];
} Il2CppArray;

typedef void* (*assembly_get_image_t)(void* assembly);
typedef MethodInfo* (*class_get_methods_t)(void* klass, void** iter);
typedef const char* (*class_get_name_t)(void* klass);
typedef const char* (*class_get_namespace_t)(void* klass);
typedef void* (*domain_get_t)(void);
typedef void** (*domain_get_assemblies_t)(void* domain, size_t* count);
typedef const char* (*method_get_name_t)(const MethodInfo*);
typedef size_t (*image_get_class_count_t)(void* image);
typedef void* (*image_get_class_t)(void* image, size_t idx);
typedef void* (*class_get_fields_t)(void* klass, void** iter);
typedef void* (*class_get_parent_t)(void* klass);
typedef bool (*class_is_valuetype_t)(void* klass);
typedef int32_t (*class_get_flags_t)(void* klass);
typedef void* (*class_from_type_t)(void* type);
typedef bool (*class_is_enum_t)(void* klass);
typedef Il2CppClass* (*class_get_interfaces_t)(Il2CppClass* class, void** iter);
typedef int32_t (*field_get_flags_t)(void* field);
typedef const char* (*field_get_name_t)(void* field);
typedef size_t (*field_get_offset_t)(void* field);
typedef void* (*field_get_type_t)(void* field);
typedef void* (*method_get_return_type_t)(const MethodInfo*);
typedef uint32_t (*method_get_param_count_t)(const MethodInfo*);
typedef void* (*method_get_param_t)(const MethodInfo*, uint32_t);
typedef const char* (*type_get_name_t)(void* type);
typedef bool (*type_is_byref_t)(void* type);
typedef uint32_t (*type_get_attrs_t)(void* type);
typedef const char* (*image_get_name_t)(void* image);
typedef Il2CppThread* (*thread_attach_t)(Il2CppDomain* domain);

typedef struct {
    void** table;

    assembly_get_image_t assembly_get_image;
    class_get_methods_t class_get_methods;
    class_get_name_t class_get_name;
    class_get_namespace_t class_get_namespace;
    domain_get_t domain_get;
    domain_get_assemblies_t domain_get_assemblies;
    method_get_name_t method_get_name;
    image_get_class_count_t image_get_class_count;
    image_get_class_t image_get_class;
    class_get_fields_t class_get_fields;
    class_get_parent_t class_get_parent;
    class_is_valuetype_t class_is_valuetype;
    class_get_interfaces_t class_get_interfaces;
    class_get_flags_t class_get_flags;
    class_from_type_t class_from_type;
    class_is_enum_t class_is_enum;
    field_get_flags_t field_get_flags;
    field_get_name_t field_get_name;
    field_get_offset_t field_get_offset;
    field_get_type_t field_get_type;
    method_get_return_type_t method_get_return_type;
    method_get_param_count_t method_get_param_count;
    method_get_param_t method_get_param;
    type_get_name_t type_get_name;
    type_is_byref_t type_is_byref;
    type_get_attrs_t type_get_attrs;
    image_get_name_t image_get_name;
    thread_attach_t thread_attach;

} Il2CppFunctionTable;

typedef struct {
    uintptr_t GetFieldFromHandle;

    uintptr_t GetRawConstantValue;
    uintptr_t GetCustomAttributes;

    uintptr_t get_MetadataToken;
} Field;

typedef struct {
    uintptr_t GetMethodFromHandle;
    uintptr_t GetParameters;
    uintptr_t get_Name;
} Method;

typedef struct {
    Field field;
    Method method;
} Il2CppReflectionOffsetTable;

// global
extern Il2CppFunctionTable Il2CppFunctions;
extern Il2CppReflectionOffsetTable ReflectionOffsets;

uintptr_t method_get_relative_pointer(void* arg);
void* class_get_type(void* arg);
void il2cpp_rva_offsets_init();
void il2cpp_functions_init(uintptr_t il2cpp_init_addr);

#endif //ASTROLABE_IL2CPP_API_FUNCTIONS_H
