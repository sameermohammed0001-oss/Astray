#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static char *copy_string(const char *text)
{
    char *copy = malloc(strlen(text) + 1);

    if (copy == NULL)
        exit(1);

    strcpy(copy, text);

    return copy;
}

void symbol_table_init(SymbolTable *table)
{
    table->count = 0;
}

int symbol_table_exists(
    SymbolTable *table,
    const char *name
)
{
    for (int i = 0; i < table->count; i++)
    {
        if (strcmp(table->symbols[i].name, name) == 0)
            return 1;
    }

    return 0;
}

int symbol_table_add(
    SymbolTable *table,
    const char *name
)
{
    if (symbol_table_exists(table, name))
        return 0;

    if (table->count >= MAX_SYMBOLS)
        return 0;

    table->symbols[table->count].name =
        copy_string(name);

    table->count++;

    return 1;
}

void symbol_table_free(SymbolTable *table)
{
    for (int i = 0; i < table->count; i++)
        free(table->symbols[i].name);

    table->count = 0;
}
