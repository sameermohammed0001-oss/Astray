#ifndef IR_H
#define IR_H

typedef struct {
    int dummy;
} IRModule;

IRModule *ir_module_create(void);
void ir_module_free(IRModule *module);

#endif
