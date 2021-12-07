/*#include "file.h"
#include "lexer.h"
#include "parser.h"*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lexer.h"

void ImprimeTipoToken(int tipo);

int main() {
	InicializaLexer("./programa.minic");

	int i = 0;

	Token *t = ProximoToken();
    while (t->tipo != TOKEN_EOF) {
        if(t->tipo == TOKEN_LITERAL){
        	printf("%d - ", i);
        	ImprimeTipoToken(t->tipo);
        	printf(" - Valor do token: %d\n", t->valor);
        }
        else if(t->tipo == TOKEN_IDENTIFIER) {
            printf("%d - ", i);
        	ImprimeTipoToken(t->tipo);
        	printf(" - Valor do token: %s\n", t->nome);
        }
        else if(t->tipo == TOKEN_KEYWORD) {
            printf("%d - ", i);
        	ImprimeTipoToken(t->tipo);
        	printf(" - Valor do token: %s\n", t->nome);
        }
        else {
        	printf("%d - ", i);
        	ImprimeTipoToken(t->tipo);
        	printf("\n");
        }
        t = ProximoToken();
        i++;
	}
	FinalizaLexer();
	return 1;
	
}

void ImprimeTipoToken(int tipo){
	switch(tipo){
		case TOKEN_LITERAL:
			printf("TOKEN_LITERAL");
			break;
		case TOKEN_KEYWORD:
			printf("TOKEN_KEYWORD");
			break;
		case TOKEN_IDENTIFIER:
			printf("TOKEN_IDENTIFIER");
			break;
		case TOKEN_SEMICOLON:
			printf("TOKEN_SEMICOLON");
			break;
		case TOKEN_ERROR:
			printf("TOKEN_ERROR");
			break;
		case TOKEN_ADD:
			printf("TOKEN_ADD");
			break;
		case TOKEN_SUB:
			printf("TOKEN_SUB");
			break;
		case TOKEN_MUL:
			printf("TOKEN_MUL");
			break;
		case TOKEN_DIV:
			printf("TOKEN_DIV");
			break;
		case TOKEN_MOD:
			printf("TOKEN_MOD");
			break;
		case TOKEN_POW:
			printf("TOKEN_POW");
			break;
		case TOKEN_AND:
			printf("TOKEN_AND");
			break;
		case TOKEN_LESS:
			printf("TOKEN_LESS");
			break;
		case TOKEN_NEG:
			printf("TOKEN_NEG");
			break;
		case TOKEN_OPENPARENTHESES:
			printf("TOKEN_OPENPARENTHESES");
			break;
		case TOKEN_CLOSEPARENTHESES:
			printf("TOKEN_CLOSEPARENTHESES");
			break;
		case TOKEN_OPENBRACKETS:
			printf("TOKEN_OPENBRACKETS");
			break;
		case TOKEN_CLOSEBRACKETS:
			printf("TOKEN_CLOSEBRACKETS");
			break;
		case TOKEN_OPENKEYS:
			printf("TOKEN_OPENKEYS");
			break;
		case TOKEN_CLOSEKEYS:
			printf("TOKEN_CLOSEKEYS");
			break;
		case TOKEN_COMMA:
			printf("TOKEN_COMMA");
			break;
		case TOKEN_EOF:
			printf("TOKEN_EOF");
			break;
		default:
			printf("Token não identificado: '%d'", tipo);
			break;
	}
}


