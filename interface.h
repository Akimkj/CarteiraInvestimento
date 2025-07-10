#ifndef ACOES_H
#define ACOES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id[2];
    float custo;
    float retorno;
    float eficiencia;
}Acao;

int menu();
float getAvailableCapital(char f[]);
int getQuantAcoes(char f[]);
void readActions(char f[], Acao *acoes);
int compararEficiencia(const void *a, const void *b);
void stockPicking(Acao *acoes, int quantAcoes, float capitalDisponivel);

#endif