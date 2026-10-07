#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    Lexer *lexer;
    Token current;
    Token previous;
} Parser;

int parser_init(Parser *parser, Lexer *lexer);
Token parser_peek(Parser *parser);
Token parser_next(Parser *parser);
int parser_match(Parser *parser, TokenType type);
int parser_expect(Parser *parser, TokenType type);

#endif
