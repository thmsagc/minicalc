#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arq.h"
#include "lexer.h"
#include "parser.h"
#include "var.h"

int potencia(int base, int expoente);
void ImprimeTipoToken(int tipo);
void ImprimeDeclaracoes(Declaracao* d);
void ProcessaDeclaracoes(Declaracao *d);
void ImprimeResultado(float resultado);

float AvaliaExpressao(Expressao* e) {
    float res = 0;
    float v1, v2;

    switch (e->oper) {
		case OPER_VAR:
            // consulta a tabela de variaveis para obter o valor
            if (ConsultaVar(e->nomeIdentificador, &v1)) {
                res = v1;
            } else {
                fprintf(stderr, "Variavel nao declarada: %s\n", e->nomeIdentificador);
                exit(3);
            }
            break;
        case OPER_CONST:
            res = e->valor;
            break;
        case OPER_SOMA:
            v1 = AvaliaExpressao(e->op1);
            v2 = AvaliaExpressao(e->op2);
            res = v1 + v2;
            break;
        case OPER_SUBT:
            v1 = AvaliaExpressao(e->op1);
            v2 = AvaliaExpressao(e->op2);
            res = v1 - v2;
            break;
        case OPER_MULT:
            v1 = AvaliaExpressao(e->op1);
            v2 = AvaliaExpressao(e->op2);
            res = v1 * v2;
            break;
        case OPER_DIV:
            v1 = AvaliaExpressao(e->op1);
            v2 = AvaliaExpressao(e->op2);
            res = v1 / v2;
            break;
        case OPER_MOD:        	
		    v1 = AvaliaExpressao(e->op1);
		    v2 = AvaliaExpressao(e->op2);
		    res = (int)v1 % (int)v2;
            break;
        case OPER_POW:
            v1 = AvaliaExpressao(e->op1);
            v2 = AvaliaExpressao(e->op2);
            res = potencia(v1, v2);
            break;
        default:
            printf("Operador nao reconhecido.\n");
    }

    return res;
}

int main() {
    InicializaLexer("./test/operacao_pontos_flutuantes.mc");

    // arvore sintatica do programa
    Programa *p = AnalisePrograma();
    
    //ImprimeDeclaracoes(p->declaracao);
    
    ProcessaDeclaracoes(p->declaracao);


	float resultado = AvaliaExpressao(p->e);
    ImprimeResultado(resultado);

    DestroiPrograma(p);
    FinalizaLexer();
    return 0;
}

void ImprimeResultado(float resultado){
	if(resultado == (int)resultado){
		printf("%d\n", (int)resultado);
	} else {
		printf("%.4f\n", resultado);
	}
}

/*int main() {
    InicializaLexer("./test/expcompleta.mc");

    // arvore sintatica do programa
    Programa *p = AnalisePrograma();

    float resultado = AvaliaExpressao(p->e);

    printf("%f\n", resultado);

    DestroiPrograma(p);
    FinalizaLexer();
    return 0;
}*/


/*int main() {
    InicializaLexer("./test/expcompleta.mc");

    Token* token = ProximoToken();
    
    while(token->tipo != TOKEN_EOF && token->tipo != TOKEN_ERRO){
    	printf("Tipo do Token: ");
    	ImprimeTipoToken(token->tipo);
    	printf("\n");
    	
    	if(token->tipo == TOKEN_INT){
    		printf("Valor do Token: %.0f\n", token->valor);
    	} else if(token->tipo == TOKEN_IDENT){
    		printf("Nome do Identificador: %s\n", token->nome);
    	} else {
    		printf("\n");
    	}
    	token = ProximoToken();
    }


    FinalizaLexer();
    return 0;
}*/

int potencia(int base, int expoente){
	int resultado = base;
	for(int i = 1; i < expoente; i++){
		resultado *= base;
	}
	return resultado;
}

void ImprimeDeclaracoes(Declaracao *d){
	while(d != NULL){
		printf("Declaração - ident %s\n", d->nomeIdentificador);
		d = d->proxima;
	}
}

void ProcessaDeclaracoes(Declaracao *d) {
    while (d != NULL) {
        float val = AvaliaExpressao(d->e);
        AdicionaVar(d->nomeIdentificador, val);
        d = d->proxima;
    }
}

void ImprimeTipoToken(int tipo){
	switch(tipo){
		case TOKEN_INT:
			printf("TOKEN_INT");
			break;
		case TOKEN_FLOAT:
			printf("TOKEN_FLOAT");
			break;
		case TOKEN_PRINT:
			printf("TOKEN_PRINT");
			break;
		case TOKEN_IDENT:
			printf("TOKEN_IDENT");
			break;
		case TOKEN_VAR:
			printf("TOKEN_VAR");
			break;
		case TOKEN_ASSIGN:
			printf("TOKEN_ASSIGN");
			break;
		case TOKEN_PTVIR:
			printf("TOKEN_PTVIR");
			break;
		case TOKEN_ERRO:
			printf("TOKEN_ERRO");
			break;
		case TOKEN_SOMA:
			printf("TOKEN_SOMA");
			break;
		case TOKEN_SUBT:
			printf("TOKEN_SUBT");
			break;
		case TOKEN_MULT:
			printf("TOKEN_MULT");
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
		case TOKEN_ABREPAR:
			printf("TOKEN_ABREPAR");
			break;
		case TOKEN_FECHAPAR:
			printf("TOKEN_FECHAPAR");
			break;
		case TOKEN_ABRECOL:
			printf("TOKEN_ABRECOL");
			break;
		case TOKEN_FECHACOL:
			printf("TOKEN_FECHACOL");
			break;
		case TOKEN_EOF:
			printf("TOKEN_EOF");
			break;
		default:
			printf("Token não identificado: '%d'", tipo);
			break;
	}
}
