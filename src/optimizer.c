#include "optimizer.h"

#include <stdlib.h>

Optimizer *optimizer_create(void) {
    return calloc(1, sizeof(Optimizer));
}

void optimizer_free(Optimizer *optimizer) {
    if (!optimizer) {
        return;
    }

    free(optimizer);
}

int optimizer_run(Optimizer *optimizer, IRModule *module) {
    (void)optimizer;
    (void)module;
    return 1;
}
