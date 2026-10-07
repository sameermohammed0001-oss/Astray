#include "codegen.h"

#include <stdlib.h>

CodeGenerator *codegen_create(void) {
    return calloc(1, sizeof(CodeGenerator));
}

void codegen_free(CodeGenerator *generator) {
    if (!generator) {
        return;
    }

    free(generator);
}

int codegen_generate(CodeGenerator *generator, IRModule *module) {
    (void)generator;
    (void)module;
    return 1;
}
