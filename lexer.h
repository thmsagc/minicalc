#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "file.h"

#define IDENT_MAX_SIZE 40


typedef enum tagTipoToken {
    TOKEN_LITERAL,
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_SEMICOLON,
    TOKEN_ERROR,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_POW,
    TOKEN_AND,
    TOKEN_LESS,
    TOKEN_NEG,
    TOKEN_COMMA,
    TOKEN_OPENPARENTHESES,
    TOKEN_CLOSEPARENTHESES,
    TOKEN_OPENBRACKETS,
    TOKEN_CLOSEBRACKETS,
    TOKEN_OPENKEYS,
    TOKEN_CLOSEKEYS,
    TOKEN_EOF
} TipoToken;

typedef struct tagToken {
    TipoToken tipo;
    int valor;
    char nome[IDENT_MAX_SIZE];
} Token;

void InicializaLexer(char *arqFonte);
Token* ProximoToken();
bool isKeyword(char* text);
void FinalizaLexer();

#endif
