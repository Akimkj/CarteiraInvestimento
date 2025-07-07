#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id;
    float custo;
    float retorno;
}Acao;

int menu();
float getAvailableCapital(char f[]);


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
    
    printf("%.2f", availableCapital);

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
    free(file);
    return avCap;
}