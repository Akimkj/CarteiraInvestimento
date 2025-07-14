#ifndef INTERFACE_H
#define INTERFACE_H


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char id[2];
    double custo;
    double retorno;
    double eficiencia;
}Acao;

int menu();
float getAvailableCapital(char f[]);
int getQuantAcoes(char f[]);
void readActions(char f[], Acao *acoes, int quantAcoes);
void eficienceCalculeAndCopy(Acao* acoes, Acao* copia, int indice,int totalAcoes);
void bSort(Acao* lista, int quantAcoes);
void stockPicking(Acao *acoes, int quantAcoes, float capitalDisponivel); 

#endif