#include <stdio.h>

#include "operacoes_problema.h"

struct no{
    struct no *filhos;
    struct no *pai;
    int quantidadeMovimentos; // custo // g()
    int quantidadeMovimentosAteFim; // heuristica // h()
    int quantidadeMovimentosEsperada; // f() = g() + h()
    int matrizEstadoAtual[TAM][TAM];
};

int h(int matriz[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            // se a peca nao estiver na posicao correta
            if(matriz[i][j] != i*TAM + j){
                
            }
        }
    }
}

void main(){
    int matriz[TAM][TAM];
    iniciaMatriz(matriz);

    struct movimento movimento;;
    movimentosPossiveis(matriz, &movimento);

    imprimeMatriz(matriz);
    imprimeMovimentos(movimento);

    for(int origem = 0; origem < MAX_MOVS; origem++){
        printf("Movimento %d:\n", origem);
        realizaMovimento(matriz, movimento, origem);
        imprimeMatriz(matriz);
        movimentosPossiveis(matriz, &movimento);
    }

}