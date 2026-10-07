#include <stdio.h>
#include "lexer.h"

int main(void)
{
    const char *source =
        "let x = 10;\n"
        "let y = 20;\n"
        "let result = x + y * 2;\n"
        "show(result);\n";

    lexer_init(source);

    while (1)
    {
        Token token = lexer_next();

        printf("%-15s %-10s line=%d\n",
               token_type_name(token.type),
               token.lexeme,
               token.line);

        if (token.type == TOKEN_EOF)
        {
            token_free(token);
            break;
        }

        token_free(token);
    }

    return 0;
}