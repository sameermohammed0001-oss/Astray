#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static const char *source;
static int current;
static int line;

void lexer_init(const char *input)
{
    source = input;
    current = 0;
    line = 1;
}

static char peek(void)
{
    return source[current];
}

static char peek_next(void)
{
    if (source[current] == '\0')
        return '\0';

    return source[current + 1];
}

static char advance_char(void)
{
    return source[current++];
}

static int match_char(char expected)
{
    if (source[current] != expected)
        return 0;

    current++;
    return 1;
}

static char *copy_text(int start, int end)
{
    int length = end - start;
    char *text = malloc(length + 1);

    if (text == NULL)
        exit(1);

    memcpy(text, source + start, length);
    text[length] = '\0';

    return text;
}

static Token make_token(TokenType type, int start)
{
    Token token;

    token.type = type;
    token.lexeme = copy_text(start, current);
    token.line = line;

    return token;
}

static Token error_token(const char *message)
{
    Token token;

    token.type = TOKEN_EOF;
    token.lexeme = malloc(strlen(message) + 1);
    strcpy(token.lexeme, message);
    token.line = line;

    return token;
}

static TokenType check_keyword(const char *text)
{
    if (strcmp(text, "let") == 0)
        return TOKEN_LET;

    if (strcmp(text, "fn") == 0)
        return TOKEN_FN;

    if (strcmp(text, "return") == 0)
        return TOKEN_RETURN;

    if (strcmp(text, "if") == 0)
        return TOKEN_IF;

    if (strcmp(text, "else") == 0)
        return TOKEN_ELSE;

    if (strcmp(text, "while") == 0)
        return TOKEN_WHILE;

    if (strcmp(text, "show") == 0)
        return TOKEN_SHOW;

    return TOKEN_IDENTIFIER;
}

static Token scan_number(int start)
{
    while (isdigit(peek()))
        advance_char();

    return make_token(TOKEN_NUMBER, start);
}

static Token scan_identifier(int start)
{
    while (isalnum(peek()) || peek() == '_')
        advance_char();

    char *text = copy_text(start, current);
    TokenType type = check_keyword(text);

    Token token;

    token.type = type;
    token.lexeme = text;
    token.line = line;

    return token;
}

Token lexer_next(void)
{
    while (1)
    {
        char c = peek();

        if (c == ' ' || c == '\t' || c == '\r')
        {
            advance_char();
            continue;
        }

        if (c == '\n')
        {
            line++;
            advance_char();
            continue;
        }

        break;
    }

    int start = current;
    char c = advance_char();

    if (c == '\0')
        return make_token(TOKEN_EOF, start);

    if (isdigit(c))
        return scan_number(start);

    if (isalpha(c) || c == '_')
        return scan_identifier(start);

    switch (c)
    {
        case '+':
            return make_token(TOKEN_PLUS, start);

        case '-':
            return make_token(TOKEN_MINUS, start);

        case '*':
            return make_token(TOKEN_STAR, start);

        case '/':
            return make_token(TOKEN_SLASH, start);

        case '%':
            return make_token(TOKEN_PERCENT, start);

        case '=':
            if (match_char('='))
                return make_token(TOKEN_EQUAL, start);

            return make_token(TOKEN_ASSIGN, start);

        case '!':
            if (match_char('='))
                return make_token(TOKEN_NOT_EQUAL, start);

            return error_token("Unexpected '!'");

        case '<':
            if (match_char('='))
                return make_token(TOKEN_LESS_EQUAL, start);

            return make_token(TOKEN_LESS, start);

        case '>':
            if (match_char('='))
                return make_token(TOKEN_GREATER_EQUAL, start);

            return make_token(TOKEN_GREATER, start);

        case '(':
            return make_token(TOKEN_LEFT_PAREN, start);

        case ')':
            return make_token(TOKEN_RIGHT_PAREN, start);

        case '{':
            return make_token(TOKEN_LEFT_BRACE, start);

        case '}':
            return make_token(TOKEN_RIGHT_BRACE, start);

        case ';':
            return make_token(TOKEN_SEMICOLON, start);

        case ',':
            return make_token(TOKEN_COMMA, start);

        default:
            return error_token("Unexpected character");
    }
}

const char *token_type_name(TokenType type)
{
    switch (type)
    {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER: return "NUMBER";

        case TOKEN_LET: return "LET";
        case TOKEN_FN: return "FN";
        case TOKEN_RETURN: return "RETURN";
        case TOKEN_IF: return "IF";
        case TOKEN_ELSE: return "ELSE";
        case TOKEN_WHILE: return "WHILE";
        case TOKEN_SHOW: return "SHOW";

        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_STAR: return "STAR";
        case TOKEN_SLASH: return "SLASH";
        case TOKEN_PERCENT: return "PERCENT";

        case TOKEN_ASSIGN: return "ASSIGN";

        case TOKEN_EQUAL: return "EQUAL";
        case TOKEN_NOT_EQUAL: return "NOT_EQUAL";
        case TOKEN_LESS: return "LESS";
        case TOKEN_GREATER: return "GREATER";
        case TOKEN_LESS_EQUAL: return "LESS_EQUAL";
        case TOKEN_GREATER_EQUAL: return "GREATER_EQUAL";

        case TOKEN_LEFT_PAREN: return "LEFT_PAREN";
        case TOKEN_RIGHT_PAREN: return "RIGHT_PAREN";
        case TOKEN_LEFT_BRACE: return "LEFT_BRACE";
        case TOKEN_RIGHT_BRACE: return "RIGHT_BRACE";

        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";

        default: return "UNKNOWN";
    }
}

void token_free(Token token)
{
    free(token.lexeme);
}