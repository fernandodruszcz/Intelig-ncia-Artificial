#include "operacoes_no.h"

void copiaMatriz(int original[TAM][TAM], int copia[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            copia[i][j] = original[i][j];
        }
    }
}

void atribuiEsperadoAteFim(struct no *no){
    int soma = 0;
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            // descobre a posicao que a peca deveria estar e soma a distancia em 'soma'
            int x = no -> matrizEstadoAtual[i][j]/TAM;
            int y = no -> matrizEstadoAtual[i][j] % TAM;
            soma += abs(x - i) + abs(y - j);
            //printf("A peça %d que deveria estar em %d,%d está em %d,%d. Distância %d\n",
            //                no -> matrizEstadoAtual[i][j], x, y, i, j, soma);
        }
    }
    no -> quantidadeMovimentosAteFim = soma;
}

void atribuiCusto(struct no *filho){
    filho -> quantidadeMovimentos = filho -> pai -> quantidadeMovimentos + 1;
}

void atribuiTotalEsperado(struct no *filho){
    filho -> quantidadeMovimentosEsperada = 
                filho -> quantidadeMovimentos + filho -> quantidadeMovimentosAteFim;
}

void iniciaRaiz(struct no *raiz, int matrizInicial[TAM][TAM]){
    copiaMatriz(matrizInicial, raiz -> matrizEstadoAtual);
    raiz -> quantidadeMovimentos = 0; // custo inicial 0
    atribuiEsperadoAteFim(raiz);
    atribuiTotalEsperado(raiz);
    raiz -> quantidadeFilhos = 0;
    movimentosPossiveis(raiz -> matrizEstadoAtual, &(raiz -> movimentosPossiveis));
}

void imprimeNo(struct no no){
    printf("Imprimindo no de matriz:\n");
    imprimeMatriz(no.matrizEstadoAtual);
    printf("Custo até então: %d\n", no.quantidadeMovimentos);
    printf("Custo esperado (heurística): %d\n", no.quantidadeMovimentosAteFim);
    printf("Custo total esperado: %d\n", no.quantidadeMovimentosEsperada);
    imprimeMovimentos(no.movimentosPossiveis);
}

struct no * criaFilho(struct no *pai, int origemMovimento){
    if((pai -> movimentosPossiveis.origens[origemMovimento].x >= 0) &&
        (pai -> movimentosPossiveis.origens[origemMovimento].y >= 0)){
        struct no *filho = (struct no *)malloc(sizeof(struct no));
        filho -> pai = pai;
        copiaMatriz(pai -> matrizEstadoAtual, filho -> matrizEstadoAtual);
        atribuiCusto(filho);
        atribuiEsperadoAteFim(filho);
        atribuiTotalEsperado(filho);

        realizaMovimento(filho -> matrizEstadoAtual, pai -> movimentosPossiveis, origemMovimento);

        movimentosPossiveis(filho -> matrizEstadoAtual, &(filho -> movimentosPossiveis));
        return filho;
    }
    return NULL;
}