#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct {
    int dummy;
} SymbolTable;

SymbolTable *symbol_table_create(void);
void symbol_table_free(SymbolTable *table);
int symbol_table_insert(SymbolTable *table, const char *name, int value);

#endif
