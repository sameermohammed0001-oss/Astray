#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ir.h"

typedef struct {
    int dummy;
} Optimizer;

Optimizer *optimizer_create(void);
void optimizer_free(Optimizer *optimizer);
int optimizer_run(Optimizer *optimizer, IRModule *module);

#endif
