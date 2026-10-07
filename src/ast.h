#ifndef AST_H
#define AST_H

typedef enum {
    AST_NODE_PROGRAM,
    AST_NODE_STATEMENT,
    AST_NODE_EXPRESSION,
    AST_NODE_IDENTIFIER,
    AST_NODE_LITERAL,
    AST_NODE_BINARY_OP
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *ast_new_node(ASTNodeType type);
void ast_free(ASTNode *node);

#endif
