#ifndef ASTRAY_AST_H
#define ASTRAY_AST_H

typedef enum
{
    AST_PROGRAM,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY,
    AST_UNARY,
    AST_ASSIGN,
    AST_VAR_DECL,
    AST_SHOW,
    AST_IF,
    AST_WHILE
} ASTNodeType;

typedef struct ASTNode ASTNode;

struct ASTNode
{
    ASTNodeType type;

    union
    {
        struct
        {
            ASTNode *condition;
            ASTNode *then_branch;
            ASTNode *else_branch;
        } if_statement;

        struct
        {
            ASTNode *condition;
            ASTNode *body;
        } while_statement;

        struct
        {
            ASTNode **statements;
            int count;
            int capacity;
        } program;

        int number;

        char *identifier;

        struct
        {
            ASTNode *left;
            ASTNode *right;
            char *operator;
        } binary;

        struct
        {
            ASTNode *operand;
            char *operator;
        } unary;

        struct
        {
            char *name;
            ASTNode *value;
        } assign;

        struct
        {
            char *name;
            ASTNode *value;
        } var_decl;

        ASTNode *show;
    };
};

ASTNode *ast_program(void);
void ast_program_add(ASTNode *program, ASTNode *statement);

ASTNode *ast_number(int value);
ASTNode *ast_identifier(const char *name);
ASTNode *ast_binary(ASTNode *left, const char *operator, ASTNode *right);
ASTNode *ast_unary(const char *operator, ASTNode *operand);
ASTNode *ast_assign(const char *name, ASTNode *value);
ASTNode *ast_var_decl(const char *name, ASTNode *value);
ASTNode *ast_show(ASTNode *expression);
ASTNode *ast_if(
    ASTNode *condition,
    ASTNode *then_branch,
    ASTNode *else_branch
);

ASTNode *ast_while(
    ASTNode *condition,
    ASTNode *body
);

void ast_print(ASTNode *node, int depth);
void ast_free(ASTNode *node);

#endif