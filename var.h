#ifndef MINICALC_VAR_H
#define MINICALC_VAR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"

#define MAX_VARS      60

typedef struct tagItem {
    char nome[IDENT_MAX_SIZE];
    float valor;
} Item;



void AdicionaVar(char* nome, float valor);
bool ConsultaVar(char* nome, float* valor);


#endif //MINICALC_VAR_H
