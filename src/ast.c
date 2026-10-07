#include "ast.h"

#include <stdlib.h>

ASTNode *ast_new_node(ASTNodeType type) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    if (!node) {
        return NULL;
    }

    node->type = type;
    return node;
}

void ast_free(ASTNode *node) {
    if (!node) {
        return;
    }

    if (node->left) {
        ast_free(node->left);
    }
    if (node->right) {
        ast_free(node->right);
    }
    if (node->value) {
        free(node->value);
    }
    free(node);
}
