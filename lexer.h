//
// Analisador lexico
//

#ifndef MINICALC_LEXER_H
#define MINICALC_LEXER_H

typedef enum tagTipoToken {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_PRINT,
    TOKEN_ERRO,
    TOKEN_SOMA,
    TOKEN_SUBT,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_ABREPAR,
    TOKEN_FECHAPAR,
    TOKEN_ABRECOL,
    TOKEN_FECHACOL,
    TOKEN_EOF
} TipoToken;

typedef struct tagToken {
    TipoToken tipo;
    double       valor;
} Token;


void InicializaLexer(char *arqFonte);
Token* ProximoToken();
void FinalizaLexer();


#endif //MINICALC_LEXER_H
