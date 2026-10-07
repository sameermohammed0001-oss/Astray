#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char *copy_string(const char *text)
{
    char *copy = malloc(strlen(text) + 1);

    if (copy == NULL)
        exit(1);

    strcpy(copy, text);

    return copy;
}

static ASTNode *create_node(ASTNodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if (node == NULL)
        exit(1);

    node->type = type;

    return node;
}

ASTNode *ast_program(void)
{
    ASTNode *node = create_node(AST_PROGRAM);

    node->program.count = 0;
    node->program.capacity = 4;
    node->program.statements =
        malloc(sizeof(ASTNode *) * node->program.capacity);

    if (node->program.statements == NULL)
        exit(1);

    return node;
}

void ast_program_add(ASTNode *program, ASTNode *statement)
{
    if (program->program.count >= program->program.capacity)
    {
        program->program.capacity *= 2;

        program->program.statements =
            realloc(
                program->program.statements,
                sizeof(ASTNode *) * program->program.capacity
            );

        if (program->program.statements == NULL)
            exit(1);
    }

    program->program.statements[program->program.count] = statement;
    program->program.count++;
}

ASTNode *ast_number(int value)
{
    ASTNode *node = create_node(AST_NUMBER);

    node->number = value;

    return node;
}

ASTNode *ast_identifier(const char *name)
{
    ASTNode *node = create_node(AST_IDENTIFIER);

    node->identifier = copy_string(name);

    return node;
}

ASTNode *ast_binary(ASTNode *left, const char *operator, ASTNode *right)
{
    ASTNode *node = create_node(AST_BINARY);

    node->binary.left = left;
    node->binary.right = right;
    node->binary.operator = copy_string(operator);

    return node;
}

ASTNode *ast_unary(const char *operator, ASTNode *operand)
{
    ASTNode *node = create_node(AST_UNARY);

    node->unary.operator = copy_string(operator);
    node->unary.operand = operand;

    return node;
}

ASTNode *ast_assign(const char *name, ASTNode *value)
{
    ASTNode *node = create_node(AST_ASSIGN);

    node->assign.name = copy_string(name);
    node->assign.value = value;

    return node;
}

ASTNode *ast_var_decl(const char *name, ASTNode *value)
{
    ASTNode *node = create_node(AST_VAR_DECL);

    node->var_decl.name = copy_string(name);
    node->var_decl.value = value;

    return node;
}

ASTNode *ast_show(ASTNode *expression)
{
    ASTNode *node = create_node(AST_SHOW);

    node->show = expression;

    return node;
}

static void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
        printf("  ");
}

void ast_print(ASTNode *node, int depth)
{
    if (node == NULL)
        return;

    print_indent(depth);

    switch (node->type)
    {
        case AST_PROGRAM:
            printf("PROGRAM\n");

            for (int i = 0; i < node->program.count; i++)
                ast_print(node->program.statements[i], depth + 1);

            break;

        case AST_NUMBER:
            printf("NUMBER %d\n", node->number);
            break;

        case AST_IDENTIFIER:
            printf("IDENTIFIER %s\n", node->identifier);
            break;

        case AST_BINARY:
            printf("BINARY %s\n", node->binary.operator);
            ast_print(node->binary.left, depth + 1);
            ast_print(node->binary.right, depth + 1);
            break;

        case AST_UNARY:
            printf("UNARY %s\n", node->unary.operator);
            ast_print(node->unary.operand, depth + 1);
            break;

        case AST_ASSIGN:
            printf("ASSIGN %s\n", node->assign.name);
            ast_print(node->assign.value, depth + 1);
            break;

        case AST_VAR_DECL:
            printf("VAR_DECL %s\n", node->var_decl.name);
            ast_print(node->var_decl.value, depth + 1);
            break;

        case AST_SHOW:
            printf("SHOW\n");
            ast_print(node->show, depth + 1);
            break;
    }
}

void ast_free(ASTNode *node)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_PROGRAM:
            for (int i = 0; i < node->program.count; i++)
                ast_free(node->program.statements[i]);

            free(node->program.statements);
            break;

        case AST_IDENTIFIER:
            free(node->identifier);
            break;

        case AST_BINARY:
            ast_free(node->binary.left);
            ast_free(node->binary.right);
            free(node->binary.operator);
            break;

        case AST_UNARY:
            ast_free(node->unary.operand);
            free(node->unary.operator);
            break;

        case AST_ASSIGN:
            free(node->assign.name);
            ast_free(node->assign.value);
            break;

        case AST_VAR_DECL:
            free(node->var_decl.name);
            ast_free(node->var_decl.value);
            break;

        case AST_SHOW:
            ast_free(node->show);
            break;

        case AST_NUMBER:
            break;
    }

    free(node);
}