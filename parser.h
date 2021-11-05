//
// Analisador sintático para MiniCalc
//

#ifndef MINICALC_PARSER_H
#define MINICALC_PARSER_H

#include "lexer.h"

#include <string.h>

typedef enum tagTipoOper {
    OPER_SOMA,
    OPER_SUBT,
    OPER_MULT,
    OPER_DIV,
    OPER_MOD,
    OPER_POW,
    OPER_CONST,
    OPER_VAR
} TipoOper;

typedef struct tagExpressao {
    struct tagExpressao *op1;
    struct tagExpressao *op2;
    float valor;
    TipoOper oper;
    char nomeIdentificador[IDENT_MAX_SIZE];
} Expressao;

typedef struct tagDeclaracao {
    char nomeIdentificador[IDENT_MAX_SIZE];
    Expressao *e;
    struct tagDeclaracao *proxima;
} Declaracao;


typedef struct tagPrograma {
	Declaracao *declaracao;
    Expressao *e;
} Programa;


Programa* AnalisePrograma();
Declaracao* AnaliseDeclaracao();
Expressao* AnaliseExpressao();
void DestroiPrograma(Programa *p);

#endif //MINICALC_PARSER_H
