#include <stdio.h>
#include <stdlib.h>

#include "arq.h"
#include "lexer.h"
#include "parser.h"

int potencia(int base, int expoente);

float AvaliaExpressao(Expressao* e) {
    float res = 0;
    float v1, v2;

    switch (e->oper) {
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
            res = v1 * v2;
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
    InicializaLexer("./test/expcompleta.mc");

    // arvore sintatica do programa
    Programa *p = AnalisePrograma();

    float resultado = AvaliaExpressao(p->e);

    printf("%f\n", resultado);

    DestroiPrograma(p);
    FinalizaLexer();
    return 0;
}

int potencia(int base, int expoente){
	int resultado = base;
	for(int i = 1; i < expoente; i++){
		resultado *= base;
	}
	return resultado;
}
