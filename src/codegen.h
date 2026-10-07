#ifndef CODEGEN_H
#define CODEGEN_H

#include "ir.h"

typedef struct {
    int dummy;
} CodeGenerator;

CodeGenerator *codegen_create(void);
void codegen_free(CodeGenerator *generator);
int codegen_generate(CodeGenerator *generator, IRModule *module);

#endif
