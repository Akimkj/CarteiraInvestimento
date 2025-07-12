# CarteiraInvestimento
Um programa que recebe um arquivo de texto como entrada e retorna a melhor combinação possível de ações que tenham o maior retorno dentro do capital disponível
## Sobre o Projeto
Este projeto foi desenvolvido como a terceira avaliação prática da disciplina de Linguagem de Programação I. Consiste em um sistema de simulação de carteiras de investimento, que lê um arquivo de texto com dados de ações e, com base no capital disponível, seleciona automaticamente a combinação mais eficiente de ações para maximizar o retorno. A implementação foi feita em linguagem C, com uso de estruturas, modularização e manipulação de arquivos.

# Instrução de Instalação
1. É necessário ter um compilador C instalado.

2. Git (para clonar o repositório).


## Clone o repositório 

````bash
git clone https://github.com/Akimkj/CarteiraInvestimento.git
````

## Compilar o projeto
````bash
gcc *.c -o ./output/main.exe

````
## Compilar o projeto
````bash
./output/main.exe
````

Importante Certifique-se de que a pasta desafios esteja no mesmo diretório do executável e contenha os arquivos iniciante.txt, moderado.txt, dificil.txt e expert.txt.

# Comandos e Estruturas Presentes no Código

## Tipos e estruturas
````c
typedef struct {
    char id[2];
    float custo;
    float retorno;
    float eficiencia;
} Acao;
````
Explicação dos campos:
| Campo        | Tipo      | Descrição                                                               |
| ------------ | --------- | ----------------------------------------------------------------------- |
| `id`         | `char[2]` | Identificador da ação (ex: "A1", "B2"). Representa de forma compacta.   |
| `custo`      | `float`   | Valor da ação em reais (R\$).                                           |
| `retorno`    | `float`   | Retorno estimado da ação, em percentual.                                |
| `eficiencia` | `float`   | Razão entre retorno e custo (`retorno / custo`). Usada para otimização. |

## Funções que usam a struct `Acao`

| Função                 | Tipo de uso        | Descrição                                                                    |
| ---------------------- | ------------------ | ---------------------------------------------------------------------------- |
| `getQuantAcoes()`      | Leitura            | Conta quantas ações estão no arquivo, preenchendo temporariamente a struct.  |
| `readActions()`        | Leitura            | Lê os dados do arquivo e preenche um vetor de structs `Acao`.                |
| `compararEficiencia()` | Comparação         | Compara duas ações com base na eficiência, usada para ordenação (`qsort`).   |
| `stockPicking()`       | Processamento      | Calcula e escolhe a melhor combinação de ações dentro do capital disponível. |
| `main()`               | Alocação e chamada | Cria dinamicamente o vetor de `Acao` e chama as funções que usam a struct.   |


## Lógica geral do programa

1. O usuário escolhe o perfil de carteira (iniciante, moderado, difícil ou expert).
2. O programa lê o arquivo correspondente.
3. Obtém o capital disponível e a lista de ações.
4. Calcula a eficiência (retorno / custo) de cada ação.
5. Ordena as ações por eficiência usando `qsort()`.
6. Seleciona automaticamente as melhores ações dentro do orçamento.
7. Exibe a carteira final, com custo total e retorno estimado.
