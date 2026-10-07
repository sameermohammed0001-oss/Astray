#ifndef ASTRAY_SYMBOL_TABLE_H
#define ASTRAY_SYMBOL_TABLE_H

#define MAX_SYMBOLS 256

typedef struct
{
    char *name;
} Symbol;

typedef struct
{
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void symbol_table_init(SymbolTable *table);

int symbol_table_add(SymbolTable *table, const char *name);

int symbol_table_exists(
    SymbolTable *table,
    const char *name
);

void symbol_table_free(SymbolTable *table);

#endif
