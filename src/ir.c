#include "ir.h"

#include <stdlib.h>

IRModule *ir_module_create(void) {
    return calloc(1, sizeof(IRModule));
}

void ir_module_free(IRModule *module) {
    if (!module) {
        return;
    }

    free(module);
}
