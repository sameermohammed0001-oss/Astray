#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

typedef struct {
    int dummy;
} SemanticAnalyzer;

SemanticAnalyzer *semantic_analyzer_create(void);
void semantic_analyzer_free(SemanticAnalyzer *analyzer);
int semantic_analyze(SemanticAnalyzer *analyzer, ASTNode *root);

#endif
