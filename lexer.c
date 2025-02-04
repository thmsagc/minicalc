// Analisador léxico para MiniCalc

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "arq.h"
#include "lexer.h"

static Buffer *buffer;
static Token *tok = NULL;

static long pos = 0;

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

bool eof() {
    return !(pos < buffer->tam - 1);
}

char* TextoToken(long ini, long fim) {
    char *str = (char*) malloc(fim - ini + 1);

    if (str == NULL) {
        fprintf(stderr, "Erro alocando memoria\n");
        exit(1);
    }

    for (int i = 0; i + ini < fim; ++i) {
        str[i] = buffer->cont[i + ini];
    }

    str[fim - ini] = '\0';

    return str;
}

bool simbolo(char c) {
    return (c == '(' || c == ')' || c == '[' || c == ']'  || c == '+' || c == '-'  || c == '*' || c == '/' || c == '%' || c == '^' || c == '=' || c == ';');
}

// função: ProximoToken
//
// Dado o arquivo-fonte, obtem e retorna o próximo token
Token* ProximoToken() {
    // TODO: obtem o proximo token da entrada e preenche tok

    // pula espaços em branco
    while (!eof() && isspace(buffer->cont[pos]))
        pos++;

    if (eof()) {
        tok->tipo = TOKEN_EOF;
        tok->valor = 0;
    } else if (isalpha(buffer->cont[pos])) {
        long initPos = pos;
        while (!eof() && !isspace(buffer->cont[pos]) && !simbolo(buffer->cont[pos]))
            pos++;
        // texto do token: entre initPos e pos-1 no buffer
        char *texto = TextoToken(initPos, pos);
        if (strcmp(texto, "print") == 0)
        {
            tok->tipo = TOKEN_PRINT;
            tok->valor = 0;
        } else if (strcmp(texto, "var") == 0)
        {
            tok->tipo = TOKEN_VAR;
            tok->valor = 0;
        } else {
            tok->tipo = TOKEN_IDENT;
            strcpy(tok->nome, texto);
        }
        free(texto);
    } else if (isdigit(buffer->cont[pos])) {
        long initPos = pos;
        // TODO: verificar se existe erro léxico no final do literal inteiro
        while (!eof() && isdigit(buffer->cont[pos]))
            pos++;    
        if(buffer->cont[pos] == '.'){
        	pos++;
		    while (!eof() && isdigit(buffer->cont[pos]))
		        pos++;
		    char *texto = TextoToken(initPos, pos);
		    tok->tipo = TOKEN_FLOAT;
		    tok->valor = atof(texto);
		    free(texto);
        } else {
		    char *texto = TextoToken(initPos, pos);
		    tok->tipo = TOKEN_INT;
		    tok->valor = atoi(texto);
		    free(texto);       
        }

    } else if (simbolo(buffer->cont[pos])) {
        switch (buffer->cont[pos]) {
            case '(':
                tok->tipo = TOKEN_ABREPAR;
                break;
            case ')':
                tok->tipo = TOKEN_FECHAPAR;
                break;
            case '[':
                tok->tipo = TOKEN_ABRECOL;
                break;
            case ']':
                tok->tipo = TOKEN_FECHACOL;
                break;
            case '+':
                tok->tipo = TOKEN_SOMA;
                break;
            case '-':
                tok->tipo = TOKEN_SUBT;
                break;
            case '*':
                tok->tipo = TOKEN_MULT;
                break;
            case '/':
                tok->tipo = TOKEN_DIV;
                break;
            case '%':
                tok->tipo = TOKEN_MOD;
                break;
            case '^':
                tok->tipo = TOKEN_POW;
                break;
            case '=':
                tok->tipo = TOKEN_ASSIGN;
                break;
            case ';':
                tok->tipo = TOKEN_PTVIR;
                break;
            default:
                fprintf(stderr, "Simbolo não esperado: %c\n", buffer->cont[pos]);
        }
        tok->valor = 0;
        pos++;
    } else if(buffer->cont[pos] == '#'){
    	long initPos = pos;
		while (!eof() && buffer->cont[pos] != '\n')
			pos++;
		char *texto = TextoToken(initPos, pos); 
		printf("Comentário: %s\n", texto);
		free(texto);
		ProximoToken();
    } else {
        tok->tipo = TOKEN_ERRO;
        tok->valor = 0;
    }

    return tok;
}

void FinalizaLexer() {
    DestroiBuffer(buffer);
    free(tok);
}
