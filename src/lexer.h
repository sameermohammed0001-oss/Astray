#ifndef ASTRAY_LEXER_H
#define ASTRAY_LEXER_H

typedef enum
{
    TOKEN_EOF,

    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_LET,
    TOKEN_FN,
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_SHOW,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    TOKEN_ASSIGN,

    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,

    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,

    TOKEN_SEMICOLON,
    TOKEN_COMMA
} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
    int line;
} Token;

void lexer_init(const char *source);
Token lexer_next(void);
const char *token_type_name(TokenType type);
void token_free(Token token);

#endif