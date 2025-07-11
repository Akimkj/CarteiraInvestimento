#include <string.h>
#include "interface.h"
const int TAM_MAX_LINHA = 400;

int menu() {
    int op = 0;
    imprime("Escolha uma das opcões: \n");
    printf("\t1 - Carteira iniciante.\n");
    printf("\t2 - Carteira moderada.\n");
    printf("\t3 - Carteira dificil.\n");
    printf("\t4 - Carteira expert\n");
    scanf("%d", &op);
    return op;
}
float getAvailableCapital(char f[]) {
    FILE *file = fopen(f, "r");
    float avCap = 0;
    if (file) {
        char linha[TAM_MAX_LINHA];
        while (fgets(linha, sizeof(linha), file)) {
            if(sscanf(linha, "CAPITAL_DISPONIVEL_R$: %f", &avCap)) {
                break;
            }
        } 
    }
    else {
        printf("Erro ao abrir o arquivo para pegar o capital disponivel.\n");
        return -1;
    }
    
    fclose(file);
    return avCap;
}
int getQuantAcoes(char f[]) {
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para pegar quantidade de acoes\n.");
        return -1;
    }

    int count = 0;
    char linha[TAM_MAX_LINHA];
    Acao acoes_temp[50];

    while (fgets(linha, sizeof(linha), file)) {

        if (linha[0] == '#' || linha[0] == '*' || strlen(linha) <= 1) {
            continue;
        }

        if(sscanf(linha, "%2s %f %f", acoes_temp[count].id, &acoes_temp[count].custo, &acoes_temp[count].retorno) == 3) {
            count++;
        }
    }
    fclose(file);
    return count;
}
void readActions(char f[], Acao *acoes) {
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para ler acoes.");
        return;
    }

    char linha[TAM_MAX_LINHA];
    int count = 0;

    while(fgets(linha, sizeof(linha), file)) {
        if (linha[0] == '#' || linha[0] == '*' || strlen(linha) <= 1) {
            continue;
        }

        if (sscanf(linha, "%2s %f %f", acoes[count].id, &acoes[count].custo, &acoes[count].retorno) == 3) {
            count++;
        }
    }

    fclose(file);
}


int compararEficiencia(const void *a, const void *b) {
    Acao *x = (Acao*)a;
    Acao *y = (Acao*)b;
    if ((*y).eficiencia > (*x).eficiencia){
        return 1;
    } 
    else if ((*y).eficiencia < (*x).eficiencia) {
        return -1;
    } 
    else {
        return 0;
    }
}

void eficienceCalculeAndCopy(Acao* acoes, Acao* copia, int indice,int totalAcoes) {
    if (indice >= totalAcoes) {
        return;
    }

    copia[indice].custo = acoes[indice].custo;
    copia[indice].retorno = acoes[indice].retorno;
    if (acoes[indice].custo > 0) {
        copia[indice].eficiencia = acoes[indice].retorno / acoes[indice].custo;
    }
    else {
        copia[indice].eficiencia = 0;
    }
    strcpy(copia[indice].id, acoes[indice].id);

    eficienceCalculeAndCopy(acoes, copia, indice + 1, totalAcoes);
}

void stockPicking(Acao *acoes, int quantAcoes, float capitalDisponivel) {
    Acao *lista = malloc(quantAcoes * sizeof(Acao));
    if (lista == NULL) {
        printf("Erro ao alocar memoria em stockPicking!");
        return;
    }
    
    eficienceCalculeAndCopy(acoes, lista, 0, quantAcoes);

    
    qsort(lista, quantAcoes, sizeof(Acao), compararEficiencia);

    float custo_total = 0.0;
    float retorno_total = 0.0;
    float capital_restante = capitalDisponivel;

    printf("\n\n");
    printf("------------------------------------");
    printf("\nCarteira de Investimentos Otimizada\n");
    printf("------------------------------------\n");
    printf("Capital disponivel: R$ %.2f\n", capital_restante);
    printf("\n");
    printf("Acoes a comprar:\n");
    for (int i = 0; i < quantAcoes; i++) {
        if (lista[i].custo <= capital_restante) {
            printf("- Acao: %2s (Custo: R$ %.2f, Retorno: %.2f%%)\n", lista[i].id, lista[i].custo, lista[i].retorno);
            capital_restante -= lista[i].custo;
            custo_total += lista[i].custo;
            retorno_total += lista[i].retorno;
        }
    }
    printf("\n");
    printf("Custo total: R$ %.2f\n", custo_total);
    printf("Retorno total estimado: %.2f%%\n", retorno_total);

    free(lista);
}