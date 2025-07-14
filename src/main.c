#include <stdio.h>
#include <string.h> 
#include "interface.h"

int main() {
    int opcao = menu();
    char fileName[100];
    switch (opcao) {
        case(1): strcpy(fileName, ".\\desafios\\iniciante.txt"); break;
        case(2): strcpy(fileName, ".\\desafios\\moderado.txt"); break;
        case(3): strcpy(fileName, ".\\desafios\\dificil.txt"); break;
        case(4): strcpy(fileName, ".\\desafios\\expert.txt"); break;
        default: printf("Erro: o Valor precisa ser entre 1 e 4."); return -1;
    }

    float availableCapital = getAvailableCapital(fileName);
    if (availableCapital == -1) {
        return -1;
    }

    int quantAcoes = getQuantAcoes(fileName);
    if (quantAcoes == -1) {
        return -1;
    }
    
    Acao *acoes = (Acao *) malloc(quantAcoes * sizeof(Acao));
    if (acoes == NULL) {
        printf("Erro ao alocar memória para as acoes.");
        return -1;
    }

    readActions(fileName,acoes, quantAcoes);

    stockPicking(acoes, quantAcoes, availableCapital);

    free(acoes);
    return 0;
}

