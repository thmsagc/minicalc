#include "var.h"

Item tabela[MAX_VARS];
int tamanhoAtual = 0;

void AdicionaVar(char* nome, float valor) {
    if (tamanhoAtual >= MAX_VARS) {
        fprintf(stderr, "Tabela de variaveis esgotada.\n");
        exit(4);
    }
    tabela[tamanhoAtual].valor = valor;
    strcpy(tabela[tamanhoAtual].nome, nome);
    tamanhoAtual++;
}

bool ConsultaVar(char* nome, float* valor) {
    for (int i = 0; i < tamanhoAtual; i++) {
        if (strcmp(nome, tabela[i].nome) == 0) {
            *valor = tabela[i].valor;
            return true;
        }
    }
    return false;
}
