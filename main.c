#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[2];
    float custo;
    float retorno;
}Acao;

int menu();
float getAvailableCapital(char f[]);
int getQuantAcoes(char f[]);
void readActions(char f[], Acao *acoes);

int main() {
    int opcao = menu();
    char fileName[100];
    switch (opcao) {
        case(1): strcpy(fileName, "..\\desafios\\iniciante.txt"); break;
        case(2): strcpy(fileName, "..\\desafios\\moderado.txt"); break;
        case(3): strcpy(fileName, "..\\desafios\\dificil.txt"); break;
        case(4): strcpy(fileName, "..\\desafios\\expert.txt"); break;
        default: printf("Erro: o Valor precisa ser entre 1 e 4."); return -1;
    }

    float availableCapital = getAvailableCapital(fileName);
    int quantAcoes = getQuantAcoes(fileName);
    Acao *acoes = (Acao *) malloc(quantAcoes * sizeof(Acao));
    if (acoes == NULL) {
        printf("Erro ao alocar memória para as acoes.");
        return -1;
    }

    readActions(fileName,acoes);

    for (int i = 0; i < quantAcoes; i++) {
        printf("Id: %s\tCusto: %.2f\tRetorno: %.2f\t\n", acoes[i].id, acoes[i].custo, acoes[i].retorno);
    }

    free(acoes);
    return 0;
}

int menu() {
    int op = 0;
    printf("Escolha uma das opcões: \n");
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
        char linha[300];
        while (fgets(linha, sizeof(linha), file)) {
            if(sscanf(linha, "CAPITAL_DISPONIVEL_R$: %f", &avCap)) {
                break;
            }
        } 
    }
    else {
        printf("Erro ao abrir o arquivo para pegar o capital disponivel.");
        return -1;
    }

    fclose(file);
    return avCap;
}
int getQuantAcoes(char f[]) {
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        printf("Erro3 ao abrir o arquivo.");
        return -1;
    }

    int count = 0;
    char linha[400];
    Acao acoes_temp[50];

    while (fgets(linha, sizeof(linha), file)) {

        if (linha[0] == '#' || linha[0] == '*' || strlen(linha) <= 1) {
            continue;
        }

        if(sscanf(linha, "%s %f %f", &acoes_temp[count].id, &acoes_temp[count].custo, &acoes_temp[count].retorno) == 3) {
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

    char linha[300];
    int count = 0;

    while(fgets(linha, sizeof(linha), file)) {
        if (linha[0] == '#' || linha[0] == '*' || strlen(linha) <= 1) {
            continue;
        }

        if (sscanf(linha, "%s %f %f", &acoes[count].id, &acoes[count].custo, &acoes[count].retorno) == 3) {
            count++;
        }
    }

    fclose(file);
}