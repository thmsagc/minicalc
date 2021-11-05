//
// Analisador sintático para MiniCalc
//

// Analisador descendente recursivo

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "lexer.h"

Token *t;

Declaracao* AnaliseDeclaracao() {
    t = ProximoToken();

    if (t->tipo != TOKEN_VAR)
        return NULL;

    Declaracao *res = (Declaracao*) malloc(sizeof(Declaracao));

    t = ProximoToken();

    if (t->tipo != TOKEN_IDENT) {
        fprintf(stderr, "Erro de sintaxe: identificador esperado\n");
        free(res);
        exit(2);
    }

    strcpy(res->nomeIdentificador, t->nome);

    t = ProximoToken();

    if (t->tipo != TOKEN_ASSIGN) {
        fprintf(stderr, "Erro de sintaxe: '=' esperado\n");
        free(res);
        exit(2);
    }

    res->e = AnaliseExpressao();

    t = ProximoToken();

    if (t->tipo != TOKEN_PTVIR) {
        fprintf(stderr, "Erro de sintaxe: ';' esperado no final da declaracao\n");
        free(res);
        exit(2);
    }

    return res;
}



// Analisador sintático do programa
// Assume que o analisador léxico foi inicializado com o código-fonte
Programa* AnalisePrograma() {
    Programa *res = (Programa*) malloc(sizeof(Programa));

    if (res == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria.");
        exit(1);
    }
    
    Declaracao *origem = AnaliseDeclaracao();
 
    res->declaracao = origem;
    
    if (res->declaracao != NULL) {
        Declaracao *d2 = AnaliseDeclaracao();
        while (d2 != NULL) {
            res->declaracao->proxima = d2;
            res->declaracao = d2;
            d2 = AnaliseDeclaracao();
        }
        res->declaracao->proxima = NULL;
    }

    res->declaracao = origem;

    if (t->tipo != TOKEN_PRINT) {
        fprintf(stderr, "Erro sintatico: palavra-chave 'print' esperada no inicio do programa.");
        exit(2);
    }

    // analisa a expressao seguinte
    res->e = AnaliseExpressao();


    return res;
}


Expressao* AnaliseExpressao() {
    // analisa a expressao
    Expressao *res = (Expressao*) malloc(sizeof(Expressao));

    // parentese abrindo
    t = ProximoToken();

    // se proximo token for constante inteira, retorne expressao constante
    if (t->tipo == TOKEN_INT || t->tipo == TOKEN_FLOAT) {
        res->oper = OPER_CONST;
        res->valor = t->valor;
        res->op1 = NULL;
        res->op2 = NULL;
        return res;
    }


	//se o próximo token for um identificador, retorne uma expressão composta por uma variável
	if(t->tipo == TOKEN_IDENT){
		res->oper = OPER_VAR;
		res->valor = 0;
		strcpy(res->nomeIdentificador, t->nome);
        res->op1 = NULL;
        res->op2 = NULL;
        return res;	
	}


    //if (t->tipo != TOKEN_ABREPAR && t->tipo != TOKEN_ABRECOL) {
    //    fprintf(stderr, "Erro sintatico: '(' ou '[' esperado");
    //    exit(2);
    //}

    // primeiro operando
    res->op1 = AnaliseExpressao(); // Expressao*

    // operador
    t = ProximoToken();

    if (t->tipo != TOKEN_SOMA && t->tipo != TOKEN_SUBT && t->tipo != TOKEN_MULT && t->tipo != TOKEN_DIV && t->tipo != TOKEN_MOD && t->tipo != TOKEN_POW) {
        fprintf(stderr, "Erro sintatico: operador esperado\n");
        exit(2);
    }

    switch(t->tipo){
        case TOKEN_SOMA:
            res->oper = OPER_SOMA;
            break;
        case TOKEN_SUBT:
            res->oper = OPER_SUBT;
            break;
        case TOKEN_MULT:
            res->oper = OPER_MULT;
            break;
        case TOKEN_DIV:
            res->oper = OPER_DIV;
            break;
        case TOKEN_MOD:
            res->oper = OPER_MOD;
            break;
        case TOKEN_POW:
            res->oper = OPER_POW;
            break;
    }

    // segundo operando
    res->op2 = AnaliseExpressao();

    // parentese fechando
    t = ProximoToken();

    //if (t->tipo != TOKEN_FECHAPAR && t->tipo != TOKEN_FECHACOL) {
    //    fprintf(stderr, "Erro sintatico: ')' ou ']' esperado");
    //    exit(2);
    //}

    return res;
}


void DestroiDeclaracoes(Declaracao *d){
	Declaracao *d2;
	while(d != NULL){
		d2 = d->proxima;
		free(d);
		d = d2;
	}
}

void DestroiExpressao(Expressao *e) {
    if (e->oper == OPER_SOMA || e->oper == OPER_SUBT || e->oper == OPER_MULT || e->oper == OPER_DIV || e->oper == OPER_MOD || e->oper == OPER_POW) {
        DestroiExpressao(e->op1);
        DestroiExpressao(e->op2);
        e->op1 = NULL;
        e->op2 = NULL;
    }

    free(e);
}

void DestroiPrograma(Programa *p) {
    DestroiExpressao(p->e);
    DestroiDeclaracoes(p->declaracao);
    p->e = NULL;
    free(p);
}
