#include "semantic.h"

#include <stdlib.h>

SemanticAnalyzer *semantic_analyzer_create(void) {
    return calloc(1, sizeof(SemanticAnalyzer));
}

void semantic_analyzer_free(SemanticAnalyzer *analyzer) {
    if (!analyzer) {
        return;
    }

    free(analyzer);
}

int semantic_analyze(SemanticAnalyzer *analyzer, ASTNode *root) {
    (void)analyzer;
    (void)root;
    return 1;
}
