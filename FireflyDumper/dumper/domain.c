#include <stdio.h>

#include "domain.h"
#include "../api/il2cpp_api_functions.h"
#include "../utils/logger.h"
#include "assembly.h"
#include "../entry.h"


void dump_domain(FILE* f) {
    size_t assembly_count = 0;
    size_t class_count = 0;

    settings.class_byval = 128;

    Il2CppDomain* domain = Il2CppFunctions.domain_get();
    Il2CppFunctions.thread_attach(domain);
    Il2CppAssembly** assemblies = Il2CppFunctions.domain_get_assemblies(domain, &assembly_count);

    int i;
    for (i = 0; i < assembly_count; i++) {
        Il2CppImage* image = Il2CppFunctions.assembly_get_image(assemblies[i]);

        if (!image) {
            fprintf(f, "// Assembly #%i: (null image)\n", i);
            continue;
        }

        const char* image_name = Il2CppFunctions.image_get_name(image);
        if (!image_name) {
            fprintf(f, "// Assembly #%i: (null name)\n", i);
            continue;
        }

        fprintf(f, "// Assembly #%i: %s\n", i, image_name);
        fflush(f);
        class_count += Il2CppFunctions.image_get_class_count(image);
    }

    fprintf(f, "\n");
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Dumping %zu classes in %zu assemblies :3", class_count, assembly_count);
    logger_info(buffer);

    for (i = 0; i < assembly_count; i++) {
        dump_assembly(f, assemblies[i], i);
    }
    logger_info("Done dumping :3, written dump to dump.cs");
    fclose(f);
}
