cmake_minimum_required(VERSION 3.28)
project(Astrolabe C)

set(CMAKE_C_STANDARD 90)

add_library(Astrolabe SHARED library.c
        utils/logger.c
        utils/logger.h
        entry.c
        entry.h
        api/il2cpp_api_functions.c
        api/il2cpp_api_functions.h
        dumper/domain.c
        dumper/domain.h
        dumper/assembly.c
        dumper/assembly.h
        dumper/fields.c
        dumper/fields.h
        dumper/methods.c
        dumper/methods.h
        dumper/class.c
        dumper/class.h
        utils/utils.c
        utils/utils.h
)
