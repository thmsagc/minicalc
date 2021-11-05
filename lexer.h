//
// Analisador lexico
//

#ifndef MINICALC_LEXER_H
#define MINICALC_LEXER_H

#define IDENT_MAX_SIZE 40

typedef enum tagTipoToken {
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_PRINT,
    TOKEN_IDENT,
    TOKEN_VAR,
    TOKEN_ASSIGN,
    TOKEN_PTVIR,
    TOKEN_ERRO,
    TOKEN_SOMA,
    TOKEN_SUBT,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_POW,
    TOKEN_ABREPAR,
    TOKEN_FECHAPAR,
    TOKEN_ABRECOL,
    TOKEN_FECHACOL,
    TOKEN_EOF
} TipoToken;

typedef struct tagToken {
    TipoToken tipo;
    double       valor;
    char nome[IDENT_MAX_SIZE];
} Token;

void InicializaLexer(char *arqFonte);
Token* ProximoToken();
void FinalizaLexer();


#endif //MINICALC_LEXER_H
