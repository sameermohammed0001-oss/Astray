#include "symbol_table.h"

#include <stdlib.h>

SymbolTable *symbol_table_create(void) {
    return calloc(1, sizeof(SymbolTable));
}

void symbol_table_free(SymbolTable *table) {
    if (!table) {
        return;
    }

    free(table);
}

int symbol_table_insert(SymbolTable *table, const char *name, int value) {
    if (!table || !name) {
        return 0;
    }

    (void)value;
    return 1;
}
