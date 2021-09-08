#include <stdio.h>
#include <stdlib.h>

#include "arq.h"
#include "lexer.h"

void ImpBuffer(Buffer *b) {
    for (long c = 0; c < b->tam; ++c)
        putchar(b->cont[c]);
}

int main() {
    InicializaLexer("literal.mc");

    Token *t = ProximoToken();
    while (t->tipo != TOKEN_EOF) {
        printf("Tipo do token: %d - ", t->tipo);   // TODO: melhorar impressao do tipo
        printf("Valor do token: %d\n", t->valor);

        t = ProximoToken();
    }

    FinalizaLexer();
    return 0;
}
