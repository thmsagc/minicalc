// Analisador léxico para MiniCalc

#include <stdio.h>
#include <stdlib.h>
#include "arq.h"
#include "lexer.h"

Buffer *buffer;
Token *tok = NULL;

long pos = 0;

void InicializaLexer(char *arqFonte) {
    buffer = CriaBuffer(arqFonte);

    pos = 0;

    tok = (Token*) malloc(sizeof(Token));

    if (tok == NULL) {
        fprintf(stderr, "Erro alocando memoria para o token\n");
        exit(2);
    }

    tok->tipo = TOKEN_EOF;
    tok->valor = 0;
}

// função: ProximoToken
//
// Dado o arquivo-fonte, obtem e retorna o próximo token
Token* ProximoToken() {
    // TODO: obtem o proximo token da entrada e preenche tok

    // TODO: pula espaços em branco

    if (pos == buffer->tam - 1) {
        tok->tipo = TOKEN_EOF;
        tok->valor = 0;
    }

    return tok;
}

void FinalizaLexer() {
    DestroiBuffer(buffer);
    free(tok);
}
