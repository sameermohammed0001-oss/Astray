#include "parser.h"

int parser_init(Parser *parser, Lexer *lexer) {
    if (!parser || !lexer) {
        return 0;
    }

    parser->lexer = lexer;
    parser->current = lexer_next_token(lexer);
    parser->previous = parser->current;
    return 1;
}

Token parser_peek(Parser *parser) {
    if (!parser) {
        return (Token){0};
    }

    return parser->current;
}

Token parser_next(Parser *parser) {
    if (!parser) {
        return (Token){0};
    }

    parser->previous = parser->current;
    parser->current = lexer_next_token(parser->lexer);
    return parser->previous;
}

int parser_match(Parser *parser, TokenType type) {
    if (!parser) {
        return 0;
    }

    if (parser->current.type == type) {
        parser_next(parser);
        return 1;
    }

    return 0;
}

int parser_expect(Parser *parser, TokenType type) {
    if (!parser) {
        return 0;
    }

    if (parser->current.type != type) {
        return 0;
    }

    parser_next(parser);
    return 1;
}
