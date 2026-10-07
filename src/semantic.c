#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "symbol_table.h"

static SymbolTable symbols;

static void semantic_error(const char *message, const char *name)
{
    printf("Semantic Error: %s '%s'\n", message, name);
    exit(1);
}

static void analyze_node(ASTNode *node)
{
    if (node == NULL)
        return;

    switch (node->type)
    {
        case AST_PROGRAM:

            for (int i = 0; i < node->program.count; i++)
                analyze_node(node->program.statements[i]);

            break;

        case AST_NUMBER:

            break;

        case AST_IDENTIFIER:

            if (!symbol_table_exists(
                    &symbols,
                    node->identifier))
            {
                semantic_error(
                    "Undefined variable",
                    node->identifier
                );
            }

            break;

        case AST_BINARY:

            analyze_node(node->binary.left);
            analyze_node(node->binary.right);

            break;

        case AST_UNARY:

            analyze_node(node->unary.operand);

            break;

        case AST_VAR_DECL:

            if (symbol_table_exists(
                    &symbols,
                    node->var_decl.name))
            {
                semantic_error(
                    "Variable already declared",
                    node->var_decl.name
                );
            }

            analyze_node(node->var_decl.value);

            symbol_table_add(
                &symbols,
                node->var_decl.name
            );

            break;

        case AST_ASSIGN:

            if (!symbol_table_exists(
                    &symbols,
                    node->assign.name))
            {
                semantic_error(
                    "Undefined variable",
                    node->assign.name
                );
            }

            analyze_node(node->assign.value);

            break;

        case AST_SHOW:

            analyze_node(node->show);

            break;

        case AST_IF:

            analyze_node(
            node->if_statement.condition
        );

    analyze_node(
        node->if_statement.then_branch
    );

    if (node->if_statement.else_branch != NULL)
    {
        analyze_node(
            node->if_statement.else_branch
        );
    }

    break;

case AST_WHILE:

    analyze_node(
        node->while_statement.condition
    );

    analyze_node(
        node->while_statement.body
    );

    break;
    }
}

void semantic_analyze(ASTNode *program)
{
    symbol_table_init(&symbols);

    analyze_node(program);

    symbol_table_free(&symbols);
}