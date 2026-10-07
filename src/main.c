#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Error: Could not open file '%s'\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *source = malloc(size + 1);

    if (source == NULL)
    {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        exit(1);
    }

    fread(source, 1, size, file);
    source[size] = '\0';

    fclose(file);

    return source;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./astray <source-file>\n");
        return 1;
    }

    char *source = read_file(argv[1]);

    lexer_init(source);

    parser_init();

    ASTNode *program = parse_program();

    printf("\n===== ASTRAY AST =====\n\n");

    ast_print(program, 0);

    ast_free(program);

    free(source);

    return 0;
}