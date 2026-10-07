#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static Token current;
static Token previous;

static void advance_token(void)
{
    token_free(previous);
    previous = current;
    current = lexer_next();
}

static int check(TokenType type)
{
    return current.type == type;
}

static int match(TokenType type)
{
    if (!check(type))
        return 0;

    advance_token();

    return 1;
}

static void error(const char *message)
{
    printf("Parser error at line %d: %s\n", current.line, message);
    exit(1);
}

static void consume(TokenType type, const char *message)
{
    if (!check(type))
        error(message);

    advance_token();
}

void parser_init(void)
{
    current.type = TOKEN_EOF;
    current.lexeme = malloc(1);
    current.lexeme[0] = '\0';
    current.line = 1;

    previous.type = TOKEN_EOF;
    previous.lexeme = malloc(1);
    previous.lexeme[0] = '\0';
    previous.line = 1;

    advance_token();
}

static ASTNode *expression(void);

static ASTNode *primary(void)
{
    if (match(TOKEN_NUMBER))
    {
        int value = atoi(previous.lexeme);

        return ast_number(value);
    }

    if (match(TOKEN_IDENTIFIER))
    {
        return ast_identifier(previous.lexeme);
    }

    if (match(TOKEN_LEFT_PAREN))
    {
        ASTNode *node = expression();

        consume(
            TOKEN_RIGHT_PAREN,
            "Expected ')' after expression"
        );

        return node;
    }

    error("Expected expression");

    return NULL;
}

static ASTNode *unary(void)
{
    if (match(TOKEN_MINUS))
    {
        ASTNode *operand = unary();

        return ast_unary("-", operand);
    }

    return primary();
}

static ASTNode *factor(void)
{
    ASTNode *node = unary();

    while (check(TOKEN_STAR) ||
           check(TOKEN_SLASH) ||
           check(TOKEN_PERCENT))
    {
        TokenType operator = current.type;

        advance_token();

        ASTNode *right = unary();

        const char *operator_text;

        if (operator == TOKEN_STAR)
            operator_text = "*";
        else if (operator == TOKEN_SLASH)
            operator_text = "/";
        else
            operator_text = "%";

        node = ast_binary(node, operator_text, right);
    }

    return node;
}

static ASTNode *term(void)
{
    ASTNode *node = factor();

    while (check(TOKEN_PLUS) ||
           check(TOKEN_MINUS))
    {
        TokenType operator = current.type;

        advance_token();

        ASTNode *right = factor();

        const char *operator_text;

        if (operator == TOKEN_PLUS)
            operator_text = "+";
        else
            operator_text = "-";

        node = ast_binary(node, operator_text, right);
    }

    return node;
}

static ASTNode *comparison(void)
{
    ASTNode *node = term();

    while (check(TOKEN_LESS) ||
           check(TOKEN_GREATER) ||
           check(TOKEN_LESS_EQUAL) ||
           check(TOKEN_GREATER_EQUAL))
    {
        TokenType operator = current.type;

        advance_token();

        ASTNode *right = term();

        const char *operator_text;

        if (operator == TOKEN_LESS)
            operator_text = "<";
        else if (operator == TOKEN_GREATER)
            operator_text = ">";
        else if (operator == TOKEN_LESS_EQUAL)
            operator_text = "<=";
        else
            operator_text = ">=";

        node = ast_binary(node, operator_text, right);
    }

    return node;
}

static ASTNode *equality(void)
{
    ASTNode *node = comparison();

    while (check(TOKEN_EQUAL) ||
           check(TOKEN_NOT_EQUAL))
    {
        TokenType operator = current.type;

        advance_token();

        ASTNode *right = comparison();

        const char *operator_text;

        if (operator == TOKEN_EQUAL)
            operator_text = "==";
        else
            operator_text = "!=";

        node = ast_binary(node, operator_text, right);
    }

    return node;
}

static ASTNode *expression(void)
{
    return equality();
}

static ASTNode *variable_declaration(void)
{
    consume(
        TOKEN_IDENTIFIER,
        "Expected variable name"
    );

    char *name = malloc(strlen(previous.lexeme) + 1);

    if (name == NULL)
        exit(1);

    strcpy(name, previous.lexeme);

    consume(
        TOKEN_ASSIGN,
        "Expected '=' after variable name"
    );

    ASTNode *value = expression();

    consume(
        TOKEN_SEMICOLON,
        "Expected ';' after variable declaration"
    );

    ASTNode *node = ast_var_decl(name, value);

    free(name);

    return node;
}

static ASTNode *show_statement(void)
{
    consume(
        TOKEN_LEFT_PAREN,
        "Expected '(' after 'show'"
    );

    ASTNode *expression_node = expression();

    consume(
        TOKEN_RIGHT_PAREN,
        "Expected ')' after expression"
    );

    consume(
        TOKEN_SEMICOLON,
        "Expected ';' after show statement"
    );

    return ast_show(expression_node);
}

static ASTNode *statement(void)
{
    if (match(TOKEN_LET))
        return variable_declaration();

    if (match(TOKEN_SHOW))
        return show_statement();

    error("Expected statement");

    return NULL;
}

ASTNode *parse_program(void)
{
    ASTNode *program = ast_program();

    while (!check(TOKEN_EOF))
    {
        ASTNode *node = statement();

        ast_program_add(program, node);
    }

    return program;
}