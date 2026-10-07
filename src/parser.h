#ifndef ASTRAY_PARSER_H
#define ASTRAY_PARSER_H

#include "ast.h"
#include "lexer.h"

void parser_init(void);
ASTNode *parse_program(void);

#endif